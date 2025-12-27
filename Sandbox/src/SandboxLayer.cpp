#include "SandboxLayer.h"

SandboxLayer::SandboxLayer()
{
}

SandboxLayer::~SandboxLayer()
{
}

void SandboxLayer::OnEvent(Render2D::Event& event)
{
//	LOG_TRACE("SandboxLayer::OnEvent() -> {0}", event.ToString());

	Render2D::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Render2D::WindowClosedEvent>([this](Render2D::WindowClosedEvent& event) { return OnWindowClosed(event); });
}

void SandboxLayer::OnUpdate(float deltaTime)
{
//	LOG_DEBUG("SandboxLayer::OnUpdate(float) -> {0}", deltaTime);
}

void SandboxLayer::OnRender()
{
//	LOG_DEBUG("SandboxLayer::OnRender()");
}

bool SandboxLayer::OnWindowClosed(Render2D::WindowClosedEvent& event)
{
//	LOG_DEBUG("SandboxLayer::OnWindowClose()");
	return false;
}
