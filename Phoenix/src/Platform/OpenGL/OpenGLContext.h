#pragma once

#include "Phoenix/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Phoenix
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* windowHandle;
	};
}