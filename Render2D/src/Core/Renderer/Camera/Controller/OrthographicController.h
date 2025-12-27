#pragma once

#include "Core/Core.h"
#include "Core/Events/Events.h"
#include "Core/Events/WindowEvents.h"
#include "Core/Events/MouseEvents.h"
#include "Core/Renderer/Camera/OrthographicCamera.h"

namespace Render2D::Renderer
{
	
	class OrthographicController
	{
	public:
		OrthographicController() = default;
		OrthographicController(float aspectRatio, bool rotation = false);

		void OnUpdate(float deltaTime);
		void OnEvent(Event& event);

		OrthographicCamera& GetCamera() { return m_Camera; }
		const OrthographicCamera& GetCamera() const { return m_Camera; }

		float GetZoomLevel() const { return m_ZoomLevel; }
		void SetZoomLevel(float zoomLevel);

		void SetAspectRatio(float aspectRatio);

		bool OnWindowResized(WindowResizedEvent& event);
		bool OnMouseScrolled(MouseScrolledEvent& event);

	private:
		float m_AspectRatio;
		float m_ZoomLevel = 1.0f;
		OrthographicCamera m_Camera;

		bool m_Rotation;

		glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
		float m_CameraRotation = 0.0f;
		float m_CameraTranslationSpeed = 5.0f;
		float m_CameraRotationSpeed = 100.0f;
	};

}
