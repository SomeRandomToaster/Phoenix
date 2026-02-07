#include "pch.h"

#define PH_INCLUDE_MAIN 
#include <Phoenix.h>

#include "MainLayer.h"


class TrashSim : public Phoenix::Application {
public:
	TrashSim() {
		PushLayer(new MainLayer());
	}

	

	~TrashSim() {

	}
};

Phoenix::Application* Phoenix::CreateApplication() {
	return new TrashSim;
}