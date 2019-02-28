

project "emp_core_tests"

    kind "ConsoleApp"
    --buildoptions { '-std=c++11','-stdlib=libc++' }
    language "C++" 
    runpathdirs { "." }

    targetdir(path_dir)

    files { 
        emp_core_dir.."/main_test.cpp",
        emp_core_dir.."/main_test.h",        
        emp_core_dir.."/tests/*.h",
        emp_core_dir.."/tests/*/*.h",        
    }
   
    includedirs{
        emp_core_dir.."/3rdparty/",
        emp_core_dir.."/3rdparty/".."/intelTBB/include",                
        emp_core_dir.."/3rdparty/Radiance/src/common",
        emp_core_dir.."/3rdparty/Radiance/src/rt",

        emp_core_dir.."/src/",
        ---third_party_dir,
        --third_party_dir.."/intelTBB/include",        
        emp_core_dir.."/googletest/googletest/include",  
        --rad_common,
        --rad_rt                   
    }  

    links {                
        "GoogleTest",                
        "emp_core"
    }  

    filter "configurations:RELEASE"    
        links {
            "tbb","tbbmalloc","tbbmalloc_proxy"
        }

    filter "configurations:DEBUG"    
        links {
            "tbb_debug","tbbmalloc_debug","tbbmalloc_proxy_debug"
        }


    -- Add the platform specific
    --if is_windows then
    filter "system:windows"
        defines { "WIN" }               

    --elseif is_macos then
    filter "system:macosx"
        defines { "MACOS" }     
        linkoptions {            
            "-L "..libs_dir.."/%{cfg.buildcfg}/tbb",  
            --"-Wl,-rpath,\\$ORIGIN"          
        }    
        buildoptions {
            "-F /Library/Frameworks",
            "-v"            
        }
        links {
            "SketchUpAPI.framework",
        }
        
    --elseif is_linux then
    filter "system:linux"
        defines { "LINUX", "AVOID_SKP" }    
        links {            
            third_party_dir.."/intelTBB/lib/intel64/vc14/*",            
        }

    --end

    
    
