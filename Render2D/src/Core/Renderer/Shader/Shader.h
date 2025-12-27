#pragma once

#include "Core/Core.h"

namespace Render2D::Renderer
{

	class Shader
	{
	public:
		Shader(const std::string& vertexPath, const std::string& fragmentPath);
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc, bool fromSource);
		~Shader();

		void Bind() const;
		void Unbind() const;

		void SetInt(const std::string& name, int32_t value);
		void SetIntArray(const std::string& name, int32_t* values, uint32_t count);
		void SetFloat(const std::string& name, float value);
		void SetFloat2(const std::string& name, const glm::vec2& value);
		void SetFloat3(const std::string& name, const glm::vec3& value);
		void SetFloat4(const std::string& name, const glm::vec4& value);
		void SetMat3(const std::string& name, const glm::mat3& value);
		void SetMat4(const std::string& name, const glm::mat4& value);

		uint32_t GetProgramID() const { return m_ProgramID; }
		const std::string& GetName() const { return m_Name; }

	private:
		std::string ReadFile(const std::string& filepath);
		uint32_t CompileShader(uint32_t type, const std::string& source);
		uint32_t CreateProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
		int32_t GetUniformLocation(const std::string& name);

	private:
		uint32_t m_ProgramID;
		std::string m_Name;
		std::unordered_map<std::string, int32_t> m_UniformLocationCache;
	};

}
