#include "pch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace Phoenix
{
	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: windowHandle(window)
	{

	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle);

		int success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PH_CORE_ASSERT(success, "Couldn't initialize GLAD!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}