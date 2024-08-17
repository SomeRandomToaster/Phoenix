#pragma once

#include "Phoenix/Renderer/Buffer.h"

namespace Phoenix
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(const void* vertices, unsigned int vertexSize, unsigned int count);
		~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;
		inline unsigned int GetCount() const override { return count; }
	private:
		unsigned int bufferID;
		unsigned int vertexSize;
		unsigned int count;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const unsigned int* indices, unsigned int count);
		~OpenGLIndexBuffer();

		void Bind() const override;
		void Unbind() const override;
		inline unsigned int GetCount() const override { return count; }
	private:
		unsigned int bufferID;
		unsigned int count;
	};
}