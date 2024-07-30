#include "pch.h"
#include "WindowsWindow.h"

namespace Phoenix
{
	bool glfwInitialized = false;

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		data.width = props.width;
		data.height = props.height;
		data.title = props.title;

		PH_CORE_INFO("Creating window {0}, ({1}, {2})", data.title, data.width, data.height);

		if (!glfwInitialized) {
			int success = glfwInit();
			PH_CORE_ASSERT(success, "Couldn't initialize GLFW!");
			glfwInitialized = true;
		}
		window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		data.Vsync = enabled;
		glfwSwapInterval(enabled ? 1 : 0);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
}