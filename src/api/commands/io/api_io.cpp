/*****************************************************************************
Emp

Copyright (C) 2018  German Molina (germolinal@gmail.com)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*****************************************************************************/

#include "./api_io.h"

int warn(lua_State * L)
{
    // Check single argument
    checkNArguments(L, 1);
    
    // Check that it is a string
    checkArgType(L, LUA_TSTRING, 1);
    
	lua_Debug ar;
	lua_getstack(L, 1, &ar);
	lua_getinfo(L, "nSl", &ar);

	const char * msg = lua_tostring(L, 1);
	std::cerr << "Warning from Line " << ar.currentline << ": " << msg << std::endl;
	
	return 0;
}

int raise(lua_State * L)
{
    // Check single argument
    checkNArguments(L, 1);
    
    // Check that it is a string
    checkArgType(L, LUA_TSTRING, 1);
    
    executionError(L,std::string(lua_tostring(L, 1)));
	return 0;
}


int printValue(lua_State * L)
{
    // Check single argument
    checkNArguments(L, 1);
    
    // Print the value
    int type = lua_type(L, 1);
    switch(type){
            
        case LUA_TNIL:
            std::cout << "nil" << std::endl;
            break;
            
        case LUA_TNONE:
            std::cout << "nil" << std::endl;
            break;
            
        case LUA_TSTRING:
            std::cout << "\"" << lua_tostring(L, 1) << "\"" << std::endl;
            break;
            
        case LUA_TNUMBER:
            std::cout << lua_tonumber(L, 1) << std::endl;
            break;
            
        case LUA_TBOOLEAN:
            std::cout << (lua_toboolean(L, 1) == 1 ? "true" : "false") << std::endl;
            break;
        
        case LUA_TTABLE:
            {
                // check if it is an array, or an object
                if(fieldExists(L, 1, 1)){
                    // array
                    json j = json::array();
                    tableToJsonArray(L,1,&j);
                    std::cout << j.dump(2) << std::endl;
                }else{
                    // Object
                    json j = json::object();
                    tableToJson(L,1,&j);
                    std::cout << j.dump(2) << std::endl;
                }
                break;                
            }
        default:
            lua_pop(L, 1); // remove value
            lua_pushstring(L, "Trying to inspect an un-inspectable value"); // push message
            warn(L);
    }
    
    return 0;
}
