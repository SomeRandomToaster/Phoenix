#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Phoenix
{
	class PH_API Layer
	{
	public:
		Layer(const std::string& name = "Layer") : debugName(name) {}
		virtual ~Layer() {};

		virtual void OnAttach() {};
		virtual void OnDetach() {};
		virtual void OnUpdate() {};
		virtual void OnEvent(Event& event) {};

		inline const std::string GetName() { return debugName; }
	protected:
		std::string debugName;
	};
}