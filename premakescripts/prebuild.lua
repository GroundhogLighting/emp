-- prebuild.lua


-- This file does things required before creating the 
-- projects.

-- Load configurations
dofile(premakescripts_dir.."/config.lua")


-- Create the bin/Debug and bin/Release directories
os.mkdir("../bin/DEBUG")
os.mkdir("../bin/RELEASE")
