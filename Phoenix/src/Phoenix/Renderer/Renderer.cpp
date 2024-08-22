#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Phoenix
{
	Renderer::SceneData* Renderer::sceneData = new SceneData();

	void Renderer::BeginScene(const std::shared_ptr<Camera>& camera)
	{
		sceneData->camera = camera;
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& va)
	{
		shader->Bind();
		shader->SetUniformMat4("u_ProjectionViewMatrix", sceneData->camera->GetProjectionViewMatrix());
		RenderCommand::DrawIndexed(va);
	}
}