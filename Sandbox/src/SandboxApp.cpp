#include "pch.h"
#include <Phoenix.h>

#include "imgui.h"
#include "glm/mat4x4.hpp"

#include "Platform/OpenGL/OpenGLShader.h"

class MyLayer : public Phoenix::Layer {
public:
	MyLayer() : Layer("MyLayer") {}

	void OnAttach() override 
	{
		float squareVertices[4 * 5]
		{
			-1.0,  -1.0,  0.0, 0.0, 0.0,
			 1.0,  -1.0,  0.0, 1.0, 0.0,
			 1.0,   1.0,  0.0, 1.0, 1.0,
			-1.0,   1.0,  0.0, 0.0, 1.0
		};

		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		squareVA.reset(Phoenix::VertexArray::Create());

		Phoenix::BufferLayout squareVBlayout = {
			{Phoenix::Float3, "a_Position"},
			{Phoenix::Float2, "a_TexCoord"}
		};

		Ref<Phoenix::VertexBuffer> squareVB;


		squareVB.reset(Phoenix::VertexBuffer::Create(squareVertices, squareVBlayout.GetStride(), 4));
		squareVB->SetLayout(squareVBlayout);

		squareVA->AddVertexBuffer(squareVB);

		Ref<Phoenix::IndexBuffer> squareIB;

		squareIB.reset(Phoenix::IndexBuffer::Create(squareIndices, 6));

		squareVA->AddIndexBuffer(squareIB);

		solidColorShader.reset(Phoenix::Shader::Create("assets/shaders/flatColor.shader"));
		textureShader.reset(Phoenix::Shader::Create("assets/shaders/texture.shader"));
		rayTracingShader.reset(Phoenix::Shader::Create("assets/shaders/rayTracing.shader"));

		texture = Phoenix::Texture2D::Create("assets/textures/checkerboard.png");

		camera.reset(new Phoenix::OrthographicCamera(-1.6, 1.6, -0.9, 0.9, -1, 1));
	}
	void OnEvent(Phoenix::Event& event) override 
	{
		
	}

	void OnImGuiRender() override 
	{
		ImGui::Begin("Info");

		ImGui::Text("Last frame time: ");
		ImGui::Text(std::to_string(lastFrameTimeMillis).c_str());
		ImGui::Text("FPS: ");
		ImGui::Text(std::to_string(int(1e3 / lastFrameTimeMillis)).c_str());

		ImGui::End();
	}

	void OnUpdate(Phoenix::Timestep ts) override 
	{
		lastFrameTimeMillis = ts.GetMilliseconds();

		if (Phoenix::Input::IsKeyPressed(PH_KEY_A))
		{
			zRotation += cameraRotationSpeed * ts;
		}
		if (Phoenix::Input::IsKeyPressed(PH_KEY_D))
		{
			zRotation -= cameraRotationSpeed * ts;
		}

		if (Phoenix::Input::IsKeyPressed(PH_KEY_LEFT))
		{
			cameraLocation.x -= cameraMovementSpeed * ts;
		}
		if (Phoenix::Input::IsKeyPressed(PH_KEY_RIGHT))
		{
			cameraLocation.x += cameraMovementSpeed * ts;
		}
		if (Phoenix::Input::IsKeyPressed(PH_KEY_DOWN))
		{
			cameraLocation.y -= cameraMovementSpeed * ts;
		}
		if (Phoenix::Input::IsKeyPressed(PH_KEY_UP))
		{
			cameraLocation.y += cameraMovementSpeed * ts;
		}

		camera->SetRotation({ 0, 0, zRotation });
		camera->SetLocation(cameraLocation);
		

		Phoenix::RenderCommand::ClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));

		Phoenix::Renderer::BeginScene(camera);

		texture->Bind();
		std::dynamic_pointer_cast<Phoenix::OpenGLShader>(textureShader)->SetUniformInt("u_Texture", 0);
		Phoenix::Renderer::Submit(textureShader, squareVA);

		Phoenix::Renderer::EndScene();
	}
	private:
		Ref<Phoenix::Camera> camera;
		Ref<Phoenix::Shader> solidColorShader;
		Ref<Phoenix::Shader> textureShader;
		Ref<Phoenix::Shader> rayTracingShader;
		Ref<Phoenix::VertexArray> squareVA;
		Ref<Phoenix::Texture2D> texture;

		float zRotation = 0;
		float cameraRotationSpeed = 180.f;
		float cameraMovementSpeed = 5.0f;
		glm::vec3 cameraLocation = { 0, 0, 0 };

		float lastFrameTimeMillis;
};

class Sandbox : public Phoenix::Application {
public:
	Sandbox() {
		PushLayer(new MyLayer());
	}
	~Sandbox() {

	}
};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox;
}