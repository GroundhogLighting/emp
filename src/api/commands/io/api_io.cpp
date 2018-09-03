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



int printValue(lua_State * L)
{
    // Check single argument
    checkNArguments(L, 1);
    
    // Print the value
    std::string r = "";
    
    int type = lua_type(L, 1);
    switch(type){
            
        case LUA_TNIL:
            r = r + "nil" + "\n";
            break;
            
        case LUA_TNONE:
            r = r + "nil" + "\n";
            break;
            
        case LUA_TSTRING:
            r = r + "\"" + std::string(lua_tostring(L, 1)) + "\"\n";
            break;
            
        case LUA_TNUMBER:
            r = r + std::to_string(lua_tonumber(L, 1)) + "\n";
            break;
            
        case LUA_TBOOLEAN:
            r = r + (lua_toboolean(L, 1) == 1 ? "true" : "false") + "\n";
            break;
        
        case LUA_TTABLE:
            {
                // check if it is an array, or an object
                if(fieldExists(L, 1, 1)){
                    // array
                    json j = json::array();
                    tableToJsonArray(L,1,&j);
                    r = r + j.dump(2) + "\n";
                }else{
                    // Object
                    json j = json::object();
                    tableToJson(L,1,&j);
                    r = r + j.dump(2) + "\n";
                }
                break;                
            }
        default:
            lua_pop(L, 1); // remove value
            lua_pushstring(L, "Trying to inspect an un-inspectable value"); // push message
            warn(L);
    }
    
    lua_pushstring(L, &r[0]);
    return 1;
}
