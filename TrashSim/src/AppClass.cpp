#include "pch.h"

#define PH_INCLUDE_MAIN 
#include <Phoenix.h>


class TrashSim : public Phoenix::Application {
public:
	TrashSim() {

	}

	

	~TrashSim() {

	}
};

Phoenix::Application* Phoenix::CreateApplication() {
	return new TrashSim;
}