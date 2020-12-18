#pragma once

#include "PerspectiveCamera.h"
#include "GLCore/Core/Timestep.h"

#include "GLCore/Events/ApplicationEvent.h"
#include "GLCore/Events/MouseEvent.h"

namespace GLCore::Utils {

	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float fovy, float aspect, float zNear, float zFar);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		PerspectiveCamera& GetCamera() { return m_Camera; }
		const PerspectiveCamera& GetCamera() const { return m_Camera; }
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
	private:
		float m_fovy;
		float m_Aspect;
		float m_zNear;
		float m_zFar;

		float m_Speed = { 2.5f };
		float m_yaw = { -90.0f };
		float m_pitch = { 0.0f };
		float m_lastX = { 0.0f };
		float m_lastY = { 0.0f };

		PerspectiveCamera m_Camera;
	};

}