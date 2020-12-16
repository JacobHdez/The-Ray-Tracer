workspace "The-Ray-Tracer"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "OpenGL_Core"
	location "OpenGL_Core"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"OGLC_PLATFORM_WINDOWS",
			"OGLC_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "OGLC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "OGLC_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "OGLC_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"OpenGL_Core/vendor/spdlog/include",
		"OpenGL_Core/src"
	}

	links
	{
		"OpenGL_Core"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"OGLC_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "OGLC_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "OGLC_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "OGLC_DIST"
		optimize "On"