#pragma once

namespace Phoenix
{
	enum ShaderDataType
	{
		Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4
	};

	unsigned int ShaderDataTypeSize(ShaderDataType type);
	unsigned int ShaderDataTypeComponentCount(ShaderDataType type);
	unsigned int ShaderDataTypeToGLBaseType(ShaderDataType type);

	class BufferElement
	{
	public:
		BufferElement(ShaderDataType type, const std::string& name, bool normalize = false)
			: type(type), name(name), normalize(normalize), offset(0), size(ShaderDataTypeSize(type)) {}

		ShaderDataType type;
		std::string name;
		bool normalize;
		unsigned int offset;
		unsigned int size;
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& list);
		unsigned int GetStride() { return stride; }

		const std::vector<BufferElement>::iterator begin() { return elements.begin(); }
		const std::vector<BufferElement>::iterator end() { return elements.end(); }
	private:
		std::vector<BufferElement> elements;
		unsigned int stride;
	};

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