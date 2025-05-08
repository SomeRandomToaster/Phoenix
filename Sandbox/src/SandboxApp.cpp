#include "pch.h"

#define PH_INCLUDE_MAIN 
#include <Phoenix.h>

#include <RenderTest.h>


class Sandbox : public Phoenix::Application {
public:
	Sandbox() {
		PushLayer(new RenderTest());
	}

	

	~Sandbox() {

	}
};

Phoenix::Application* Phoenix::CreateApplication() {
	return new Sandbox;
}