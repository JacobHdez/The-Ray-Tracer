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

#ifdef OGLC_ENABLE_ASSERTS
	#define OGLC_ASSERT(x, ...) { if(!(x)) { OGLC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define OGLC_CORE_ASSERT(x, ...) { if(!(x)) { OGLC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define OGLC_ASSERT(x, ...)
	#define OGLC_CORE_ASSERT(x, ...)
#endif // OGLC_ENABLE_ASSERTS

#define BIT(x) (1 << x) 