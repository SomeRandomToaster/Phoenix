#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Phoenix 
{
	class PH_API WindowProps
	{
	public:

		WindowProps(unsigned int width = 1280, unsigned int height = 720, const std::string& title = "Phoenix Engine")
			: width(width), height(height), title(title) {}

		std::string title;
		unsigned int width;
		unsigned int height;
	};

	class PH_API Window 
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual ~Window() {};
		
		virtual void OnUpdate() = 0;

		inline virtual unsigned int GetWidth() const = 0;
		inline virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}