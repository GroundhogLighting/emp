project "emp_core"   
    
    kind "StaticLib"
    defines {"AVOID_EMP_CORE_WARNINGS"}
    buildoptions { '-std=c++11','-stdlib=libc++' }
    language "C++" 
    runpathdirs { "." }

    targetdir(libs_dir)

    files {                 
        emp_core_dir.."/src/**.cpp",  
        emp_core_dir.."/src/**.h",  
        emp_core_dir.."/include/**.h",  
    }
   
    includedirs{        
        emp_core_dir.."/3rdparty/",
        emp_core_dir.."/3rdparty/".."/intelTBB/include",                
        emp_core_dir.."/3rdparty/Radiance/src/common",
        emp_core_dir.."/3rdparty/Radiance/src/rt",
    }  

    links {                            
        "rtrad"
    }  


    -- Add the platform specific
    if is_windows then
        defines { "WIN" }               
        links {
            third_party_dir.."/SketchUp/WIN/binaries/sketchup/x64/*",                        
        }
    elseif is_macos then
        defines { "MACOS" }            
        runpathdirs { "libs" }
        --includedirs
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
        --buildoptions {
        --    "-F "..emp_core_dir.."/3rdparty/SketchUp/MACOS/headers",            
        --}
        
    elseif is_linux then
        defines { "LINUX", "AVOID_SKP" }    
        links {            
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

