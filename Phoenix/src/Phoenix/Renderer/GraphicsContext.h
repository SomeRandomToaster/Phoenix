#pragma once

#include "Phoenix/Core/Core.h"

namespace Phoenix
{
	class PH_API GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
}