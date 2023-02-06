workspace "PopEngine"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "PopEngine/vendor/GLFW/include"
IncludeDir["Glad"] = "PopEngine/vendor/Glad/include"
IncludeDir["ImGui"] = "PopEngine/vendor/imgui"
IncludeDir["glm"] = "PopEngine/vendor/glm"
IncludeDir["stb_image"] = "PopEngine/vendor/stb_image"

group "Dependencies"
include "PopEngine/vendor/GLFW"
include "PopEngine/vendor/Glad"
include "PopEngine/vendor/imgui"

group "Core"
	
project "PopEngine"
	location "PopEngine"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "pepch.h"
	pchsource "PopEngine/src/pepch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
		
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}",
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"
		
		defines
		{
			"PE_PLATFORM_WINDOWS",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
		}
		
	filter "configurations:Debug"
		defines "PE_DEBUG"
		symbols "On"
		runtime "Debug"
				
	filter "configurations:Release"
		defines "PE_RELEASE"
		optimize "On"
		runtime "Release"
		
	filter "configurations:Dist"
		defines "PE_DIST"
		optimize "On"
		runtime "Release"
		
group ""
		
project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	includedirs
	{
		"PopEngine/src",
		"PopEngine/vendor/spdlog/include",
		"PopEngine/vendor/imgui",
		"%{IncludeDir.glm}"
	}
	
	links
	{
		"PopEngine"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		systemversion "latest"
		
		defines
		{
			"PE_PLATFORM_WINDOWS"
		}
		
	filter "configurations:Debug"
		defines "PE_DEBUG"
		symbols "On"
				
	filter "configurations:Release"
		defines "PE_RELEASE"
		optimize "On"
				
	filter "configurations:Dist"
		defines "PE_DIST"
		optimize "On"