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
			-0.5,  -0.5,  0.0, 0.0, 0.0,
			 0.5,  -0.5,  0.0, 1.0, 0.0,
			 0.5,   0.5,  0.0, 1.0, 1.0,
			-0.5,   0.5,  0.0, 0.0, 1.0
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

		std::string solidColorVertexShaderSrc = R"(
			#version 330 core

			out vec3 v_Position;
			out vec3 v_Color;

			layout(location = 0) in vec3 a_Position;
			
			uniform mat4 u_ProjectionViewMatrix;	
			uniform mat4 u_Transform;		

			void main()
			{
				gl_Position = u_ProjectionViewMatrix * u_Transform * vec4(a_Position, 1.0f);
				v_Position = gl_Position.xyz;
			}; 
		)";
		std::string solidColorFragmentShaderSrc = R"(
			#version 330 core

            layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(u_Color, 1.0);
			}
		)";

		std::string textureVertexShaderSrc = R"(
			#version 330 core

			out vec3 v_Position;
			out vec2 v_TexCoord;

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec2 a_TexCoord;
			
			uniform mat4 u_ProjectionViewMatrix;	
			uniform mat4 u_Transform;		

			void main()
			{
				gl_Position = u_ProjectionViewMatrix * u_Transform * vec4(a_Position, 1.0f);
				v_Position = gl_Position.xyz;
				v_TexCoord = a_TexCoord;
			}; 
		)";
		std::string textureFragmentShaderSrc = R"(
			#version 330 core

            layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec2 v_TexCoord;

			uniform sampler2D u_Texture;

			void main()
			{
				color = texture(u_Texture, v_TexCoord);
			}
		)";

		texture = Phoenix::Texture2D::Create("assets/textures/checkerboard.png");
		lunaTexture = Phoenix::Texture2D::Create("assets/textures/luna.png");

		solidColorShader.reset(Phoenix::Shader::Create(solidColorVertexShaderSrc, solidColorFragmentShaderSrc));
		textureShader.reset(Phoenix::Shader::Create(textureVertexShaderSrc, textureFragmentShaderSrc));

		camera.reset(new Phoenix::OrthographicCamera(-1.6, 1.6, -0.9, 0.9, -1, 1));
	}
	void OnEvent(Phoenix::Event& event) override 
	{
		
	}

	void OnImGuiRender() override 
	{

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

		std::dynamic_pointer_cast<Phoenix::OpenGLShader>(textureShader)->SetUniformInt("u_Texture", 0);
		texture->Bind();
		Phoenix::Renderer::Submit(textureShader, squareVA);
		lunaTexture->Bind();
		Phoenix::Renderer::Submit(textureShader, squareVA);

		Phoenix::Renderer::EndScene();
	}
	private:
		Ref<Phoenix::Camera> camera;
		Ref<Phoenix::Shader> solidColorShader;
		Ref<Phoenix::Shader> textureShader;
		Ref<Phoenix::VertexArray> squareVA;

		float zRotation = 0;
		float cameraRotationSpeed = 180.f;
		float cameraMovementSpeed = 5.0f;
		glm::vec3 cameraLocation = { 0, 0, 0 };
		
		Ref<Phoenix::Texture2D> texture;
		Ref<Phoenix::Texture2D> lunaTexture;
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