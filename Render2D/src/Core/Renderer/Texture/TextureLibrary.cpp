#include "TextureLibrary.h"

#include "Core/Logger/Logger.h"

namespace Render2D::Renderer
{

	void TextureLibrary::Add(const std::string& name, const std::shared_ptr<Texture>& texture)
	{
		if (Exists(name))
		{
			LOG_WARNING("Texture already exists in library: {0}", name);
			return;
		}
		m_Textures[name] = texture;
		LOG_TRACE("Texture added to library: {0}", name);
	}

	void TextureLibrary::Add(const std::shared_ptr<Texture>& texture)
	{
		auto& path = texture->GetPath();
		if (path.empty())
		{
			LOG_ERROR("Cannot add texture with empty path to library!");
			return;
		}

		auto lastSlash = path.find_last_of("/\\");
		auto filename = (lastSlash == std::string::npos) ? path : path.substr(lastSlash + 1);

		Add(filename, texture);
	}

	std::shared_ptr<Render2D::Renderer::Texture> TextureLibrary::Load(const std::string& path)
	{
		auto lastSlash = path.find_last_of("/\\");
		auto filename = (lastSlash == std::string::npos) ? path : path.substr(lastSlash + 1);

		if (Exists(filename))
		{
			LOG_TRACE("Texture already loaded, returning cached: {0}", filename);
			return Get(filename);
		}

		auto texture = std::make_shared<Texture>(path);
		Add(filename, texture);
		return texture;
	}

	std::shared_ptr<Render2D::Renderer::Texture> TextureLibrary::Load(const std::string& name, const std::string& path)
	{
		if (Exists(name))
		{
			LOG_TRACE("Texture already loaded, returning cached: {0}", name);
			return Get(name);
		}

		auto texture = std::make_shared<Texture>(path);
		Add(name, texture);
		return texture;
	}

	std::shared_ptr<Render2D::Renderer::Texture> TextureLibrary::Create(const std::string& name, const TextureSpecification& specs)
	{
		if (Exists(name))
		{
			LOG_TRACE("Texture already exists, returning existing: {0}", name);
			return Get(name);
		}

		auto texture = std::make_shared<Texture>(specs);
		Add(name, texture);
		return texture;
	}

	std::shared_ptr<Render2D::Renderer::Texture> TextureLibrary::Get(const std::string& name)
	{
		if (!Exists(name))
		{
			LOG_TRACE("Texture not found in library: {0}", name);
			return nullptr;
		}
		return m_Textures[name];
	}

	bool TextureLibrary::Exists(const std::string& name)
	{
		return m_Textures.find(name) != m_Textures.end();
	}

	void TextureLibrary::Clear()
	{
		LOG_INFO("Clearing texture library ({0} textures)", m_Textures.size());
		m_Textures.clear();
	}

}
