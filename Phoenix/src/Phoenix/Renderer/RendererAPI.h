#pragma once

#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Phoenix
{
	class RendererAPI
	{
	public:
		enum API
		{
			None = 0,
			OpenGL = 1
		};

		virtual void ClearColor(const glm::vec4& color) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& va) = 0;

		static inline API GetAPI() { return api; }
	private:
		static API api;
	};
}