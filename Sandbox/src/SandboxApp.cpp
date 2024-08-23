#include "pch.h"
#include <Phoenix.h>

#include "imgui.h"
#include "glm/mat4x4.hpp"

class MyLayer : public Phoenix::Layer {
public:
	MyLayer() : Layer("MyLayer") {}

	void OnAttach() override 
	{
		float triangleVertices[3 * 9] = {
			-0.5, -0.5, 0.0,	0.0, 0.0,	1.0, 0.0, 0.0, 1.0,
			 0.5, -0.5, 0.0,    1.0, 0.0,	0.0, 1.0, 0.0, 1.0,
			 0.0,  0.5, 0.0,    0.0, 1.0,	0.0, 0.0, 1.0, 1.0
		};

		float squareVertices[4 * 3]
		{
			-0.5,  -0.5,  0.0,
			 0.5,  -0.5,  0.0,
			 0.5,   0.5,  0.0,
			-0.5,   0.5,  0.0
		};

		unsigned int triangleIndices[3] = { 0, 1, 2 };
		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		triangleVA.reset(Phoenix::VertexArray::Create());
		squareVA.reset(Phoenix::VertexArray::Create());

		Phoenix::BufferLayout triangleVBlayout = {
			{Phoenix::Float3, "a_Position"},
			{Phoenix::Float2, "a_TextureCoord"},
			{Phoenix::Float4, "a_Color"}
		};
		Phoenix::BufferLayout squareVBlayout = {
			{Phoenix::Float3, "a_Position"}
		};

		std::shared_ptr<Phoenix::VertexBuffer> triangleVB;
		std::shared_ptr<Phoenix::VertexBuffer> squareVB;

		triangleVB.reset(Phoenix::VertexBuffer::Create(triangleVertices, triangleVBlayout.GetStride(), 3));
		triangleVB->SetLayout(triangleVBlayout);

		squareVB.reset(Phoenix::VertexBuffer::Create(squareVertices, squareVBlayout.GetStride(), 4));
		squareVB->SetLayout(squareVBlayout);

		triangleVA->AddVertexBuffer(triangleVB);
		squareVA->AddVertexBuffer(squareVB);

		std::shared_ptr<Phoenix::IndexBuffer> triangleIB;
		std::shared_ptr<Phoenix::IndexBuffer> squareIB;

		triangleIB.reset(Phoenix::IndexBuffer::Create(triangleIndices, 3));
		squareIB.reset(Phoenix::IndexBuffer::Create(squareIndices, 6));

		triangleVA->AddIndexBuffer(triangleIB);
		squareVA->AddIndexBuffer(squareIB);

		std::string triangleVertexShaderSrc = R"(
			#version 330 core

			out vec3 v_Position;
			out vec4 v_Color;

			layout(location = 0) in vec3 a_Position;
			layout(location = 2) in vec4 a_Color;

			uniform mat4 u_ProjectionViewMatrix;	

			void main()
			{
				gl_Position = u_ProjectionViewMatrix * vec4(a_Position, 1.0f);
				v_Position = gl_Position.xyz;
				v_Color = a_Color;
			}; 
		)";
		std::string triangleFragmentShaderSrc = R"(
			#version 330 core

            layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
			}
		)";

		std::string squareVertexShaderSrc = R"(
			#version 330 core

			out vec3 v_Position;

			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ProjectionViewMatrix;	
			uniform mat4 u_Transform;		

			void main()
			{
				gl_Position = u_ProjectionViewMatrix * u_Transform * vec4(a_Position, 1.0f);
				v_Position = gl_Position.xyz;
			}; 
		)";
		std::string squareFragmentShaderSrc = R"(
			#version 330 core

            layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		triangleShader.reset(new Phoenix::Shader(triangleVertexShaderSrc, triangleFragmentShaderSrc));
		squareShader.reset(new Phoenix::Shader(squareVertexShaderSrc, squareFragmentShaderSrc));

		camera.reset(new Phoenix::OrthographicCamera(-1.6, 1.6, -0.9, 0.9, -1, 1));
	}
	void OnEvent(Phoenix::Event& event) override 
	{
		
	}

	void OnImGuiRender() override 
	{
		ImGui::Begin("Test window");

		ImGui::Text("Hello, World!");

		ImGui::End();

	}

	void OnUpdate(Phoenix::Timestep ts) override 
	{
		
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

		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				glm::mat4 squareTransform = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
				squareTransform = glm::translate(squareTransform, glm::vec3(1.1f * i, 1.1f * j, 0));

				Phoenix::Renderer::Submit(squareShader, squareVA, squareTransform);

			}
		}

		Phoenix::Renderer::EndScene();
	}
	private:
		std::shared_ptr<Phoenix::Camera> camera;
		std::shared_ptr<Phoenix::Shader> triangleShader;
		std::shared_ptr<Phoenix::Shader> squareShader;
		std::shared_ptr<Phoenix::VertexArray> triangleVA;
		std::shared_ptr<Phoenix::VertexArray> squareVA;

		float zRotation = 0;
		float cameraRotationSpeed = 180.f;
		float cameraMovementSpeed = 5.0f;
		float squareMovementSpeed = 5.0f;
		glm::vec3 cameraLocation = { 0, 0, 0 };
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