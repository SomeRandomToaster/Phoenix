#pragma once

#include "Buffer.h"

namespace Phoenix
{
	class VertexArray
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& buffer) = 0;
		virtual void AddIndexBuffer(const Ref<IndexBuffer>& buffer) = 0;
		virtual ~VertexArray() {}

		static Ref<VertexArray> Create();
	};
}