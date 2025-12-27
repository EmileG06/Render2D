#include "PerspectiveCamera.h"

#include "Core/Logger/Logger.h"

namespace Render2D::Renderer
{

	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: Camera(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip)),
		m_FOV(fov), m_AspectRatio(aspectRatio), m_NearClip(nearClip), m_FarClip(farClip)
	{
		m_ViewMatrix = glm::mat4(1.0f);
		m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
		LOG_INFO("PerspectiveCamera created: FOV={0}, AspectRatio={1}, Near={2}, Far={3}",
			fov, aspectRatio, nearClip, farClip);
	}

	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip)
	{
		m_FOV = fov;
		m_AspectRatio = aspectRatio;
		m_NearClip = nearClip;
		m_FarClip = farClip;

		m_Projection = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);
		m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
		LOG_TRACE("PerspectiveCamera projection updated: FOV={0}, AspectRatio={1}", fov, aspectRatio);
	}

	void PerspectiveCamera::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetRotation(const glm::vec3& rotation)
	{
		m_Rotation = rotation;
		RecalculateViewMatrix();
	}

	void PerspectiveCamera::SetFOV(float fov)
	{
		m_FOV = fov;
		SetProjection(m_FOV, m_AspectRatio, m_NearClip, m_FarClip);
	}

	glm::vec3 PerspectiveCamera::GetForwardDirection() const
	{
		glm::vec3 forward;
		forward.x = glm::cos(glm::radians(m_Rotation.y)) * glm::cos(glm::radians(m_Rotation.x));
		forward.y = glm::sin(glm::radians(m_Rotation.x));
		forward.z = glm::sin(glm::radians(m_Rotation.y)) * glm::cos(glm::radians(m_Rotation.x));
		return glm::normalize(forward);
	}

	glm::vec3 PerspectiveCamera::GetRightDirection() const
	{
		return glm::normalize(glm::cross(GetForwardDirection(), glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	glm::vec3 PerspectiveCamera::GetUpDirection() const
	{
		return glm::normalize(glm::cross(GetRightDirection(), GetForwardDirection()));
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position);
		transform = glm::rotate(transform, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)); // Pitch
		transform = glm::rotate(transform, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)); // Yaw
		transform = glm::rotate(transform, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1)); // Roll

		m_ViewMatrix = glm::inverse(transform);
		m_ViewProjectionMatrix = m_Projection * m_ViewMatrix;
	}

}
