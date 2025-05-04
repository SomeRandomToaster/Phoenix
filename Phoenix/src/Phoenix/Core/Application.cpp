#include "pch.h"
#include "Application.h"

#include "Phoenix/Renderer/Renderer.h"
#include "Phoenix/Renderer/RenderCommand.h"
#include "Phoenix/Core/Timestep.h"

#include "GLFW/glfw3.h"

namespace Phoenix {


	Application* Application::instance = nullptr;

	Application::Application() {
		PH_CORE_ASSERT(!instance, "Application already exists!");
		instance = this;
		window = Scope<Window>(Window::Create());
		window->SetEventCallback(PH_BIND_EVENT_FUNCTION(Application::OnEvent));
		imGuiLayer = new ImGuiLayer();
		layerStack.PushOverlay(imGuiLayer);

		Renderer::Init();
	}
	Application::~Application() {
		
	}
	void Application::Run() {

		while (isRunning) 
		{
			float time = glfwGetTime();
			Timestep deltaTime = time - lastFrameTime;

			if (!isMinimized) {
				for (Layer* layer : layerStack) {
					layer->OnUpdate(deltaTime);
				}
			}

			imGuiLayer->Begin();

			for(Layer* layer : layerStack) {
				layer->OnImGuiRender();
			}

			imGuiLayer->End();

			window->OnUpdate();

			lastFrameTime = time;
		}
	}

	void Application::OnEvent(Event& event) 
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<WindowCloseEvent>(PH_BIND_EVENT_FUNCTION(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(PH_BIND_EVENT_FUNCTION(Application::OnWindowResize));

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

	bool Application::OnWindowResize(WindowResizeEvent& event)
	{
		if(event.GetWidth() == 0 || event.GetHeight() == 0) {
			isMinimized = true;
		}
		else {
			isMinimized = false;
		}
		Renderer::OnWindowResize(event.GetWidth(), event.GetHeight());
		return false;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* layer)
	{
		layerStack.PushOverlay(layer);
	}

	void Application::Close()
	{
		isRunning = false;
	}
}

