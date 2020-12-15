#pragma once

#include "Core.h"

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