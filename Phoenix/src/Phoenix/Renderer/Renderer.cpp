#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Phoenix
{
	Renderer::SceneData* Renderer::sceneData = new SceneData();

	void Renderer::Init()
	{
		RenderCommand::Init();
	}

	void Renderer::BeginScene(const Camera& camera)
	{
		sceneData->camera = &camera;
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& va, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_Transform", transform);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->SetUniformMat4("u_ProjectionViewMatrix", sceneData->camera->GetProjectionViewMatrix());
		RenderCommand::DrawIndexed(va);
	}
}