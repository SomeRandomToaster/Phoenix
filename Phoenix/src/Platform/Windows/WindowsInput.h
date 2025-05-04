#pragma once

#include "Phoenix/Core/Input.h"

namespace Phoenix
{
	class WindowsInput : public Input
	{
	private:
		bool IsKeyPressedImpl(unsigned int keycode) override;
		bool IsMouseButtonPressedImpl(unsigned int button) override;

		float GetMousePosXImpl() override;
		float GetMousePosYImpl() override;
		std::pair<float, float> GetMousePosImpl() override;
	};
}