#include "pch.h"
#include "WindowsWindow.h"

#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Events/KeyEvent.h"
#include "Phoenix/Events/MouseEvent.h"

#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace Phoenix
{
	bool glfwInitialized = false;

	static void GLFWerrorCallback(int error, const char* description)
	{
		PH_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

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

			glfwSetErrorCallback(GLFWerrorCallback);
			glfwInitialized = true;
		}
		window = glfwCreateWindow(data.width, data.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);

		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PH_CORE_ASSERT(success, "Couldn't initialize GLAD!");

		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);


		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowResizeEvent event(width, height);

				data.width = width;
				data.height = height;
				data.eventCallback(event);
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;

				data.eventCallback(event);
			});

		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) 
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.eventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.eventCallback(event);
						break;
					}
				}
			});

			glfwSetCharCallback(window, [](GLFWwindow* window, unsigned int c) 
				{
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

					KeyTypedEvent event(c);
					data.eventCallback(event);
				});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.eventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.eventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.eventCallback(event);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.eventCallback(event);
			});
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