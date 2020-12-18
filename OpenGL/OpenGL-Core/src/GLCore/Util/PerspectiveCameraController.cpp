#include "glpch.h"
#include "PerspectiveCameraController.h"

#include "GLCore/Core/Input.h"
#include "GLCore/Core/KeyCodes.h"
#include "GLCore/Core/MouseButtonCodes.h"

namespace GLCore::Utils {

	PerspectiveCameraController::PerspectiveCameraController(float fovy, float aspect, float zNear, float zFar)
		: m_fovy{ fovy }, m_Aspect{ aspect }, m_zNear{ zNear }, m_zFar{ zFar }
		, m_Camera(fovy, aspect, zNear, zFar)
	{
	}

	void PerspectiveCameraController::OnUpdate(Timestep ts)
	{
		if (Input::IsKeyPressed(HZ_KEY_W))
		{
			glm::vec3 transform = m_Camera.GetPosition() + m_Camera.GetRight() * m_Speed * float(ts);
			m_Camera.SetPosition(transform);
		}
		if (Input::IsKeyPressed(HZ_KEY_S))
		{
			glm::vec3 transform = m_Camera.GetPosition() - m_Camera.GetRight() * m_Speed * float(ts);
			m_Camera.SetPosition(transform);
		}
		if (Input::IsKeyPressed(HZ_KEY_A))
		{
			glm::vec3 transform = m_Camera.GetPosition() - glm::normalize(glm::cross(m_Camera.GetRight(), m_Camera.GetUp())) * m_Speed * float(ts);
			m_Camera.SetPosition(transform);
		}
		if (Input::IsKeyPressed(HZ_KEY_D))
		{
			glm::vec3 transform = m_Camera.GetPosition() + glm::normalize(glm::cross(m_Camera.GetRight(), m_Camera.GetUp())) * m_Speed * float(ts);
			m_Camera.SetPosition(transform);
		}
		if (Input::IsMouseButtonPressed(HZ_MOUSE_BUTTON_RIGHT))
		{
			m_yaw += (Input::GetMouseX() - m_lastX) * 0.1f;
			m_pitch += (Input::GetMouseY() - m_lastY) * 0.1f;
			if (m_pitch > 89.0f) m_pitch = 89.0f;
			if (m_pitch < -89.0f) m_pitch = -89.0f;

			glm::vec3 transform;
			transform.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
			transform.y = -sin(glm::radians(m_pitch));
			transform.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
			m_Camera.SetRight(glm::normalize(transform));

			m_lastX = Input::GetMouseX();
			m_lastY = Input::GetMouseY();
		}
	}

	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnMouseScrolled));
		dispatcher.Dispatch<WindowResizeEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnWindowResized));
		dispatcher.Dispatch<MouseButtonPressedEvent>(GLCORE_BIND_EVENT_FN(PerspectiveCameraController::OnMouseButtonPressed));
	}

	bool PerspectiveCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		m_fovy -= e.GetYOffset();
		if (m_fovy < 1.0f) m_fovy = 1.0f;
		else if (m_fovy > 45.0f) m_fovy = 45.0f;
		else m_Camera.SetProjection(m_fovy, m_Aspect, m_zNear, m_zFar);
		return false;
	}

	bool PerspectiveCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		m_Aspect = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera.SetProjection(m_fovy, m_Aspect, m_zNear, m_zFar);
		return false;
	}

	bool PerspectiveCameraController::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		if (e.GetMouseButton() == HZ_MOUSE_BUTTON_RIGHT)
		{
			m_lastX = Input::GetMouseX();
			m_lastY = Input::GetMouseY();
		}
		return false;
	}

}