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

		void OnImGuiRender() override;
		void OnEvent(Event& event) override;

		void Begin();
		void End();


		//static ImGuiKey PhoenixKeyToImGui(unsigned int keycode);
	private:
		float lastUpdateTime = 0 ;
		
	};
}