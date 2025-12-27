#include "Texture.h"

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "Core/Logger/Logger.h"

namespace Render2D::Renderer
{

	static GLenum TextureFormatToGL(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB8:  return GL_RGB8;
		case TextureFormat::RGBA8: return GL_RGBA8;
		case TextureFormat::RED_INTEGER: return GL_R32I;
		}
		LOG_ERROR("Unknown texture format!");
		return 0;
	}

	static GLenum TextureFormatToDataFormat(TextureFormat format)
	{
		switch (format)
		{
		case TextureFormat::RGB8:  return GL_RGB;
		case TextureFormat::RGBA8: return GL_RGBA;
		case TextureFormat::RED_INTEGER: return GL_RED_INTEGER;
		}
		LOG_ERROR("Unknown texture format!");
		return 0;
	}

	Texture::Texture(const TextureSpecification& specs)
		: m_Width(specs.Width), m_Height(specs.Height)
	{
		m_InternalFormat = TextureFormatToGL(specs.Format);
		m_DataFormat = TextureFormatToDataFormat(specs.Format);

		CreateTexture(specs);

		LOG_INFO("Texture created from specification: {0}x{1}, Format={2}",
			m_Width, m_Height, static_cast<int32_t>(specs.Format));
	}

	Texture::Texture(const std::string& path)
		: m_Path(path)
	{
		int32_t width, height, channels;
		stbi_set_flip_vertically_on_load(true);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		if (!data)
		{
			LOG_ERROR("Failed to load texture: {0}", path);
			return;
		}

		m_Width = width;
		m_Height = height;

		uint32_t internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}
		else if (channels == 1)
		{
			internalFormat = GL_R8;
			dataFormat = GL_RED;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		if (internalFormat == 0 || dataFormat == 0)
		{
			LOG_ERROR("Texture format not supported! Channels: {0}", channels);
			stbi_image_free(data);
			return;
		}

		TextureSpecification specs;
		specs.Width = m_Width;
		specs.Height = m_Height;
		specs.Format = (channels == 4) ? TextureFormat::RGBA8 : TextureFormat::RGB8;

		CreateTexture(specs);

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		LOG_INFO("Texture loaded from file: {0}, {1}x{2}, Channels={3}",
			path, m_Width, m_Height, channels);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_ID);
		LOG_TRACE("Texture destroyed: ID={0}, Path={1}", m_ID, m_Path.empty() ? "N/A" : m_Path);
	}

	void Texture::Bind(uint32_t slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_ID);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		if (size != m_Width * m_Height * bpp)
		{
			LOG_ERROR("Data size mismatch! Expected: {}, Got: {}", m_Width * m_Height * bpp, size);
			return;
		}

		glBindTexture(GL_TEXTURE_2D, m_ID);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
		LOG_TRACE("Texture data updated: ID={0}, Size={1} bytes", m_ID, size);
	}

	void Texture::CreateTexture(const TextureSpecification& spec)
	{
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(spec.MinFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(spec.MagFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(spec.WrapS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(spec.WrapT));

		glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, nullptr);

		if (spec.GenerateMips)
			glGenerateMipmap(GL_TEXTURE_2D);

		LOG_TRACE("OpenGL texture created: ID={0}, Size={1}x{2}", m_ID, m_Width, m_Height);
	}

}
