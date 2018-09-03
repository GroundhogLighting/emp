
project "emp"
    kind "ConsoleApp"
    language "C++"
    buildoptions { '-std=c++11' }
    runpathdirs { "." }
    targetdir(path_dir)
    buildoptions { "-v"}
    files { 
        "../main.cpp",
        "../src/**.h",
        "../src/**.cpp",    
        "../main.h",
        --emp_core_dir.."/src/**"
    }
    links {        
        "Lua",            
        "emp_core"
    }  

    includedirs{
        "../src/",
        third_party_dir,       
        emp_core_dir.."/include",
        emp_core_dir.."/3rdparty/intelTBB/include",                
        lua_dir,  
        emp_core_dir.."/src/",
        emp_core_dir.."/3rdparty/",        
        emp_core_dir.."/3rdparty/Radiance/src/common/",--rad_common,
        emp_core_dir.."/3rdparty/Radiance/src/rt/",--rad_rt        
    }

        
    
    -- Add the platform specific
    if is_windows then
        defines { "WIN" }    
        links {            
            emp_core_dir.."/3rdparty/intelTBB/lib/intel64/vc14/*",            
        }
        includedirs {
            third_party_dir.."/SketchUp/WIN/headers", 
        }    
    elseif is_macos then
        defines { "MACOS" }    
                
        buildoptions {
            "-F /Library/Frameworks",
            "-v",          
        }
        links {
            "SketchUpAPI.framework",
        }
        linkoptions {            
            "-L "..emp_core_dir.."/libs/%{cfg.buildcfg}/tbb"
        }   

        
    elseif is_linux then
        defines { "LINUX", "AVOID_SKP" }    
        links {
            --third_party_dir.."/SketchUp/WIN/"..path_dir.."aries/sketchup/x64/*",            
            third_party_dir.."/intelTBB/lib/intel64/vc14/*",            
        }

    end


    filter "configurations:RELEASE"    
    links {
        "tbb","tbbmalloc","tbbmalloc_proxy"
    }

    filter "configurations:DEBUG"    
    links {
        "tbb_debug","tbbmalloc_debug","tbbmalloc_proxy_debug"
    }



