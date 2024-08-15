#include "pch.h"
#include <Phoenix.h>

#include "imgui.h"
#include "glm/mat4x4.hpp"

class MyLayer : public Phoenix::Layer {
public:
	MyLayer() : Layer("MyLayer") {}

	void OnAttach() override {
		
	}
	void OnEvent(Phoenix::Event& event) override {
		//PH_INFO("layerEvent: {0}", event.ToString());
		
	}

	void OnImGuiRender() override 
	{
		ImGui::Begin("Test window");

		ImGui::Text("Hello, World!");

		ImGui::End();

	}

	void OnUpdate() override {
		
	}
};

class Sandbox : public Phoenix::Application {
public:
	Sandbox() {
		PushLayer(new MyLayer());
	}
	~Sandbox() {

	}
};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox;
}