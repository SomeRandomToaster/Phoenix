#pragma once

#include "Phoenix/Window.h"
#include "Phoenix/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Phoenix 
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return data.width; }
		inline unsigned int GetHeight() const override { return data.height; }

		inline void SetEventCallback(const EventCallbackFunction& callback) override { data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override { return data.Vsync; }
		inline void* GetNativeWindow() const override { return window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* window;
		GraphicsContext* context;
		struct WindowData 
		{
			std::string title;
			unsigned int width, height;
			bool Vsync;
			EventCallbackFunction eventCallback;
		} data;

	};
}