#include "pch.h"
#include "Application.h"


#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Phoenix {


	Application* Application::instance = nullptr;

	Application::Application() {
		PH_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
		imGuiLayer = new ImGuiLayer();
		layerStack.PushOverlay(imGuiLayer);

		float vertices[3 * 3] = {
			-0.5, -0.5, 0.0,
			0.5, -0.5, 0.0,
			0.0, 0.5, 0.0
		};

		unsigned int indices[3] = { 0, 1, 2 };

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(int), indices, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
			#version 330 core

			out vec3 v_Position;
			layout(location = 0) in vec3 a_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(v_Position, 1.0f);
			}; 
		)";
		std::string fragmentSrc = R"(
			#version 330 core

            layout(location = 0) out vec4 color;
			
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));
		shader->Bind();
	}
	Application::~Application() {
		
	}
	void Application::Run() {

		while (isRunning) 
		{
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindVertexArray(vertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layerStack) {
				layer->OnUpdate();
			}

			imGuiLayer->Begin();

			for(Layer* layer : layerStack) {
				layer->OnImGuiRender();
			}

			imGuiLayer->End();

			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event) 
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));

		for (auto it = layerStack.end(); it != layerStack.begin();)
		{
			(*(--it))->OnEvent(event);
			if (event.Handled) {
				break;
			}
		}

		//PH_CORE_TRACE(event.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& event) 
	{
		isRunning = false;
		return true;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
	}
}