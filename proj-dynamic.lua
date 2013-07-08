    project "MScriptableBehaviour"
        kind "SharedLib"
        language "C++"

        -- include all the files, including Maratis SDK ones
        files {
            "src/**.cpp",
            "include/**.h",
            "**.md",
            os.getenv("MSDKDIR") .. "SDK/**.h"
        }
        includedirs { "include" }
        targetdir "bin"
        targetprefix ""

        -- split the files up a bit nicer inside Visual Studio
        vpaths { 
            ["MCore/*"] = os.getenv("MSDKDIR") .. "/SDK/MCore/Includes/**.h",
            ["MEngine/*"] = os.getenv("MSDKDIR") .. "/SDK/MEngine/Includes/**.h",
            ["MIngEd/*"] = os.getenv("MSDKDIR") .. "/SDK/MIngEd/Includes/**.h",
            ["Plugin/*"] = { "**.h", "**.cpp" },
            ["Doc/*"] = { "**.md" }
        }
        -- link to Maratis
        links { "MCore", "MEngine" }
    
        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }
 
        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }  