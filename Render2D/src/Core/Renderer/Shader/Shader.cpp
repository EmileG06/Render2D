#include "Shader.h"

#include <fstream>
#include <sstream>

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include "Core/Logger/Logger.h"

namespace Render2D::Renderer
{

	Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	{
		std::string vertexSource = ReadFile(vertexPath);
		std::string fragmentSource = ReadFile(fragmentPath);
		m_ProgramID = CreateProgram(vertexSource, fragmentSource);

		size_t lastSlash = vertexPath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;

		size_t lastDot = vertexPath.rfind('.');
		size_t count = lastDot == std::string::npos ? vertexPath.size() - lastSlash : lastDot - lastSlash;

		m_Name = vertexPath.substr(lastSlash, count);
	}

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc, bool fromSource)
	{
		m_ProgramID = CreateProgram(vertexSrc, fragmentSrc);
		m_Name = "InlineShader";
	}

	Shader::~Shader()
	{
		glDeleteProgram(GetProgramID());
	}

	void Shader::Bind() const
	{
		glUseProgram(GetProgramID());
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::SetInt(const std::string& name, int32_t value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetIntArray(const std::string& name, int32_t* values, uint32_t count)
	{
		glUniform1iv(GetUniformLocation(name), count, values);
	}

	void Shader::SetFloat(const std::string& name, float value)
	{
		glUniform1f(GetUniformLocation(name), value);
	}

	void Shader::SetFloat2(const std::string& name, const glm::vec2& value)
	{
		glUniform2f(GetUniformLocation(name), value.x, value.y);
	}

	void Shader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
	}

	void Shader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void Shader::SetMat3(const std::string& name, const glm::mat3& value)
	{
		glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	void Shader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
	}

	std::string Shader::ReadFile(const std::string& filepath)
	{
		std::ifstream file(filepath, std::ios::in | std::ios::binary);
		if (!file)
		{
			LOG_ERROR("File not found: {0}", filepath);
			return "";
		}

		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

	uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
	{
		uint32_t shader = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(shader, 1, &src, nullptr);
		glCompileShader(shader);

		int32_t success;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			int32_t length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(shader, length, &length, message);

			LOG_ERROR("Shader compilation failed ({0}): {1}", (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT"), message);

			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	uint32_t Shader::CreateProgram(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		uint32_t program = glCreateProgram();
		uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexSrc);
		uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentSrc);

		if (vs == 0 || fs == 0)
		{
			if (vs) glDeleteShader(vs);
			if (fs) glDeleteShader(fs);

			glDeleteProgram(program);

			return 0;
		}

		glAttachShader(program, vs);
		glAttachShader(program, fs);
		glLinkProgram(program);

		int32_t success;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			int32_t length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetProgramInfoLog(program, length, &length, message);

			LOG_ERROR("Program linking failed: {0}", message);

			glDeleteProgram(program);
			glDeleteShader(vs);
			glDeleteShader(fs);

			return 0;
		}

		glValidateProgram(program);

		glDeleteShader(vs);
		glDeleteShader(fs);

		return program;
	}

	int32_t Shader::GetUniformLocation(const std::string& name)
	{
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int32_t location = glGetUniformLocation(GetProgramID(), name.c_str());
		if (location == -1)
			LOG_WARNING("Uniform not found: {0}", name);

		m_UniformLocationCache[name] = location;
		return location;
	}

}
