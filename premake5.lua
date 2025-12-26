workspace "Render2D"
    architecture "x64"
    configurations { "Debug", "Release" }
    startproject "Sandbox"

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    IncludeDir = {}
    IncludeDir["GLFW"] = "vendor/GLFW/include"
    IncludeDir["glad"] = "vendor/glad/include"
    IncludeDir["glm"] = "vendor/glm"

     group "Dependencies"
        include "vendor/GLFW"
    group ""

    include "Render2D"
    include "Sandbox"