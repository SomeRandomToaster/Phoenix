#pragma once

#include "Event.h"

namespace Phoenix {
	class PH_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return keyCode; }
		
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

	protected:
		int keyCode;

		KeyEvent(int keyCode) 
			: keyCode(keyCode) {}
	};

	class PH_API KeyPressedEvent : public KeyEvent 
	{
	public:
		KeyPressedEvent(int keyCode, int repeatCount) 
			: KeyEvent(keyCode), repeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override 
		{
			std::ostringstream ss;
			ss << "KeyPressedEvent: " << keyCode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	protected:
		int repeatCount;
	};

	class PH_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keyCode)
			: KeyEvent(keyCode) {}

		std::string ToString() const override
		{
			std::ostringstream ss;
			ss << "KeyReleasedEvent: " << keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}