#include "pch.h"
#include "LayerStack.h"

namespace Phoenix
{
	LayerStack::LayerStack()
	{

	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers.push_front(layer);
		layer->OnAttach();
	}
	
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layer->OnDetach();
			layers.erase(it);
		}
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		layers.push_back(layer);
		layer->OnAttach();
	}

	void LayerStack::PopOverlay(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layer->OnDetach();
			layers.erase(it);
		}
	}
}