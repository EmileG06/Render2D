#include "OrthographicController.h"

#include "Core/Logger/Logger.h"
#include "Core/Application/Application.h"

#include <GLFW/glfw3.h>

namespace Render2D::Renderer
{

	OrthographicController::OrthographicController(float aspectRatio, bool rotation)
		: m_AspectRatio(aspectRatio),
		m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio* m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel),
		m_Rotation(rotation)
	{
		LOG_INFO("OrthographicCameraController created: AspectRatio={0}, Rotation={1}",
			aspectRatio, rotation);
	}

	void OrthographicController::OnUpdate(float deltaTime)
	{
		if (glfwGetKey(Application::Get().GetWindow()->GetHandle(), GLFW_KEY_A))
			m_CameraPosition.x -= m_CameraTranslationSpeed * deltaTime;
		else if (glfwGetKey(Application::Get().GetWindow()->GetHandle(), GLFW_KEY_D))
			m_CameraPosition.x += m_CameraTranslationSpeed * deltaTime;

		if (glfwGetKey(Application::Get().GetWindow()->GetHandle(), GLFW_KEY_W))
			m_CameraPosition.y += m_CameraTranslationSpeed * deltaTime;
		else if (glfwGetKey(Application::Get().GetWindow()->GetHandle(), GLFW_KEY_S))
			m_CameraPosition.y -= m_CameraTranslationSpeed * deltaTime;

		if (m_Rotation)
		{
			if (glfwGetKey(Application::Get().GetWindow()->GetHandle(), GLFW_KEY_Q))
				m_CameraRotation += m_CameraRotationSpeed * deltaTime;
			if (glfwGetKey(Application::Get().GetWindow()->GetHandle(), GLFW_KEY_E))
				m_CameraRotation -= m_CameraRotationSpeed * deltaTime;

			m_Camera.SetRotation(m_CameraRotation);
		}

		m_Camera.SetPosition(m_CameraPosition);

		m_CameraTranslationSpeed = m_ZoomLevel;
	}

	void OrthographicController::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseScrolledEvent>([this](MouseScrolledEvent& event) { return OnMouseScrolled(event); });
		dispatcher.Dispatch<WindowResizedEvent>([this](WindowResizedEvent& event) { return OnWindowResized(event); });
	}

	void OrthographicController::SetZoomLevel(float zoomLevel)
	{
		m_ZoomLevel = std::max(zoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel);
		LOG_TRACE("Camera zoom level changed: {0}", m_ZoomLevel);
	}

	void OrthographicController::SetAspectRatio(float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel);
		LOG_TRACE("Camera aspect ratio changed: {0}", m_AspectRatio);
	}

	bool OrthographicController::OnWindowResized(WindowResizedEvent& event)
	{
		if (event.GetHeight() == 0) return false;

		m_AspectRatio = event.GetWidth() / event.GetHeight();
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel);

		return false;
	}

	bool OrthographicController::OnMouseScrolled(MouseScrolledEvent& event)
	{
		m_ZoomLevel -= event.GetY() * 0.25f;
		m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
		m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel,
			-m_ZoomLevel, m_ZoomLevel);

		return false;
	}

}
