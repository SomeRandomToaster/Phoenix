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

		float triangleVertices[3 * 9] = {
			-0.5, -0.5, 0.0,	0.0, 0.0,	1.0, 0.0, 0.0, 1.0,
			 0.5, -0.5, 0.0,    1.0, 0.0,	0.0, 1.0, 0.0, 1.0,
			 0.0,  0.5, 0.0,    0.0, 1.0,	0.0, 0.0, 1.0, 1.0
		};

		float squareVertices[4 * 3]
		{
			0.25, 0.0,  0.0,
			0.5,  0.0,  0.0,
			0.5,  0.5,  0.0,
			0.25, 0.5,  0.0
		};

		unsigned int triangleIndices[3] = { 0, 1, 2 };
		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

		triangleVA.reset(VertexArray::Create());
		squareVA.reset(VertexArray::Create());

		BufferLayout triangleVBlayout = {
			{Float3, "a_Position"},
			{Float2, "a_TextureCoord"},
			{Float4, "a_Color"}
		};
		BufferLayout squareVBlayout = {
			{Float3, "a_Position"}
		};

		std::shared_ptr<VertexBuffer> triangleVB;
		std::shared_ptr<VertexBuffer> squareVB;

		triangleVB.reset(VertexBuffer::Create(triangleVertices, triangleVBlayout.GetStride(), 3));
		triangleVB->SetLayout(triangleVBlayout);
		
		squareVB.reset(VertexBuffer::Create(squareVertices, squareVBlayout.GetStride(), 4));
		squareVB->SetLayout(squareVBlayout);
		
		triangleVA->AddVertexBuffer(triangleVB);
		squareVA->AddVertexBuffer(squareVB);

		std::shared_ptr<IndexBuffer> triangleIB;
		std::shared_ptr<IndexBuffer> squareIB;

		triangleIB.reset(IndexBuffer::Create(triangleIndices, 3));
		squareIB.reset(IndexBuffer::Create(squareIndices, 6));

		triangleVA->AddIndexBuffer(triangleIB);
		squareVA->AddIndexBuffer(squareIB);

		std::string triangleVertexShaderSrc = R"(
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

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(v_Position, 1.0f);
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

		triangleShader.reset(new Shader(triangleVertexShaderSrc, triangleFragmentShaderSrc));
		squareShader.reset(new Shader(squareVertexShaderSrc, squareFragmentShaderSrc));
	}
	Application::~Application() {
		
	}
	void Application::Run() {

		while (isRunning) 
		{
			glClearColor(0.1, 0.1, 0.1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			triangleVA->Bind();
			triangleShader->Bind();
			glDrawElements(GL_TRIANGLES, triangleVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			squareVA->Bind();
			squareShader->Bind();
			glDrawElements(GL_TRIANGLES, squareVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

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