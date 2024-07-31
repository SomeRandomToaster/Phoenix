#pragma once

#include "Phoenix/Layer.h"

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
	private:
		float lastUpdateTime = 0 ;
	};
}