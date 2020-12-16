#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace OpenGL_Core {

	class OPENGLC_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define OGLC_CORE_TRACE(...)	::OpenGL_Core::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define OGLC_CORE_INFO(...)		::OpenGL_Core::Log::GetCoreLogger()->info(__VA_ARGS__)
#define OGLC_CORE_WARN(...)		::OpenGL_Core::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define OGLC_CORE_ERROR(...)	::OpenGL_Core::Log::GetCoreLogger()->error(__VA_ARGS__)
#define OGLC_CORE_FATAL(...)	::OpenGL_Core::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define OGLC_TRACE(...)			::OpenGL_Core::Log::GetClientLogger()->trace(__VA_ARGS__)
#define OGLC_INFO(...)			::OpenGL_Core::Log::GetClientLogger()->info(__VA_ARGS__)
#define OGLC_WARN(...)			::OpenGL_Core::Log::GetClientLogger()->warn(__VA_ARGS__)
#define OGLC_ERROR(...)			::OpenGL_Core::Log::GetClientLogger()->error(__VA_ARGS__)
#define OGLC_FATAL(...)			::OpenGL_Core::Log::GetClientLogger()->fatal(__VA_ARGS__)