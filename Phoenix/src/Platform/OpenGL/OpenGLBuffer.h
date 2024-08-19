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

		virtual const BufferLayout& GetLayout() const override { return layout; }
		virtual void SetLayout(const BufferLayout& layout) override { this->layout = layout; }

		inline unsigned int GetCount() const override { return count; }
	private:
		unsigned int bufferID;
		unsigned int vertexSize;
		unsigned int count;
		BufferLayout layout;
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