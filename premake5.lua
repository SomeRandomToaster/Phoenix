workspace "Phoenix"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Phoenix"
	location "Phoenix"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/lib/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PH_PLATFORM_WINDOWS",
			"PH_BUILD_DLL"
		}

		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "PH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PH_DIST"
		optimize "On"


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
		cppdialect "C++14"
		staticruntime "On"
		systemversion "latest"

		defines {
			"PH_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "PH_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "PH_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "PH_DIST"
		optimize "On"