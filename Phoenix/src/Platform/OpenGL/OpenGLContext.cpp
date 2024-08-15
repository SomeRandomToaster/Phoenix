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

		PH_CORE_INFO("OpenGL info:");
		PH_CORE_INFO("    Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		PH_CORE_INFO("    Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		PH_CORE_INFO("    Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle);
	}
}