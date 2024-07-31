workspace "Phoenix"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


include "Phoenix/lib/glfw"
include "Phoenix/lib/glad"
include "Phoenix/lib/imgui"

project "Phoenix"
	location "Phoenix"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	
	pchheader "pch.h"
	pchsource "Phoenix/src/pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/lib/spdlog/include",
		"%{prj.name}/lib/glfw/include",
		"%{prj.name}/lib/glad/include",
		"%{prj.name}/lib/imgui"
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PH_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"PH_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "PH_DEBUG"
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "PH_RELEASE"
		optimize "On"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "PH_DIST"
		optimize "On"
		buildoptions "/MD"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Phoenix/lib/spdlog/include",
		"Phoenix/src"
	}

	links {
		"Phoenix"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PH_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PH_DEBUG"
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "PH_RELEASE"
		optimize "On"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "PH_DIST"
		optimize "On"
		buildoptions "/MD"