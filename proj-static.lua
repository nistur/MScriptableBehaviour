    project "MScriptableBehaviourStatic"
        kind "StaticLib"
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
        targetname "MScriptableBehaviour"

        -- split the files up a bit nicer inside Visual Studio
        vpaths { 
            ["MCore/*"] = os.getenv("MSDKDIR") .. "/SDK/MCore/Includes/**.h",
            ["MEngine/*"] = os.getenv("MSDKDIR") .. "/SDK/MEngine/Includes/**.h",
            ["MIngEd/*"] = os.getenv("MSDKDIR") .. "/SDK/MIngEd/Includes/**.h",
            ["Plugin/*"] = { "**.h", "**.cpp" },
            ["Doc/*"] = { "**.md" }
        }
        defines { "M_SCRIPTABLE_BEHAVIOUR_STATIC" }
        -- link to Maratis
        links { "MCore", "MEngine" }
    
        configuration "Debug"
            defines { "DEBUG" }
            flags { "Symbols" }
 
        configuration "Release"
            defines { "NDEBUG" }
            flags { "Optimize" }  