-- prebuild.lua


-- This file does things required before creating the 
-- projects.


-- Load Emp_core versions
version_file = io.open("../emp_core/src/versions.h","r")
_ = version_file:read() -- #Pragma once
emp_core_version = version_file:read()
radiance_version = version_file:read()
version_file:close()

-- Load own version
version_file = io.open("../src/VERSION","r")
emp_version = version_file:read()
version_file:close()


-- Write Radiance and Emp_core and Emp versions
file = io.open("../src/versions.h",'w')
file:write("#pragma once","\n")
file:write(emp_core_version,"\n")
file:write(radiance_version,"\n")
file:write("#define EMP_VERSION \"Emp "..emp_version.."\"","\n")
file:close()

-- Load configurations
dofile(premakescripts_dir.."/config.lua")


-- Create the bin/Debug and bin/Release directories
os.mkdir("../dist/DEBUG/"..p_dir)
os.mkdir("../dist/RELEASE/"..p_dir)
os.mkdir("../dist/DEBUG/"..rp_dir)
os.mkdir("../dist/RELEASE/"..rp_dir)
os.mkdir("../dist/DEBUG/"..ep_dir)
os.mkdir("../dist/RELEASE/"..ep_dir)
