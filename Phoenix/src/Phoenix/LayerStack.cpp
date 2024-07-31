#include "pch.h"
#include "LayerStack.h"

namespace Phoenix
{
	LayerStack::LayerStack()
	{
		layerInsert = layers.begin();
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers) {
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layerInsert = layers.emplace(layerInsert, layer);
		layer->OnAttach();
	}
	
	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layer->OnDetach();
			layers.erase(it);
			layerInsert--;
		}
	}

	void LayerStack::PushOverlay(Layer* layer)
	{
		layers.emplace_back(layer);
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