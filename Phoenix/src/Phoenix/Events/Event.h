#pragma once

#include "Phoenix/Core.h"

#include <string>
#include <functional>


namespace Phoenix {
	enum class EventType {
		None = 0,
		AppTick, AppUpdate, AppRender,
		WindowClose, WindowResize, WindowMoved, WindowFocus, WindowLostFocus,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

	class PH_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		bool handled = false;
	};

	
	class PH_API EventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) 
			: event(event) 
		{}

		template<typename T>
		bool Dispatch(EventFunction<T> func) {
			if (event.GetEventType() == T::GetStaticType())
			{
				event.handled = func(*((T*)&event));
				return true;
			}
			return false;
		}

	private:
		Event& event;
	};

	inline std::ostream& operator<< (std::ostream& os, const Event& event) {
		return os << event.ToString();
	}
}


#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
	virtual EventType GetEventType() const override {return GetStaticType(); } \
	virtual const char* GetName() const override { return #type; }