#pragma once

#include "VertexArray.h"

#include "glm/glm.hpp"
#include "RendererAPI.h"

namespace Phoenix 
{
	class RenderCommand
	{
	public:
		static void Init() { rendererAPI->Init(); }
		static void ClearColor(const glm::vec4& color) { rendererAPI->ClearColor(color); }
		static void DrawIndexed(const Ref<VertexArray>& va) { rendererAPI->DrawIndexed(va); }
		static void SetViewport(unsigned x, unsigned y, unsigned width, unsigned height) { rendererAPI->SetViewport(x, y, width, height); }
	private:
		static RendererAPI* rendererAPI;
	};
}