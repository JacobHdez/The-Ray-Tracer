#include "oglcpch.h"
#include "Application.h"

#include "OpenGL_Core/Events/ApplicationEvent.h"
#include "OpenGL_Core/Log.h"

namespace OpenGL_Core {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			OGLC_TRACE(e);
		}
		if (e.IsInCategory(EventCategoryInput))
		{
			OGLC_TRACE(e);
		}

		while (true);
	}

}