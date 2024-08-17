#pragma once

namespace Phoenix
{
	class VertexBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual unsigned int GetCount() const = 0;
		virtual ~VertexBuffer() {}

		static VertexBuffer* Create(const void* vertices, unsigned int vertexSize, unsigned int count);
	};

	class IndexBuffer
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual unsigned int GetCount() const = 0;
		virtual ~IndexBuffer() {}

		static IndexBuffer* Create(const unsigned int* indices, unsigned int count);
	};
}