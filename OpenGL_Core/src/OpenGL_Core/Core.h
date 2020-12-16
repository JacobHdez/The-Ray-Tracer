#pragma once

#ifdef OGLC_PLATFORM_WINDOWS
	#ifdef OGLC_BUILD_DLL
		#define OPENGLC_API __declspec(dllexport)
	#else
		#define OPENGLC_API __declspec(dllimport)
	#endif // OGLC_BUILD_DLL
#else
	#error OpenGl_Core only supports Windows!
#endif // OGLC_PLATFORM_WINDOWS

#define BIT(x) (1 << x) 