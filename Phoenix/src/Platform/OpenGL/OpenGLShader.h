#pragma once

#include "Phoenix/Renderer/Shader.h"

namespace Phoenix
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc, const std::string& name);
		OpenGLShader(const std::string& path, const std::string& name);
		OpenGLShader(const std::string& path);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;
		const std::string& GetName() const override { return name; }

		void SetUniformFloat(const std::string& name, float value);
		void SetUniformFloat2(const std::string& name, const glm::vec2& vector);
		void SetUniformFloat3(const std::string& name, const glm::vec3& vector);
		void SetUniformFloat4(const std::string& name, const glm::vec4& vector);
		void SetUniformMat3(const std::string& name, const glm::mat3& matrix);
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);
		void SetUniformInt(const std::string& name, int value);
		void SetUniformInt2(const std::string& name, const glm::i32vec2& vector);
		void SetUniformInt3(const std::string& name, const glm::i32vec3& vector);
		void SetUniformInt4(const std::string& name, const glm::i32vec4& vector);
	private:
		std::string ReadFile(const std::string& path);
		std::unordered_map<unsigned int, std::string> ParseFileContents(const std::string& contents);
		unsigned int GetOpenGLShaderType(const std::string& type);
		void Compile(const std::unordered_map<unsigned int, std::string>& source);
	private:
		unsigned int programID;
		std::string name;
	};
}