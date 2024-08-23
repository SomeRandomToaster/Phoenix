#pragma once

#include "RendererAPI.h"
#include "VertexArray.h"

#include "Camera.h"
#include "Shader.h"

namespace Phoenix
{
	class Renderer
	{
	public:
		static void BeginScene(const std::shared_ptr<Camera>& camera);
		static void EndScene();
		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va, const glm::mat4& transform = glm::mat4(1.0f));

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			std::shared_ptr<Camera> camera;
		};
		static SceneData* sceneData;
	};
}