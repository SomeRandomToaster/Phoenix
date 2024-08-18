#include "pch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "glad/glad.h"

namespace Phoenix
{
	unsigned int ShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
		case Phoenix::Float:	return sizeof(float);
		case Phoenix::Float2:	return sizeof(float) * 2;
		case Phoenix::Float3:	return sizeof(float) * 3;
		case Phoenix::Float4:	return sizeof(float) * 4;
		case Phoenix::Mat3:		return sizeof(float) * 3 * 3;
		case Phoenix::Mat4:		return sizeof(float) * 4 * 4;
		case Phoenix::Int:		return sizeof(int);
		case Phoenix::Int2:		return sizeof(int) * 2;
		case Phoenix::Int3:		return sizeof(int) * 3;
		case Phoenix::Int4:		return sizeof(int) * 4;
		default: PH_ASSERT(false, "Unknown ShaderDataType"); return 0;
		}
	}

	unsigned int ShaderDataTypeComponentCount(ShaderDataType type)
	{
		switch (type)
		{
		case Phoenix::Float:	return 1;
		case Phoenix::Float2:	return 2;
		case Phoenix::Float3:	return 3;
		case Phoenix::Float4:	return 4;
		case Phoenix::Mat3:		return 3 * 3;
		case Phoenix::Mat4:		return 4 * 4;
		case Phoenix::Int:		return 1;
		case Phoenix::Int2:		return 2;
		case Phoenix::Int3:		return 3;
		case Phoenix::Int4:		return 4;
		default: PH_ASSERT(false, "Unknown ShaderDataType"); return 0;
		}
	}

	unsigned int ShaderDataTypeToGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Phoenix::Float:	return GL_FLOAT;
		case Phoenix::Float2:	return GL_FLOAT;
		case Phoenix::Float3:	return GL_FLOAT;
		case Phoenix::Float4:	return GL_FLOAT;
		case Phoenix::Mat3:		return GL_FLOAT;
		case Phoenix::Mat4:		return GL_FLOAT;
		case Phoenix::Int:		return GL_INT;
		case Phoenix::Int2:		return GL_INT;
		case Phoenix::Int3:		return GL_INT;
		case Phoenix::Int4:		return GL_INT;
		default: PH_ASSERT(false, "Unknown ShaderDataType"); return 0;
		}
	}

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

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& list)
		: elements(list), stride(0)
	{
		unsigned int offset = 0;
		for (auto it = elements.begin(); it != elements.end(); it++)
		{
			it->offset = offset;
			offset += ShaderDataTypeSize(it->type);
			stride += ShaderDataTypeSize(it->type);
		}
	}
}