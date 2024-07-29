#pragma once

#include "Core.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace Phoenix {
	class PH_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};
	Application* CreateApplication();
}