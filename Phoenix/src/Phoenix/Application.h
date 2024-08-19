#pragma once

#include "Window.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"
#include "Phoenix/ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

namespace Phoenix {
	class PH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& event);
		bool OnWindowClose(WindowCloseEvent& event);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *instance; }
		inline Window& GetWindow() { return *window; }
	private:
		std::unique_ptr<Window> window;

		std::unique_ptr<Shader> triangleShader;
		std::unique_ptr<Shader> squareShader;
		std::shared_ptr<VertexArray> triangleVA;
		std::shared_ptr<VertexArray> squareVA;

		ImGuiLayer* imGuiLayer;
		bool isRunning = true;
		LayerStack layerStack;

	private:
		static Application* instance;
	};
	Application* CreateApplication();
}