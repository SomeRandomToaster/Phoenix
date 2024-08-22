#pragma once

#include "glm/glm.hpp"

namespace Phoenix
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		
		void Bind();
		void Unbind();
		
		void SetUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int renderer;
	};
}