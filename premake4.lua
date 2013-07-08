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
              "include" }
    
    -- OS defines
    if os.is("windows") then
        defines { "WIN32" }
    end

    defines { "M_SCRIPTABLE_BEHAVIOUR_BUILD" }

    dofile("proj-dynamic.lua")
    dofile("proj-static.lua")

