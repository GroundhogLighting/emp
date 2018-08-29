
project "GoogleTest"
    kind "StaticLib"
    files { emp_core_dir.."/googletest/googletest/src/gtest-all.cc" }
    includedirs { emp_core_dir.."/googletest/googletest/include", emp_core_dir.."/googletest/googletest/" }
    targetdir (libs_dir.."/%{cfg.platform}")        



