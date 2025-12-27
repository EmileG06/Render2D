#pragma once

#include "Core/Core.h"

#include "Texture.h"

namespace Render2D::Renderer
{

	class TextureLibrary
	{
	public:
		void Add(const std::string& name, const std::shared_ptr<Texture>& texture);
		void Add(const std::shared_ptr<Texture>& texture);

		std::shared_ptr<Texture> Load(const std::string& path);
		std::shared_ptr<Texture> Load(const std::string& name, const std::string& path);
		std::shared_ptr<Texture> Create(const std::string& name, const TextureSpecification& specs);

		std::shared_ptr<Texture> Get(const std::string& name);
		bool Exists(const std::string& name);

		void Clear();

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture>> m_Textures;
	};

}
