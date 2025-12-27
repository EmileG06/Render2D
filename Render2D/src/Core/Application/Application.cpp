#include "Application.h"

#include <GLFW/glfw3.h>

#include "Core/Logger/Logger.h"

namespace Render2D
{
	static Application* s_Instance = nullptr;

	Application::Application(const ApplicationSpecifics& specs)
		: m_Specs(specs)
	{
		s_Instance = this;

		if (m_Specs.Window.Title.empty())
			m_Specs.Window.Title = m_Specs.Title;

		m_Specs.Window.EventCallback = [this](Event& event) { RaiseEvent(event); };

		m_Window = std::make_unique<Window>(m_Specs.Window);
		m_Window->Create();
	}

	Application::~Application()
	{
		s_Instance = nullptr;
	}

	Application& Application::Get()
	{
		return *s_Instance;
	}

	void Application::Run()
	{
		m_Running = true;

		while (m_Running)
		{
			if (m_Window->ShouldClose())
			{
				Stop();
				break;
			}

			float currentFrame = static_cast<float>(glfwGetTime());
			m_DeltaTime = currentFrame - m_LastFrame;
			m_LastFrame = currentFrame;

			Update();
			Render();

			m_Window->Update();
		}
	}

	void Application::Stop()
	{
		m_Running = false;
	}

	void Application::RaiseEvent(Event& event)
	{
		for (std::unique_ptr<Layer>& layer : m_LayerStack)
		{
			layer->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	std::unique_ptr<Render2D::Window>& Application::GetWindow()
	{
		return m_Window;
	}

	void Application::Update()
	{
		for (const std::unique_ptr<Layer>& layer : m_LayerStack)
			layer->OnUpdate(m_DeltaTime);
	}

	void Application::Render()
	{
		for (const std::unique_ptr<Layer>& layer : m_LayerStack)
			layer->OnRender();
	}

}
