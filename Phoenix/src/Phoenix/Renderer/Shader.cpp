#include "pch.h"
#include "Shader.h"

#include "glad/glad.h"

namespace Phoenix
{
	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
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

		renderer = glCreateProgram();

		glAttachShader(renderer, vertexShader);
		glAttachShader(renderer, fragmentShader);

		glLinkProgram(renderer);

		int isLinked = 0;
		glGetProgramiv(renderer, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(renderer, GL_INFO_LOG_LENGTH, &maxLength);

			char* infoLog = new char[maxLength];
			glGetProgramInfoLog(renderer, maxLength, &maxLength, infoLog);

			glDeleteProgram(renderer);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			PH_CORE_ERROR("Shader program linking error: {0}", infoLog);
			delete[] infoLog;
			PH_CORE_ASSERT(false, "Terminating the application");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(renderer, vertexShader);
		glDetachShader(renderer, fragmentShader);
	}

	void Shader::Bind()
	{
		glUseProgram(renderer);
	}

	void Shader::Unbind()
	{
		glUseProgram(0);
	}
}