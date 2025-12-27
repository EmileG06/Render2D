project "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"
    toolset "v145"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp",
        "../vendor/glad/src/glad.c"
    }

    includedirs
    {
        "../Render2D/src",
        "../%{IncludeDir.GLFW}",
        "../%{IncludeDir.glad}",
        "../%{IncludeDir.glm}"
    }

    defines
    {
        "BUILD_APP"
    }

    links
    {
        "Render2D",
        "GLFW",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"