#include "pch.h"
#include "OpenGLShader.h"

#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"

namespace Phoenix
{
	OpenGLShader::OpenGLShader(const std::string& path)
	{
		std::string fileContents = ReadFile(path);
		std::unordered_map<GLenum, std::string> source = ParseFileContents(fileContents);
		Compile(source);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		std::unordered_map<GLenum, std::string> source;
		source[GL_VERTEX_SHADER] = vertexSrc;
		source[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(source);

	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::string contents;
		std::ifstream file(path, std::ios_base::binary);
		PH_CORE_ASSERT(file, "Couldn't open file '{0}'", path.c_str());
		file.seekg(0, std::ios::end);
		int size = file.tellg();
		file.seekg(0, std::ios::beg);
		contents.resize(size);
		file.read(contents.data(), size);
		return contents;
	}

	std::unordered_map<unsigned int, std::string> OpenGLShader::ParseFileContents(const std::string& contents)
	{
		const std::string TYPE_TOKEN = "#type";
		int searchPos = 0;
		int tokenPos;

		std::unordered_map<unsigned int, std::string> source;

		while ((tokenPos = contents.find(TYPE_TOKEN, searchPos)) != std::string::npos)
		{
			int typePos = tokenPos + TYPE_TOKEN.length();
			
			while (std::isspace(contents[typePos])) 
			{
				typePos++;
			}

			int typeLength = 0;
			while (!std::isspace(contents[typePos + typeLength])) 
			{
				typeLength++;
			}
			
			std::string typeStr = contents.substr(typePos, typeLength);
			unsigned int type = GetOpenGLShaderType(typeStr);

			int srcPos = typePos + typeLength;
			int nextTokenPos;
			if ((nextTokenPos = contents.find(TYPE_TOKEN, srcPos)) != std::string::npos) 
			{
				source.insert({ type, contents.substr(srcPos, nextTokenPos - srcPos) });
			} 
			else 
			{
				source.insert({ type, contents.substr(srcPos, contents.length() - srcPos)});
			}

			searchPos = tokenPos + 1;
		}
		
		return source;
	}

	unsigned int OpenGLShader::GetOpenGLShaderType(const std::string& type)
	{
		if (type == "vertex")
			return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel")
			return GL_FRAGMENT_SHADER;
		PH_CORE_ASSERT(0, "Unknown shader type: '{0}'", type);
		return 0;
	}

	void OpenGLShader::Compile(const std::unordered_map<unsigned int, std::string>& source)
	{
		std::vector<unsigned int> shaderIDs;
		
		for (const auto& elem : source) 
		{
			unsigned int type = elem.first;

			unsigned int id = glCreateShader(type);
			shaderIDs.push_back(id);

			const char* src = elem.second.c_str();

			glShaderSource(id, 1, &src, 0);
			glCompileShader(id);

			int isCompiled = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE)
			{
				int maxLength = 0;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

				char* infoLog = new char[maxLength];
				glGetShaderInfoLog(id, maxLength, &maxLength, infoLog);

				for (int i = 0; i < shaderIDs.size(); i++) {
					glDeleteShader(shaderIDs[i]);
				}

				PH_CORE_ERROR("Shader compilation error : {0}", infoLog);
				delete[] infoLog;
				PH_CORE_ASSERT(false, "Terminating the application");

				return;
			}
		}

		programID = glCreateProgram();

		for (int i = 0; i < shaderIDs.size(); i++) {
			glAttachShader(programID, shaderIDs[i]);
		}
		
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

			for (int i = 0; i < shaderIDs.size(); i++) {
				glDeleteShader(shaderIDs[i]);
			}

			PH_CORE_ERROR("Shader program linking error: {0}", infoLog);
			delete[] infoLog;
			PH_CORE_ASSERT(false, "Terminating the application");
			return;
		}

		for (int i = 0; i < shaderIDs.size(); i++) {
			glDetachShader(programID, shaderIDs[i]);
		}
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