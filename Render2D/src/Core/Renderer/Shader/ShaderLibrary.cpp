#include "ShaderLibrary.h"

#include "Core/Logger/Logger.h"

namespace Render2D::Renderer
{

	void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		if (Exists(name))
		{
			LOG_WARNING("Shader already exists: {0}", name);
			return;
		}
		m_Shaders[name] = shader;
	}

	void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}

	std::shared_ptr<Render2D::Renderer::Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = std::make_shared<Shader>(filepath, filepath);
		Add(shader);
		return shader;
	}

	std::shared_ptr<Render2D::Renderer::Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = std::make_shared<Shader>(filepath, filepath);
		Add(name, shader);
		return shader;
	}

	std::shared_ptr<Render2D::Renderer::Shader> ShaderLibrary::Load(const std::string& name, const std::string& vertexPath, const std::string& fragmentPath)
	{
		auto shader = std::make_shared<Shader>(vertexPath, fragmentPath);
		Add(name, shader);
		return shader;
	}

	std::shared_ptr<Render2D::Renderer::Shader> ShaderLibrary::Get(const std::string& name)
	{
		if (!Exists(name))
		{
			LOG_ERROR("Shader not found: {0}", name);
			return nullptr;
		}
		return m_Shaders[name];
	}

	bool ShaderLibrary::Exists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}

}
