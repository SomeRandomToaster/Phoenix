#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Phoenix/ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/OrthographicCamera.h"

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