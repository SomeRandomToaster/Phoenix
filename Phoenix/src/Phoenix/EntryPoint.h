#pragma once

#include "Application.h"
#include "Log.h"

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv) {
	Phoenix::Log::Init();

	Phoenix::Application* app = Phoenix::CreateApplication();
	app->Run();
	delete app;
}