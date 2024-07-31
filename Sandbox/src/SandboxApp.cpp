#include "pch.h"
#include <Phoenix.h>

class MyLayer : public Phoenix::Layer {
public:
	MyLayer() : Layer("MyLayer") {}
	void OnEvent(Phoenix::Event& event) override {
		PH_INFO("layerEvent: {0}", event.ToString());
	}

	void OnUpdate() override {
		PH_TRACE("layerUpdate");
	}
};

class Sandbox : public Phoenix::Application {
public:
	Sandbox() {
		PushLayer(new MyLayer());
		PushOverlay(new Phoenix::ImGuiLayer());
	}
	~Sandbox() {

	}
};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox;
}