#include "pch.h"
#include "Renderer.h"

#include "RenderCommand.h"

namespace Phoenix
{
	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& va)
	{
		RenderCommand::DrawIndexed(va);
	}
}