#pragma once

#include "Application.h"

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv) {
	Phoenix::Application* app = Phoenix::CreateApplication();
	app->Run();
	delete app;
}