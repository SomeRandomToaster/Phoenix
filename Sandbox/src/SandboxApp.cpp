#include "pch.h"

#define PH_INCLUDE_MAIN 
#include <Phoenix.h>

#include <AppLayer.h>


class Sandbox : public Phoenix::Application {
public:
	Sandbox() {
		PushLayer(new AppLayer());
	}

	

	~Sandbox() {

	}
};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox;
}