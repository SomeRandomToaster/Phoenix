#include "pch.h"
#include <Phoenix.h>

class MyLayer : public Phoenix::Layer {
public:
	MyLayer() : Layer("MyLayer") {}
	void OnEvent(Phoenix::Event& event) override {
		//PH_INFO("layerEvent: {0}", event.ToString());
	}

	void OnUpdate() override {
		std::pair<float, float> pos;
		pos = Phoenix::Input::GetMousePos();
		PH_INFO("{0} {1}", pos.first, pos.second);
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