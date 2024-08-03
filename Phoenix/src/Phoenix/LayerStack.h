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
			
		const std::vector<Layer*>::iterator begin() { return layers.begin(); }
		const std::vector<Layer*>::iterator end() { return layers.end(); }
	private:
		std::vector<Layer*> layers;
		std::vector<Layer*>::iterator layerInsert;

	};
}