#include "pch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "Phoenix/Application.h"

namespace Phoenix 
{
	Input* Input::instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(unsigned int keycode)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(unsigned int button)
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	float WindowsInput::GetMousePosXImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto [x, y] = GetMousePosImpl();
		return x;
	}
	float WindowsInput::GetMousePosYImpl()
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto [x, y] = GetMousePosImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl()
	{
		double x, y;
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		glfwGetCursorPos(window, &x, &y);
		return { (float)x, float(y) };
	}
}