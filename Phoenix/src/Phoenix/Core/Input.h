#pragma once

#include "Core.h"

namespace Phoenix
{
	class PH_API Input
	{
	public:
		static inline bool IsKeyPressed(unsigned int keycode) { return instance->IsKeyPressedImpl(keycode); }
		static inline bool IsMouseButtonPressed(unsigned int button) { return instance->IsMouseButtonPressedImpl(button); }

		static inline float GetMousePosX() { return instance->GetMousePosXImpl(); }
		static inline float GetMousePosY() { return instance->GetMousePosXImpl(); }
		static inline std::pair<float, float> GetMousePos() { return instance->GetMousePosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(unsigned int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(unsigned int button) = 0;

		virtual float GetMousePosXImpl() = 0;
		virtual float GetMousePosYImpl() = 0;
		virtual std::pair<float, float> GetMousePosImpl() = 0;
	private:
		static Input* instance;
	};
}