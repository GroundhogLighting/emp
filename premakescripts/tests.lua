
lu = require("./3rdparty/LuaUnit/luaunit")


TestToto = {} --class

    function TestToto:test1_withFailure()
        local a = 1
        lu.assertEquals( a , 1 )
        -- will fail
        lu.assertEquals( a , 2 )
    end


--lu.LauaUnit.run()
os.exit(lu.LuaUnit.run())