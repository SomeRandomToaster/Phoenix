#pragma once

#include "Buffer.h"

namespace Phoenix
{
	class VertexArray
	{
	public:
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;
		virtual ~VertexArray() {}

		static VertexArray* Create();
	};
}