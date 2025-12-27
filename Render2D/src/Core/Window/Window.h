#pragma once

#include "Core/Core.h"
#include "Core/Events/Events.h"

struct GLFWwindow;

namespace Render2D
{
	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width = 1920, Height = 1080;
		bool UseVSync = true;

		using EventCallbackFn = std::function<void(Event&)>;
		EventCallbackFn EventCallback;
	};

	class Window
	{
	public:
		Window(const WindowSpecification& specs = WindowSpecification());
		~Window();

		void Create();

		void Update();

		void RaiseEvent(Event& event);

		bool ShouldClose();

		GLFWwindow* GetHandle() const { return m_Handle; }

	private:
		WindowSpecification m_Specs;

		GLFWwindow* m_Handle;
	};

}

