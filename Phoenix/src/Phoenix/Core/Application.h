#pragma once

#include "Window.h"
#include "Phoenix/Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Phoenix/ImGui/ImGuiLayer.h"
#include "Phoenix/Renderer/Shader.h"
#include "Phoenix/Renderer/Buffer.h"
#include "Phoenix/Renderer/VertexArray.h"
#include "Phoenix/Renderer/OrthographicCamera.h"

namespace Phoenix {
	class PH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void Close();

		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& event);
		bool OnWindowResize(WindowResizeEvent& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *instance; }
		inline Window& GetWindow() { return *window; }
	private:
		Scope<Window> window;

		ImGuiLayer* imGuiLayer;
		bool isRunning = true;
		bool isMinimized = false;
		LayerStack layerStack;

		float lastFrameTime = 0.0f;

	private:
		static Application* instance;
	};
	Application* CreateApplication();
}