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
		static void Init();
		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& va, const glm::mat4& transform = glm::mat4(1.0f));
		static void OnWindowResize(unsigned width, unsigned height);

		static inline RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		struct SceneData
		{
			const Camera* camera;
		};
		static SceneData* sceneData;
	};
}