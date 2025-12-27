#pragma once

#include <Render2D.h>
#include <Core/Events/WindowEvents.h>

class SandboxLayer : public Render2D::Layer
{
public:
	SandboxLayer();
	~SandboxLayer();

	virtual void OnEvent(Render2D::Event& event) override;

	virtual void OnUpdate(float deltaTime) override;
	virtual void OnRender() override;

	bool OnWindowClosed(Render2D::WindowClosedEvent& event);
};
