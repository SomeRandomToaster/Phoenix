#include "pch.h"
#include "OpenGLVertexArray.h"

#include "glad/glad.h"

namespace Phoenix
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &rendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(rendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& buffer)
	{
		PH_ASSERT(buffer->GetLayout().GetElements().size(), "Vertex buffer has no layout");

		glBindVertexArray(rendererID);
		buffer->Bind();

		int index = 0;
		BufferLayout layout = buffer->GetLayout();
		for (const auto& elem : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, ShaderDataTypeComponentCount(elem.type), ShaderDataTypeToGLBaseType(elem.type),
				elem.normalize ? GL_TRUE : GL_FALSE, layout.GetStride(), (void*)elem.offset);
			index++;
		}

		vertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::AddIndexBuffer(const Ref<IndexBuffer>& buffer)
	{
		glBindVertexArray(rendererID);
		buffer->Bind();
		indexBuffer = buffer;
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &rendererID);
	}
}