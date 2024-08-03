#include "pch.h"
#include <Phoenix.h>

#include "glm/mat4x4.hpp"

class MyLayer : public Phoenix::Layer {
public:
	MyLayer() : Layer("MyLayer") {}

	void OnAttach() override {
		glm::mat4x4 mat = glm::mat4x4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(0, 0, 0, 1));
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				PH_TRACE(mat[i][j]);
			}
		}
	}
	void OnEvent(Phoenix::Event& event) override {
		//PH_INFO("layerEvent: {0}", event.ToString());
		
	}

	void OnUpdate() override {
		
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