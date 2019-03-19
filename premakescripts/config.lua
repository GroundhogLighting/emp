-- Configurations for premake
-- ==========================


-- Emp basic organizations
base_dest_dir="../dist/%{cfg.buildcfg}"

p_dir = "/path"
rp_dir = "/raypath"
ep_dir = "/empath"

path_dir = base_dest_dir..p_dir
raypath_dir = base_dest_dir..rp_dir
empath_dir = base_dest_dir..ep_dir

libs_dir = "../libs/%{cfg.platform}".."/%{cfg.buildcfg}"

third_party_dir = "../3rdparty"
emp_core_dir = "../emp_core"
rad_common = emp_core_dir.."/3rdparty/Radiance/src/common"
rad_rt = emp_core_dir.."/3rdparty/Radiance/src/rt"

-- Google test directory
google_test_dir = "../googletest/googletest"


-- Lua base directory
lua_dir = "../3rdparty/Lua/"

-- Check if it is windows
is_windows = (os.target()=="windows")
is_linux = (os.target()=="linux")
is_macos = (os.target()=="macosx")


