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

#include "emp_core.h"
#include "./get_layer.h"
#include "./get_componentdefinition.h"
#include "./common.h"

Layer * getLayer(lua_State * L, std::string * layerName)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    EmpModel * model = getCurrentModel(L);
    Layer * layer = model->getLayerByName(layerName);
    
    if (layer == nullptr) {
        std::string errmsg = "Layer '" + *layerName + "' does not exist";
        sendError(L, "No Layer", &errmsg[0]);
    }
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    return layer;
}


Layer * getLayerAccordingToTable(lua_State * L, int tableIndex)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    Layer * layer;
    if(checkFieldType(L, tableIndex, "layer", LUA_TSTRING,false)){
        // There is a Layer option
        std::string layerName = std::string(lua_tostring(L,lua_gettop(L)));
        layer = getLayer(L, &layerName);
    }else{
        // There is NO layer option.
        // ... check for a Component option
        if(checkFieldType(L, tableIndex, "component", LUA_TSTRING,false)){
            std::string componentName = std::string(lua_tostring(L,lua_gettop(L)));
            layer = getComponentDefinition(L, &componentName);
            
        }else{
            EmpModel * model = getCurrentModel(L);
            
            // Default to first layer... Create one if not.
            if(model->getNumLayers() == 0){
                std::string layerName = "DefaultLayer";
                model->addLayer(&layerName);
            }
            
            layer = model->getLayerRef(0);
        }
        lua_pop(L,1);
    }
    lua_pop(L,1);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    return layer;    
}
