#pragma once

#include "Layer.h"

namespace Phoenix
{
	class PH_API LayerStack
	{
	public:
		LayerStack();
		~LayerStack();
		
		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopOverlay(Layer* layer);
			
		const std::deque<Layer*>::iterator begin() { return layers.begin(); }
		const std::deque<Layer*>::iterator end() { return layers.end(); }
	private:
		std::deque<Layer*> layers;

	};
}