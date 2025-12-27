#pragma once

#include "Application/Application.h"

#ifdef BUILD_APP

extern Render2D::Application* CreateApplication();

int main(int argc, char** argv)
{
	Render2D::Application* app = CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif
