
project "emp"
    kind "ConsoleApp"
    language "C++"
    buildoptions { '-std=c++11' }

    targetdir "../bin/%{cfg.buildcfg}"

    files { 
        "../main.cpp",
        "../src/**",    
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
            third_party_dir.."/SketchUp/WIN/binaries/sketchup/x64/*",                        
            emp_core_dir.."/3rdparty/intelTBB/lib/intel64/vc14/*",            
        }
        includedirs {
            third_party_dir.."/SketchUp/WIN/headers", 
        }    
    elseif is_macos then
        defines { "MACOS" }    
        
        buildoptions {
            "-F "..third_party_dir.."/SketchUp/MACOS/headers",            
        }
        links {
            third_party_dir.."/SketchUp/MACOS/headers/SketchUpAPI.framework",
        }
        linkoptions {
            "-F "..third_party_dir.."/SketchUp/MACOS/headers", 
            "-L "..emp_core_dir.."/libs/%{cfg.buildcfg}/tbb",
            "-v"
        }    
    elseif is_linux then
        defines { "LINUX", "AVOID_SKP" }    
        links {
            --third_party_dir.."/SketchUp/WIN/binaries/sketchup/x64/*",            
            third_party_dir.."/intelTBB/lib/intel64/vc14/*",            
        }

    end


    filter "configurations:Release"    
    links {
        "tbb"
    }

    filter "configurations:Debug"
    files {
        --third_party_dir.."/nvwa/nvwa/debug_new.cpp", 
    }
    includedirs{
        --third_party_dir.."/nvwa/nvwa",   
        --google_test_dir.."/include",    
    }
    links {
        "tbb_debug"
    }



