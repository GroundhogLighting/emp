

/*****************************************************************************
 Emp
 
 Copyright (C) 2017  German Molina (germolinal@gmail.com)
 
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

#include "./layer.h"
#include "../utils/common.h"
#include "../utils/get_otype.h"



int otypeExists(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string objectName = lua_tostring(L, 1);
    
    GroundhogModel * model = getCurrentModel(L);
    
    // Check if workplane exists
    bool exists = (model->getOtypeByName(&objectName) != nullptr);
    
    // Push the result
    lua_pushboolean(L, exists);
    
    // return
    return 1;
}

int getOtypeType(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string objectName = lua_tostring(L, 1);
    
    Otype * o = getOtype(L,&objectName);
    
    lua_pushstring(L, o->getType()->c_str());
    
    return 1;
}


