#pragma once

#ifdef OGLC_PLATFORM_WINDOWS

	extern OpenGL_Core::Application* OpenGL_Core::CreateApplication();

	void main()
	{
		auto app = OpenGL_Core::CreateApplication();
		app->Run();
		delete app;
	}

#else
	#error OpenGl_Core only supports Windows!
#endif // OGLC_PLATFORM_WINDOWS