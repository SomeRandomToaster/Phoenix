#pragma once
#include <Phoenix.h>
#include <Platform/OpenGL/OpenGLShader.h>

class AppLayer : public Phoenix::Layer
{
private:
	unsigned viewportResolutionX = 1120;
	unsigned viewportResolutionY = 630;

	Ref<Phoenix::Framebuffer> viewportFramebuffer;
	Ref<Phoenix::VertexArray> squareVA;
	Phoenix::ShaderLibrary shaderLibrary;
	Ref<Phoenix::Shader> flatColorShader;
	Ref<Phoenix::OrthographicCamera> camera;

	float zRotation = 0;
	float cameraRotationSpeed = 180.f;
	float cameraMovementSpeed = 5.0f;
	float squareMovementSpeed = 5.0f;
	glm::vec3 cameraLocation = { 0, 0, 0 };
	glm::vec3 color1 = { 0.2, 0.3, 0.8 };
	glm::vec3 color2 = { 0.8, 0.3, 0.2 };


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
		Phoenix::FramebufferProps props;
		props.Width = 1280;
		props.Height = 720;
		viewportFramebuffer = Phoenix::Framebuffer::Create(props);

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

		camera.reset(new Phoenix::OrthographicCamera(-1.6, 1.6, -0.9, 0.9, -1, 1));
	}

	void OnImGuiRender() override
	{
        SetupDockspace();
        DrawMenuBar();
		DrawSettingsWindow();
		DrawViewportWindow();

		ImGui::End();
	}

	void OnDetach() override
	{

	}

	void OnUpdate(Phoenix::Timestep ts) override;

	
private:
    void SetupDockspace();
    void DrawMenuBar();
    void DrawSettingsWindow();
	void DrawViewportWindow();

};
