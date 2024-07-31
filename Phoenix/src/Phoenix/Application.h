#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

namespace Phoenix {
	class PH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *instance; }
		inline Window& GetWindow() { return *window; }
	private:
		std::unique_ptr<Window> window;
		bool isRunning = true;
		LayerStack layerStack;
	private:
		static Application* instance;
	};
	Application* CreateApplication();
}