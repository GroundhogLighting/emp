
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
#include "../../utils/common.h"
#include "../../utils/get_layer.h"




int getLayersList(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 0);
    
    GroundhogModel * model = getCurrentModel(L);
    size_t nwps = model->getNumLayers();
    
    // Create the table
    lua_newtable(L); // index = 1
    
    // push layer names
    for (size_t i = 0; i < nwps; i++) {
        std::string name = model->getLayerRef(i)->getName();
        lua_pushstring(L, &name[0]);
        lua_seti(L, 1, i+1);
    }
    
    return 1;
}

int countLayerObjects(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string layerName = lua_tostring(L, 1);
    
    // Check if workplane exists
    Layer * layer = getLayer(L,&layerName);
    
    const std::vector<Otype *> * objects = layer->getObjectsRef();
    
    lua_pushnumber(L,objects->size());
    
    return 1;
}

int countLayerInstances(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string layerName = lua_tostring(L, 1);
    
    // Check if workplane exists
    Layer * layer = getLayer(L,&layerName);
    
    const std::vector<ComponentInstance *> * instances = layer->getComponentInstancesRef();
    
    lua_pushnumber(L,instances->size());
    
    return 1;
}

int layerExists(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string layerName = lua_tostring(L, 1);
    
    GroundhogModel * model = getCurrentModel(L);
    
    // Check if workplane exists
    bool exists = (model->getLayerByName(&layerName) != nullptr);
    
    // Push the result
    lua_pushboolean(L, exists);
    
    // return
    return 1;
}

int createLayer(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string layerName = lua_tostring(L, 1);
    
    lua_pushstring(L, layerName.c_str());
    
    GroundhogModel * model = getCurrentModel(L);
    
    model->addLayer(&layerName);
    return 1;
}
