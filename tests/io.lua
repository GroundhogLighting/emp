TestIO = {} --class

    function TestIO:inspect_number()
        local a = inspect(1)
        lu.assertEquals( a , "1" )        
    end

    function TestIO:inspect_string()
        local a = "car"
        lu.assertEquals( a , "\"car\"" )
        
    end
