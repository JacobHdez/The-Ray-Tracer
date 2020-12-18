#include "glpch.h"
#include "PerspectiveCamera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace GLCore::Utils {

	PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float zNear, float zFar)
		: m_ProjectionMatrix(glm::perspective(glm::radians(fovy), aspect, zNear, zFar))
		, m_ViewMatrix(1.0f)
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Right, m_Up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::SetProjection(float fovy, float aspect, float zNear, float zFar)
	{
		m_ProjectionMatrix = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void PerspectiveCamera::RecalculateViewMatrix()
	{
		m_ViewMatrix = glm::lookAt(m_Position, m_Position + m_Right, m_Up);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

}