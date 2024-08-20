#include "pch.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Phoenix
{
	RendererAPI::API RendererAPI::api = RendererAPI::API::OpenGL;
}