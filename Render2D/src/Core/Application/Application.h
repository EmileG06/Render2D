#pragma once

#include "Core/Core.h"
#include "Core/Window/Window.h"
#include "Core/Layer/Layer.h"
#include "Core/Events/Events.h"

namespace Render2D
{
	struct ApplicationSpecifics
	{
		std::string Title = "Application";
		WindowSpecification Window;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecifics& specs = ApplicationSpecifics());
		virtual ~Application();

		static Application& Get();

		void Run();
		void Stop();

		template <typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		void PushLayer()
		{
			m_LayerStack.push_back(std::make_unique<TLayer>());
		}

		template <typename TLayer>
		requires(std::is_base_of_v<Layer, TLayer>)
		TLayer* GetLayer()
		{
			for (const std::unique_ptr<Layer>& layer : m_LayerStack)
			{
				if (TLayer* casted = dynamic_cast<TLayer*>(layer))
					return casted;
			}
			return nullptr;
		}

		void RaiseEvent(Event& event);

		std::unique_ptr<Window>& GetWindow();

	private:
		void Update();
		void Render();

	private:
		ApplicationSpecifics m_Specs;

		std::unique_ptr<Window> m_Window;
		bool m_Running = false;

		float m_DeltaTime = 0.0f;
		float m_LastFrame = 0.0f;

		std::vector<std::unique_ptr<Layer>> m_LayerStack;
	};
}

Render2D::Application* CreateApplication();
