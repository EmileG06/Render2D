#include "OrthographicCamera.h"

#include "Core/Logger/Logger.h"

namespace Render2D::Renderer
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: Camera(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
	{
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
		LOG_INFO("OrthographicCamera created: Bounds=[{0}, {1}, {2}, {3}]", left, right, bottom, top);
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_Projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
		LOG_TRACE("OrthographicCamera projection updated: Bounds=[{0}, {1}, {2}, {3}]", left, right, bottom, top);
	}

	void OrthographicCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::SetRotation(float rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
	}

}
