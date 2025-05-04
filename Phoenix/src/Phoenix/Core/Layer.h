#pragma once

#include "Core.h"
#include "Phoenix/Events/Event.h"
#include "Phoenix/Core/Timestep.h"

namespace Phoenix
{
	class PH_API Layer
	{
	public:
		Layer(const std::string& name = "Layer") : debugName(name) {}
		virtual ~Layer() {};

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate(Timestep ts) {};
		virtual void OnEvent(Event& event) {};
		virtual void OnImGuiRender() {}

		inline const std::string GetName() { return debugName; }
	protected:
		std::string debugName;
	};
}