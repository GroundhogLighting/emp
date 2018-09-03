premake.modules.lua = {}
local m = premake.modules.lua

local p = premake

newaction {
	trigger = "intelTBB",
	description = "Builds the Intel TBB library",

	onStart = function()
		print("About to compile, move and clean the Intel TBB library")
	end,

	execute = function()
        
        -- Compile tbb in Release and Debug format. Will create the 
        --tbb_release and tbb_debug directories in ./build
        os.execute("cd emp_core/3rdparty/IntelTBB; make compiler=clang stdlib=libc++ tbb_build_prefix='tbb' tbb tbbmalloc")

        -- Create the lib 
        os.mkdir("emp_core/libs/DEBUG")
        os.mkdir("emp_core/libs/RELEASE")

        mv = "mv"
        cp = "cp"
        if is_windows then
            mv = "move"
            cp = "copy"
        end

        -- Remove the old TBB version
        os.rmdir("emp_core/libs/DEBUG/tbb")
        os.rmdir("emp_core/libs/RELEASE/tbb")

        -- Move results to Lib
        os.execute(mv.." emp_core/3rdparty/IntelTBB/build/tbb_release emp_core/libs/RELEASE/tbb")
        os.execute(mv.." emp_core/3rdparty/IntelTBB/build/tbb_debug emp_core/libs/DEBUG/tbb") 
        
        -- Move the dynamic lib to the emp_core/"..p_dir.."
        os.execute(cp.." emp_core/libs/RELEASE/tbb/libtbb.dylib emp_core/bin/RELEASE/libtbb.dylib") 
        os.execute(cp.." emp_core/libs/DEBUG/tbb/libtbb_debug.dylib emp_core/bin/DEBUG/libtbb_debug.dylib") 
        os.execute(cp.." emp_core/libs/RELEASE/tbb/libtbbmalloc.dylib emp_core/bin/RELEASE/libtbbmalloc.dylib") 
        os.execute(cp.." emp_core/libs/DEBUG/tbb/libtbbmalloc_debug.dylib emp_core/bin/DEBUG/libtbbmalloc_debug.dylib") 
        os.execute(cp.." emp_core/libs/RELEASE/tbb/libtbbmalloc_proxy.dylib emp_core/bin/RELEASE/libtbbmalloc_proxy.dylib") 
        os.execute(cp.." emp_core/libs/DEBUG/tbb/libtbbmalloc_proxy_debug.dylib emp_core/bin/DEBUG/libtbbmalloc_proxy_debug.dylib") 

        -- Store a copy in EMP as well        
        os.execute(cp.." emp_core/libs/RELEASE/tbb/libtbb.dylib dist/RELEASE"..p_dir.."/libtbb.dylib") 
        os.execute(cp.." emp_core/libs/DEBUG/tbb/libtbb_debug.dylib dist/DEBUG"..p_dir.."/libtbb_debug.dylib") 
        os.execute(cp.." emp_core/libs/RELEASE/tbb/libtbbmalloc.dylib dist/RELEASE"..p_dir.."/libtbbmalloc.dylib") 
        os.execute(cp.." emp_core/libs/DEBUG/tbb/libtbbmalloc_debug.dylib dist/DEBUG"..p_dir.."/libtbbmalloc_debug.dylib") 
        os.execute(cp.." emp_core/libs/RELEASE/tbb/libtbbmalloc_proxy.dylib dist/RELEASE"..p_dir.."/libtbbmalloc_proxy.dylib") 
        os.execute(cp.." emp_core/libs/DEBUG/tbb/libtbbmalloc_proxy_debug.dylib dist/DEBUG"..p_dir.."/libtbbmalloc_proxy_debug.dylib") 


        -- Clean new ones
        os.rmdir("emp_core/3rdparty/IntelTBB/build/tbb_release")
        os.rmdir("emp_core/3rdparty/IntelTBB/build/tbb_debug")

          
	end,

	onEnd = function()
		print("Finished compiling Intel TBB")
	end
}

return m