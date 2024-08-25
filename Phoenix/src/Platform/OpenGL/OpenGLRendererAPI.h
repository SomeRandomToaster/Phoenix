#pragma once

#include "Phoenix/Renderer/RendererAPI.h"

namespace Phoenix
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void ClearColor(const glm::vec4& color) override;
		void DrawIndexed(const Ref<VertexArray>& va) override;
	};
}