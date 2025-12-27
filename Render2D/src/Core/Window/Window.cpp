#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Core/Logger/Logger.h"
#include "Core/Application/Application.h"
#include "Core/Events/WindowEvents.h"
#include "Core/Events/KeyEvents.h"
#include "Core/Events/MouseEvents.h"

namespace Render2D
{
	static bool s_GLFWInit = false;

	static void FramebufferSizeCallback(GLFWwindow* window, int32_t width, int32_t height)
	{
		auto& windowRef = Application::Get().GetWindow();
		windowRef->UpdateSize(width, height);
		glViewport(0, 0, width, height);
	}

	Window::Window(const WindowSpecification& specs)
		: m_Specs(specs)
	{
	}

	Window::~Window()
	{
	}

	void Window::Create()
	{
		if (!s_GLFWInit)
		{
			if (glfwInit() != GLFW_TRUE)
			{
				LOG_ERROR("Failed to initialize GLFW!");
				__debugbreak();
			}

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			s_GLFWInit = true;
		}

		m_Handle = glfwCreateWindow(m_Specs.Width, m_Specs.Height, m_Specs.Title.c_str(), nullptr, nullptr);
		if (!m_Handle)
		{
			LOG_ERROR("Failed to create window!");
			__debugbreak();
		}

		glfwMakeContextCurrent(m_Handle);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			LOG_ERROR("Failed to initialize GLAD!");
			__debugbreak();
		}

		glfwSwapInterval(m_Specs.UseVSync ? 1 : 0);

		glfwSetWindowUserPointer(m_Handle, this);

		glfwSetWindowCloseCallback(m_Handle, [](GLFWwindow* handle)
			{
				Window& window = *((Window*)glfwGetWindowUserPointer(handle));

				WindowClosedEvent event;
				window.RaiseEvent(event);
			});

		glfwSetFramebufferSizeCallback(m_Handle, [](GLFWwindow* handle, int32_t width, int32_t height)
			{
				Window& window = *((Window*)glfwGetWindowUserPointer(handle));

				WindowResizedEvent event = WindowResizedEvent(static_cast<float>(width), static_cast<float>(height));
				window.RaiseEvent(event);
			});

		glfwSetKeyCallback(m_Handle, [](GLFWwindow* handle, int32_t key, int32_t scancode, int32_t action, int32_t mods)
			{
				Window& window = *((Window*)glfwGetWindowUserPointer(handle));

				switch (action)
				{
				case GLFW_PRESS:
				case GLFW_REPEAT:
				{
					KeyPressedEvent event = KeyPressedEvent(key, action == GLFW_REPEAT);
					window.RaiseEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event = KeyReleasedEvent(key);
					window.RaiseEvent(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(m_Handle, [](GLFWwindow* handle, int32_t button, int32_t action, int32_t mods)
			{
				Window& window = *((Window*)glfwGetWindowUserPointer(handle));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event = MouseButtonPressedEvent(button);
					window.RaiseEvent(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event = MouseButtonReleasedEvent(button);
					window.RaiseEvent(event);
					break;
				}
				}
			});

		glfwSetCursorPosCallback(m_Handle, [](GLFWwindow* handle, double x, double y)
			{
				Window& window = *((Window*)glfwGetWindowUserPointer(handle));

				MouseMovedEvent event = MouseMovedEvent(static_cast<float>(x), static_cast<float>(y));
				window.RaiseEvent(event);
			});

		glfwSetScrollCallback(m_Handle, [](GLFWwindow* handle, double x, double y)
			{
				Window& window = *((Window*)glfwGetWindowUserPointer(handle));

				MouseScrolledEvent event = MouseScrolledEvent(static_cast<float>(x), static_cast<float>(y));
				window.RaiseEvent(event);
			});

		LOG_INFO("Window created -> {0} [{1}, {2}]", 
			m_Specs.Title, m_Specs.Width, m_Specs.Height);
	}

	void Window::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Handle);
	}

	void Window::RaiseEvent(Event& event)
	{
		if (m_Specs.EventCallback)
			m_Specs.EventCallback(event);
	}

	void Window::UpdateSize(int32_t width, int32_t height)
	{
		m_Specs.Width = width;
		m_Specs.Height = height;
	}

	bool Window::ShouldClose()
	{
		return glfwWindowShouldClose(m_Handle) != 0;
	}

}
