#include "pch.h"
#include "Application.h"
 
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Phoenix {

#define BIND_EVENT_FUNCTION(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::instance = nullptr;

	Application::Application() {
		PH_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;
		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT_FUNCTION(OnEvent));

	}
	Application::~Application() {
		
	}
	void Application::Run() {

		while (isRunning) 
		{
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack) {
				layer->OnUpdate();
			}

			window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& event) 
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(OnWindowClose));

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