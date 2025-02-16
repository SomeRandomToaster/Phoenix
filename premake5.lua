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
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	
	pchheader "pch.h"
	pchsource "Phoenix/src/pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/lib/glm/glm/**.hpp",
		"%{prj.name}/lib/glm/glm/**.inl",
		"%{prj.name}/lib/stb/**.h",
		"%{prj.name}/lib/stb/**.cpp"
	}

	includedirs {
		"%{prj.name}/src",
		"%{prj.name}/lib/spdlog/include",
		"%{prj.name}/lib/glfw/include",
		"%{prj.name}/lib/glad/include",
		"%{prj.name}/lib/imgui",
		"%{prj.name}/lib/glm",
		"%{prj.name}/lib/stb",
	}

	links {
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PH_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE",
			"PH_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "PH_DEBUG"
		symbols "On"
		buildoptions "/MTd"

	filter "configurations:Release"
		defines "PH_RELEASE"
		optimize "On"
		buildoptions "/MT"

	filter "configurations:Dist"
		defines "PH_DIST"
		optimize "On"
		buildoptions "/MT"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Phoenix/lib/spdlog/include",
		"Phoenix/src",
		"Phoenix/lib/glm",
		"Phoenix/lib/imgui",
		"%{prj.name}/src"
	}

	links {
		"Phoenix"
	}

	filter "system:windows"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PH_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PH_DEBUG"
		symbols "On"
		buildoptions "/MTd"

	filter "configurations:Release"
		defines "PH_RELEASE"
		optimize "On"
		buildoptions "/MT"

	filter "configurations:Dist"
		defines "PH_DIST"
		optimize "On"
		buildoptions "/MT"