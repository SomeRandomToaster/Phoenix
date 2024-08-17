#pragma once

namespace Phoenix
{
	enum RendererAPI
	{
		None = 0,
		OpenGL = 1
	};

	class Renderer
	{
	public:
		static inline RendererAPI GetAPI() { return rendererAPI; }
	private:
		static RendererAPI rendererAPI;
	};
}