#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace OpenGL_Core {

	class OPENGLC_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be define in CLIENT
	Application* CreateApplication();

}