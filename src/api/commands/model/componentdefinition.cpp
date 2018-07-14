
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

#include "./componentdefinition.h"
#include "../../utils/common.h"
#include "../../utils/get_componentdefinition.h"

//#include <iostream>


int getComponentDefinitionsList(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 0);
    
    GroundhogModel * model = getCurrentModel(L);
    size_t nwps = model->getNumComponentDefinitions();
    
    // Create the table
    lua_newtable(L); // index = 1
    
    // push layer names
    for (size_t i = 0; i < nwps; i++) {
        std::string name = model->getComponentDefinitionRef(i)->getName();
        lua_pushstring(L, &name[0]);
        lua_seti(L, 1, i+1);
    }
    
    return 1;
}

int countComponentDefinitionObjects(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string layerName = lua_tostring(L, 1);
    
    // Check if workplane exists
    ComponentDefinition * cd = getComponentDefinition(L,&layerName);
    
    const std::vector<Otype *> * objects = cd->getObjectsRef();
    
    lua_pushnumber(L,objects->size());
    
    return 1;
}

int countComponentDefinitionInstances(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string layerName = lua_tostring(L, 1);
    
    // Check if workplane exists
    ComponentDefinition * cd = getComponentDefinition(L,&layerName);
    
    const std::vector<ComponentInstance *> * instances = cd->getComponentInstancesRef();
    
    lua_pushnumber(L,instances->size());
    
    return 1;
}

int componentDefinitionExists(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string cdName = lua_tostring(L, 1);
    
    GroundhogModel * model = getCurrentModel(L);
    
    // Check if workplane exists
    bool exists = (model->getComponentDefinitionByName(&cdName) != nullptr);
    
    // Push the result
    lua_pushboolean(L, exists);
    
    // return
    return 1;
}


int createComponentDefinition(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string name = lua_tostring(L, 1);
            
    // Create a ComponentDefinition and add it
    GroundhogModel * model = getCurrentModel(L);
    model->addComponentDefinition(&name);
    
    // Return the name
    lua_pushstring(L, name.c_str());
    
    return 1;
}

