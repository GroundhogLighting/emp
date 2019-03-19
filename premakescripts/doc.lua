premake.modules.lua = {}
local m = premake.modules.lua

local p = premake



newaction {
	trigger = "emp_doc",
	description = "Builds the Emp Lua API documentation",

	onStart = function()
		print("About to build doc")
	end,

	execute = function()        
        
        local source_files = {
            './src/api/load_commands.h'
        }

        function trim(s)
            return (s:gsub("^%s*(.-)%s*$", "%1"))
        end

        local has_tag = function(line,tag)
            return string.find(line,tag)
        end

        local get_value = function(string,tag)
            ini,fin = has_tag(string,tag)            
            return string.sub(string,fin+2)
        end

        local print_md = function(file,string,tdc)
            if tdc > 0 then
                file:write("\n")
            end
            for i = 1,tdc do
                file:write("#")
            end
            if tdc > 0 then
                file:write(" ")
            end
            file:write(trim(string),"\n\n")

        end

        file = io.open("./emp-doc/api-reference.md", "w")        

        -- For each line in file
        for fileIndex=1,#source_files do
            
            source_file_name = source_files[fileIndex]
            
            print("   ... Processing file '"..source_file_name.."'")
            
            -- Gather lines
            local lines = {}
            for line in io.lines(source_file_name) do
                lines[#lines+1]=line
            end

            -- Process lines
            for i=1,#lines do                
                local line = lines[i]                
                if has_tag(line,"@APIgroup") then                     
                    v = get_value(line,"@APIgroup")
                    print_md(file,v,1)                    
                elseif has_tag(line,'@APIfunction') then                    
                    i = i+1
                    line = lines[i]

                    local description = ""
                    local params = {}
                    local returns = {}                    
                    local examples = {}

                    -- Opens space for function
                    while not has_tag(line,"lua_register") do                        
                        if has_tag(line,"@") then
                            if has_tag(line,"@param") then
                                local r = {}
                                if has_tag(line,"required") then
                                    r["required"] = true
                                    aux = get_value(line,"@param%[required%]")
                                    ini , _ = string.find(aux," ")
                                    r["name"] = string.sub(aux,1,ini)
                                    r["description"] = string.sub(aux,ini+1)
                                elseif has_tag(line,"optional") then
                                    r["required"] = false
                                    aux = get_value(line,"@param%[optional%]")
                                    ini , _ = string.find(aux," ")
                                    r["name"] = string.sub(aux,1,ini)
                                    r["description"] = string.sub(aux,ini+1)
                                else
                                    error("Param is not optional nor required in "..line)
                                end
                                params[#params+1] = r
                            elseif has_tag(line,"@return") then
                                local r = {}
                                aux = get_value(line,"@return")
                                ini , _ = string.find(aux," ")
                                r["name"] = string.sub(aux,1,ini)                                
                                r["description"] = string.sub(aux,ini+1)
                                returns[#returns + 1] = r
                            elseif has_tag(line,"@example") then
                                -- start recording example.
                                local r = {}
                                while true do
                                    i = i+1
                                    line = lines[i]
                                    if has_tag(line,"@endexample") then
                                        break
                                    end
                                    r[#r+1] = line
                                end

                                examples[#examples+1] = r
                            else
                                error("Unknown tag in line "..line)
                            end
                        else
                            if not string.find(line,"*/") then                      
                                description = description..line
                            end
                        end
                        
                        i = i+1
                        line = lines[i]
                    end   -- All information about the Function has been retrieved
                    
                                      
                    
                    -- Get and print the name of the function                                                         
                    local func_name
                    if has_tag(line,"lua_register")  then
                        ini,fin = has_tag(line,"\"")
                        func_name = string.sub(line,fin+1)
                        ini,fin = has_tag(func_name,"\"")
                        func_name = string.sub(func_name,1,ini-1)                                                                                       
                        print_md(file,func_name,2)
                    else
                        error("Line '"..line.."' does nor register a Lua function")
                    end

                    -- print description
                    print_md(file,description,0)

                    -- Print params
                    print_md(file,"**Parameters**",0)
                    if #params > 0 then
                        file:write("| **Name** | **Parameter** | **Required** |".."\n")
                        file:write("| --- | --- | --- |".."\n")
                        for j=1,#params do
                            local row = ""
                            row  = row .."| "..params[j]["name"]
                            row  = row .." | "..params[j]["description"]                            

                            local req = "TRUE"
                            if not params[j]["required"] then
                                req = "FALSE"
                            end
                            row  = row .." | "..req
                            file:write(row.." | \n")
                            
                        end
                    else
                        file:write("*This function receives no parameters*".."\n\n")
                    end
                    
                    -- print returns
                    print_md(file,"**Returns**",0)
                    if #returns > 0 then
                        file:write("| **Return** | **Description** |".."\n")
                        file:write("| --- | --- |".."\n")
                        for j=1,#returns do
                            local row = ""
                            row  = row .."| "..returns[j]["name"]                                                        
                            row  = row .." | "..returns[j]["description"]
                            --row  = row .." | "..req
                            file:write(row.." | \n")                            
                        end
                    else
                        file:write("*This function returns nothing*".."\n\n")
                    end

                    -- print examples
                    file:write("\n{% tabs %}".."\n")
                    
                    if #examples > 0 then
                        for j=1,#examples do                        
                            file:write("{% tab title='Example "..j.."' %}".."\n")
                            file:write("```lua".."\n")
                            for ex_ln=1,#examples[j] do
                                file:write(examples[j][ex_ln].."\n")
                            end
                            
                            file:write("```".."\n")
                            file:write("{% endtab %}".."\n")
                        end
                    else
                        -- tab 1... default
                        file:write("{% tab title='Example 1' %}".."\n")
                        file:write("```lua".."\n")

                        -- returns first
                        if #returns > 0 then
                            for j=1,#returns do
                                if j>1 then
                                    file:write(",")                                                        
                                end
                                file:write(returns[j]["name"])                                                        
                            end
                            file:write(" = ")                                                        
                        end
                        
                        -- Name of function with arguments
                        args = ""
                        for j=1,#params do
                            if j ~= 1 then
                                args = args..", "
                            end
                            args = args..trim(params[j]["name"])
                        end

                        file:write(func_name.."("..args..")".."\n")
                            
                        file:write("```".."\n")
                        file:write("{% endtab %}".."\n")
                    end

                    
                    file:write("{% endtabs %}".."\n".."\n")
                    

                end -- end of function
            end -- end iteration of lines

            


        end

        file:close()
          
	end,

	onEnd = function()
		print("Finished building doc")
	end
}

return m