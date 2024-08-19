#pragma once

#include "Phoenix/Renderer/VertexArray.h"

namespace Phoenix
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();

		void Bind() const override;
		void Unbind() const override;

		const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; }
		const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; }

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
		void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;
		
		~OpenGLVertexArray();
	private:
		unsigned int rendererID;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
	};
}