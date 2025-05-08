#include "pch.h"
#include "RenderTest.h"

#include <Platform/OpenGL/OpenGLShader.h>

void RenderTest::OnAttach()
{
	float squareVertices[4 * 3]
	{
		-1.0,  -1.0,  0.0,
		 1.0,  -1.0,  0.0,
		 1.0,   1.0,  0.0,
		-1.0,   1.0,  0.0
	};
	unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

	squareVA = Phoenix::VertexArray::Create();

	Phoenix::BufferLayout squareVBlayout = {
			{Phoenix::Float3, "a_Position"}
	};

	Ref<Phoenix::VertexBuffer> squareVB;
	squareVB = Phoenix::VertexBuffer::Create(squareVertices, squareVBlayout.GetStride(), 4);
	squareVB->SetLayout(squareVBlayout);

	squareVA->AddVertexBuffer(squareVB);

	Ref<Phoenix::IndexBuffer> squareIB;

	squareIB = Phoenix::IndexBuffer::Create(squareIndices, 6);

	squareVA->AddIndexBuffer(squareIB);

	flatColorShader = Phoenix::Shader::Create("assets/shaders/flatColor.shader");
}
void RenderTest::OnDetach()
{
}

void RenderTest::OnUpdate(Phoenix::Timestep ts)
{
    cameraController.OnUpdate(ts);

    Phoenix::RenderCommand::ClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));
    Phoenix::Renderer::BeginScene(cameraController.GetCamera());

    std::dynamic_pointer_cast<Phoenix::OpenGLShader>(flatColorShader)->SetUniformFloat4("u_Color", squareColor);
    Phoenix::Renderer::Submit(flatColorShader, squareVA);
    

    Phoenix::Renderer::EndScene();
}

void RenderTest::OnEvent(Phoenix::Event& e)
{
    cameraController.OnEvent(e);
}

void RenderTest::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square color", glm::value_ptr(squareColor));
	ImGui::End();
}