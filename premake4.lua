dofile("embed.lua")

embed "scripts"
embed "editor"

solution "MScriptableBehaviour"
    configurations { "Debug", "Release" }
    language "C++"
    
    -- make sure we can search and link properly
    libdirs { os.getenv("MSDKDIR") .. "/SDK/MCore/Libs",
          os.getenv("MSDKDIR") .. "/SDK/MEngine/Libs",
          "." }
    includedirs { os.getenv("MSDKDIR") .. "/SDK/MCore/Includes",
              os.getenv("MSDKDIR") .. "/SDK/MEngine/Includes",
              os.getenv("MSDKDIR") .. "/SDK/MIngEd/Includes" ,
              os.getenv("MSDKDIR") .. "/Plugins/Includes",
              "include", "scripts", "editor" }

    -- use MGameEvent if it exists
    if os.isfile(os.getenv("MSDKDIR") .. "Plugins/Includes/MGameEvent.h") then
        defines { "M_USE_GAME_EVENT" }
    end

    if os.isfile(os.getenv("MSDKDIR") .. "Plugins/Includes/MScriptExt.h") then
        defines { "M_USE_SCRIPT_EXT" }
    end

    if os.isfile(os.getenv("MSDKDIR") .. "Plugins/Includes/MEmbedFile.h") then
        defines { "M_USE_EMBED_FILE" }
    end

    -- OS defines
    if os.is("windows") then
        defines { "WIN32" }
    end

    defines { "M_SCRIPTABLE_BEHAVIOUR_BUILD" }

    dofile("proj-dynamic.lua")
    dofile("proj-static.lua")

