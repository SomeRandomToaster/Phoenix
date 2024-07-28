#pragma once

#include "Core.h"

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