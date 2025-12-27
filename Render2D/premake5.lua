project "Render2D"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    staticruntime "on"
    toolset "v145"

    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

    flags { "MultiProcessorCompile" }

    files
    {
        "src/**.h",
        "src/**.cpp",
        "../vendor/glad/src/glad.c"
    }

    includedirs
    {
        "src",
        "src/vendor",
        "../%{IncludeDir.GLFW}",
        "../%{IncludeDir.glad}",
        "../%{IncludeDir.glm}"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        runtime "Release"
        optimize "on"