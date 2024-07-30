#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"

namespace Phoenix {
	class PH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& event);
	private:
		std::unique_ptr<Window> window;
		bool isRunning = true;
	};
	Application* CreateApplication();
}