#pragma once

#include "Core/Core.h"

namespace Render2D::Renderer
{

	enum class TextureFormat
	{
		None = 0,
		RGB8,
		RGBA8,
		RED_INTEGER
	};

	enum class TextureFilter
	{
		Linear = 0x2601, // GL_LINEAR
		Nearest = 0x2600 // GL_NEAREST
	};

	enum class TextureWrap
	{
		Repeat = 0x2901, // GL_REPEAT
		ClampToEdge = 0x812F, // GL_CLAMP_TO_EDGE
		ClampToBorder = 0x812D, // GL_CLAMP_TO_BORDER
		MirroredRepeat = 0x8370 // GL_MIRRORED_REPEAT
	};

	struct TextureSpecification
	{
		uint32_t Width = 1;
		uint32_t Height = 1;
		TextureFormat Format = TextureFormat::RGBA8;
		TextureFilter MinFilter = TextureFilter::Linear;
		TextureFilter MagFilter = TextureFilter::Linear;
		TextureWrap WrapS = TextureWrap::Repeat;
		TextureWrap WrapT = TextureWrap::Repeat;
		bool GenerateMips = true;
	};

	class Texture
	{
	public:
		Texture(const TextureSpecification& specs);
		Texture(const std::string& path);
		~Texture();

		void Bind(uint32_t slot = 0) const;
		void Unbind() const;

		void SetData(void* data, uint32_t size);

		uint32_t GetWidth() const { return m_Width; }
		uint32_t GetHeight() const { return m_Height; }
		uint32_t GetID() const { return m_ID; }
		const std::string& GetPath() const { return m_Path; }

		bool operator==(const Texture& other) const
		{
			return m_ID == other.m_ID;
		}

	private:
		void CreateTexture(const TextureSpecification& spec);

	private:
		uint32_t m_ID = 0;
		uint32_t m_Width = 0;
		uint32_t m_Height = 0;
		uint32_t m_InternalFormat = 0;
		uint32_t m_DataFormat = 0;
		std::string m_Path;
	};

}
