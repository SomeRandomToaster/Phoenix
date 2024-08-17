#include "pch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Phoenix
{
	VertexBuffer* VertexBuffer::Create(const void* vertices, unsigned int vertexSize, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
		case None:
			PH_ASSERT(false, "RendererAPI::None now is not supported");
			return nullptr;
		case OpenGL:
			return new OpenGLVertexBuffer(vertices, vertexSize, count);
		default:
			PH_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(const unsigned int* indices, unsigned int count)
	{
		switch (Renderer::GetAPI())
		{
		case None:
			PH_ASSERT(false, "RendererAPI::None now is not supported");
			return nullptr;
		case OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		default:
			PH_ASSERT(false, "Unknown RendererAPI");
			return nullptr;
		}
	}
}