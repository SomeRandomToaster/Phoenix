#pragma once

#include "VertexArray.h"

#include "glm/glm.hpp"
#include "RendererAPI.h"

namespace Phoenix 
{
	class RenderCommand
	{
	public:
		static void ClearColor(const glm::vec4& color) { rendererAPI->ClearColor(color); }
		static void DrawIndexed(const Ref<VertexArray>& va) { rendererAPI->DrawIndexed(va); }
	private:
		static RendererAPI* rendererAPI;
	};
}