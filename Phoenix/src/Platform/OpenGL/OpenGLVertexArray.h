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

		const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; }
		const Ref<IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; }

		void AddVertexBuffer(const Ref<VertexBuffer>& buffer) override;
		void AddIndexBuffer(const Ref<IndexBuffer>& buffer) override;
		
		~OpenGLVertexArray();
	private:
		unsigned int rendererID;
		std::vector<Ref<VertexBuffer>> vertexBuffers;
		Ref<IndexBuffer> indexBuffer;
	};
}