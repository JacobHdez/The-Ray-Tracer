#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "OpenGL_Core/Events/ApplicationEvent.h"

#include "Window.h"

namespace OpenGL_Core {

	class OPENGLC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be define in CLIENT
	Application* CreateApplication();

}