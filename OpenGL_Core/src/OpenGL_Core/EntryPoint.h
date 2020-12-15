#pragma once

#ifdef OGLC_PLATFORM_WINDOWS

	extern OpenGL_Core::Application* OpenGL_Core::CreateApplication();

	void main()
	{
		OpenGL_Core::Log::Init();
		OGLC_CORE_WARN("Initialized Log!");
		int a = 5;
		OGLC_INFO("Hello! Var={0}", a);

		auto app = OpenGL_Core::CreateApplication();
		app->Run();
		delete app;
	}

#else
	#error OpenGl_Core only supports Windows!
#endif // OGLC_PLATFORM_WINDOWS