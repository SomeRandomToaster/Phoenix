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
		float squareVertices[4 * 3]
		{
			-0.5,  -0.5,  0.0,
			 0.5,  -0.5,  0.0,
			 0.5,   0.5,  0.0,
			-0.5,   0.5,  0.0
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

		solidColorShader.reset(Phoenix::Shader::Create(solidColorVertexShaderSrc, solidColorFragmentShaderSrc));

		camera.reset(new Phoenix::OrthographicCamera(-1.6, 1.6, -0.9, 0.9, -1, 1));
	}
	void OnEvent(Phoenix::Event& event) override 
	{
		
	}

	void OnImGuiRender() override 
	{
		ImGui::Begin("Settings");
		
		static const char* items[] =
		{
			"Monochrome",
			"Chess board",
			"Stripes",
			"Gradient"
		};

		ImGui::Combo("Pattern", &selectedPattern, items, 4);


		switch (selectedPattern)
		{
		case Monochrome:
			ImGui::Text("Select color");
			ImGui::RadioButton("Color 1", &selectedColor, 0); ImGui::SameLine();
			ImGui::RadioButton("Color 2", &selectedColor, 1);
			break;
		case Stripes:
		case Gradient:
			ImGui::Checkbox("Change direction", &patternDirection);
			break;
		default:
			break;
		}

		ImGui::Text("Colors");
		ImGui::ColorPicker3("Color1", glm::value_ptr(color1));
		ImGui::ColorPicker3("Color2", glm::value_ptr(color2));

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

				solidColorShader->Bind();

				switch (selectedPattern)
				{
				case Monochrome:
					if(selectedColor)
						std::dynamic_pointer_cast<Phoenix::OpenGLShader>(solidColorShader)->SetUniformFloat3("u_Color", color2);
					else
						std::dynamic_pointer_cast<Phoenix::OpenGLShader>(solidColorShader)->SetUniformFloat3("u_Color", color1);
					break;
				case Chessboard:
					std::dynamic_pointer_cast<Phoenix::OpenGLShader>(solidColorShader)->SetUniformFloat3("u_Color", (i + j) % 2 ? color1 : color2);
					break;
				case Stripes:
					if(patternDirection)
						std::dynamic_pointer_cast<Phoenix::OpenGLShader>(solidColorShader)->SetUniformFloat3("u_Color", j % 2 ? color1 : color2);
					else
						std::dynamic_pointer_cast<Phoenix::OpenGLShader>(solidColorShader)->SetUniformFloat3("u_Color", i % 2 ? color1 : color2);
					break;
				case Gradient:
					float t;
					if (patternDirection)
						t = j / 10.0f;
					else
						t = i / 10.0f;
					std::dynamic_pointer_cast<Phoenix::OpenGLShader>(solidColorShader)->SetUniformFloat3("u_Color", t * color1 + (1 - t) * color2);
					break;
				}

				//std::dynamic_pointer_cast<Phoenix::OpenGLShader>(solidColorShader)->SetUniformFloat3("u_Color", (i + j) % 2 ? color1 : color2);
				Phoenix::Renderer::Submit(solidColorShader, squareVA, squareTransform);

			}
		}

		Phoenix::Renderer::EndScene();
	}
	private:
		Ref<Phoenix::Camera> camera;
		Ref<Phoenix::Shader> solidColorShader;
		Ref<Phoenix::VertexArray> squareVA;

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