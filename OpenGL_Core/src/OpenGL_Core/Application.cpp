#include "oglcpch.h"
#include "Application.h"

#include "OpenGL_Core/Events/ApplicationEvent.h"
#include "OpenGL_Core/Log.h"

#include "GLFW/glfw3.h"

namespace OpenGL_Core {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}