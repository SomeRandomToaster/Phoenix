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

		float vertices[3 * 9] = {
			-0.5, -0.5, 0.0,	0.0, 0.0,	1.0, 0.0, 0.0, 1.0,
			 0.5, -0.5, 0.0,    1.0, 0.0,	0.0, 1.0, 0.0, 1.0,
			 0.0,  0.5, 0.0,    0.0, 1.0,	0.0, 0.0, 1.0, 1.0
		};

		unsigned int indices[3] = { 0, 1, 2 };

		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		BufferLayout layout = {
			{Float3, "a_Position"},
			{Float2, "a_TextureCoord"},
			{Float4, "a_Color"}
		};

		vertexBuffer.reset(VertexBuffer::Create(vertices, layout.GetStride(), 3));

		int index = 0;
		for (auto it = layout.begin(); it != layout.end(); it++)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, ShaderDataTypeComponentCount(it->type), ShaderDataTypeToGLBaseType(it->type),
				it->normalize, layout.GetStride(), (void*)it->offset);
			index++;
		}

		indexBuffer.reset(IndexBuffer::Create(indices, 3));

		std::string vertexSrc = R"(
			#version 330 core

			out vec3 v_Position;
			out vec4 v_Color;
			layout(location = 0) in vec3 a_Position;
			layout(location = 2) in vec4 a_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(v_Position, 1.0f);
			}; 
		)";
		std::string fragmentSrc = R"(
			#version 330 core

            layout(location = 0) out vec4 color;
			
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = v_Color;
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