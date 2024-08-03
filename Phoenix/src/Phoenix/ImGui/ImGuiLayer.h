#pragma once

#include "Phoenix/Layer.h"
#include "Phoenix/Events/ApplicationEvent.h"
#include "Phoenix/Events/KeyEvent.h"
#include "Phoenix/Events/MouseEvent.h"

enum ImGuiKey;

namespace Phoenix
{
	class PH_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();

		void OnUpdate() override;
		void OnEvent(Event& event) override;

		bool OnWindowResizeEvent(WindowResizeEvent& event);
		bool OnKeyPressedEvent(KeyPressedEvent& event);
		bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		bool OnKeyTypedEvent(KeyTypedEvent& event);
		bool OnMouseMovedEvent(MouseMovedEvent& event);
		bool OnMouseScrolledEvent(MouseScrolledEvent& event);
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);

		static ImGuiKey PhoenixKeyToImGui(unsigned int keycode);
	private:
		float lastUpdateTime = 0 ;
		
	};
}