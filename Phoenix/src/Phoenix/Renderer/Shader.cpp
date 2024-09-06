#include "pch.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Phoenix
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PH_CORE_ASSERT(false, "RendererAPI::None now is not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(vertexSrc, fragmentSrc);
		default:
			PH_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}

	Shader* Shader::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:
			PH_CORE_ASSERT(false, "RendererAPI::None now is not supported");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(path);
		default:
			PH_CORE_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}
}