#pragma once
#include <Phoenix.h>
#include <Platform/OpenGL/OpenGLShader.h>

class AppLayer : public Phoenix::Layer
{
private:

	Ref<Phoenix::VertexArray> squareVA;
	Phoenix::ShaderLibrary shaderLibrary;
	Ref<Phoenix::Shader> flatColorShader;

	glm::vec3 color1 = { 0.2, 0.3, 0.8 };
	glm::vec3 color2 = { 0.8, 0.3, 0.2 };

	Phoenix::OrthographicCameraController cameraController{1280.f / 720.f};

	enum Patterns
	{
		Monochrome, Chessboard, Stripes, Gradient
	};
	int selectedPattern = Chessboard;
	int selectedColor = 0;
	bool patternDirection = false;
public:
	void OnAttach() override
	{
		float squareVertices[4 * 3]
		{
			-1.0,  -1.0,  0.0,
			 1.0,  -1.0,  0.0,
			 1.0,   1.0,  0.0,
			-1.0,   1.0,  0.0
		};

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		squareVA.reset(Phoenix::VertexArray::Create());

		Phoenix::BufferLayout squareVBlayout = {
			{Phoenix::Float3, "a_Position"}
		};

		Ref<Phoenix::VertexBuffer> squareVB;


		squareVB.reset(Phoenix::VertexBuffer::Create(squareVertices, squareVBlayout.GetStride(), 4));
		squareVB->SetLayout(squareVBlayout);

		squareVA->AddVertexBuffer(squareVB);

		Ref<Phoenix::IndexBuffer> squareIB;

		squareIB.reset(Phoenix::IndexBuffer::Create(squareIndices, 6));

		squareVA->AddIndexBuffer(squareIB);

		shaderLibrary.Load("assets/shaders/flatColor.shader");
		flatColorShader = shaderLibrary.Get("flatColor");
	}

	void OnImGuiRender() override
	{
		DrawSettingsWindow();
	}

	void OnDetach() override
	{

	}

	void OnUpdate(Phoenix::Timestep ts) override;
	void OnEvent(Phoenix::Event& e) override;

	
private:
    void DrawSettingsWindow();

};
