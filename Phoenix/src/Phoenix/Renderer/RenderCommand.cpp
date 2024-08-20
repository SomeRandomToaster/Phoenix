#include "pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h" 

namespace Phoenix
{
	RendererAPI* RenderCommand::rendererAPI = new OpenGLRendererAPI();
}