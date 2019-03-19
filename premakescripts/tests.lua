premake.modules.lua = {}
local m = premake.modules.lua
local p = premake

newoption {
    trigger     = "test_filter",
    description = "Filters tests in the LuaUnit tests"
}


newaction {
	trigger = "emp_test",
	description = "Test the Emp API",


	execute = function()        
        
        
        lu = require("./3rdparty/LuaUnit/luaunit")


        dofile("./tests/io.lua")
                

        
        if _OPTIONS["test_filter"] then
            os.exit(lu.LuaUnit.run("--pattern",_OPTIONS["test_filter"]))
        else
            os.exit(lu.LuaUnit.run())
        end
          
	end
}

return m
