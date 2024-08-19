#include "pch.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Phoenix/Renderer/Renderer.h"

namespace Phoenix
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case None:
			PH_ASSERT(false, "RendererAPI::None now is not supported");
			return nullptr;
		case OpenGL:
			return new OpenGLVertexArray();
		default:
			PH_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}
}