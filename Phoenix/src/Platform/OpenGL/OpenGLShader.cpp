#include "pch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Phoenix
{
	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const char* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		glCompileShader(vertexShader);

		int isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			char* infoLog = new char[maxLength];
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, infoLog);

			glDeleteShader(vertexShader);

			PH_CORE_ERROR("Vertex shader compilation error: {0}", infoLog);
			delete[] infoLog;
			PH_CORE_ASSERT(false, "Terminating the application");

			return;
		}

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			int maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			char* infoLog = new char[maxLength];
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, infoLog);

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			PH_CORE_ERROR("Fragment shader compilation error: {0}", infoLog);
			delete[] infoLog;
			PH_CORE_ASSERT(false, "Terminating the application");

			return;
		}

		programID = glCreateProgram();

		glAttachShader(programID, vertexShader);
		glAttachShader(programID, fragmentShader);

		glLinkProgram(programID);

		int isLinked = 0;
		glGetProgramiv(programID, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

			char* infoLog = new char[maxLength];
			glGetProgramInfoLog(programID, maxLength, &maxLength, infoLog);

			glDeleteProgram(programID);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			PH_CORE_ERROR("Shader program linking error: {0}", infoLog);
			delete[] infoLog;
			PH_CORE_ASSERT(false, "Terminating the application");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(programID, vertexShader);
		glDetachShader(programID, fragmentShader);
	}

	void OpenGLShader::Bind() const
	{
		glUseProgram(programID);
	}

	void OpenGLShader::Unbind() const
	{
		glUseProgram(0);
	}

	
	void OpenGLShader::SetUniformFloat(const std::string& name, float value)
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::SetUniformFloat2(const std::string& name, const glm::vec2& vector)
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform2f(location, vector.x, vector.y);
	}

	void OpenGLShader::SetUniformFloat3(const std::string& name, const glm::vec3& vector)
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::SetUniformFloat4(const std::string& name, const glm::vec4& vector)
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
	}

	void OpenGLShader::SetUniformMat3(const std::string& name, const glm::mat3& matrix)
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniformInt2(const std::string& name, const glm::i32vec2& vector)
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform2i(location, vector.x, vector.y);
	}

	void OpenGLShader::SetUniformInt3(const std::string& name, const glm::i32vec3& vector)
	{;
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform3i(location, vector.x, vector.y, vector.z);
	}

	void OpenGLShader::SetUniformInt4(const std::string& name, const glm::i32vec4& vector)
	{
		int location = glGetUniformLocation(programID, name.c_str());
		glUniform4i(location, vector.x, vector.y, vector.z, vector.w);
	}

	OpenGLShader::~OpenGLShader()
	{
		glDeleteProgram(programID);
	}
}