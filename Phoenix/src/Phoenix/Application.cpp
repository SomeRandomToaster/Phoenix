#include "pch.h"
#include "Application.h"

#include "GLFW/glfw3.h"

namespace Phoenix {
	Application::Application() {
		window = std::unique_ptr<Window>(Window::Create());
	}
	Application::~Application() {
		
	}
	void Application::Run() {

		while (isRunning) 
		{
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->OnUpdate();
		}
	}
}