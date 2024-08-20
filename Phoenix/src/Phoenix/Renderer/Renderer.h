#pragma once

#include "RendererAPI.h"
#include "VertexArray.h"

namespace Phoenix
{
	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();
		static void Submit(const std::shared_ptr<VertexArray>& va);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}