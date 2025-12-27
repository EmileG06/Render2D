#include <Render2D.h>
#include <Core/Entrypoint.h>

#include "SandboxLayer.h"

class Sandbox : public Render2D::Application
{
public:
    Sandbox(const Render2D::ApplicationSpecifics& specs = Render2D::ApplicationSpecifics())
        : Application(specs) { }
    ~Sandbox() { }
};

Render2D::Application* CreateApplication()
{
    Render2D::ApplicationSpecifics appSpecs;
    appSpecs.Title = "Sandbox";
	appSpecs.Window.Width = 1920;
	appSpecs.Window.Height = 1080;
	appSpecs.Window.UseVSync = true;

    Render2D::Application* app = new Sandbox(appSpecs);
    app->PushLayer<SandboxLayer>();
    return app;
}
