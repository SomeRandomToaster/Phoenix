#pragma once

namespace Phoenix
{
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		void Bind();
		void Unbind();
	private:
		unsigned int renderer;
	};
}