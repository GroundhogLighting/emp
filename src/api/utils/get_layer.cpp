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

#include "../../../emp_core/include/emp_core.h"
#include "./get_layer.h"
#include "./common.h"

Layer * getLayer(lua_State * L, std::string * layerName)
{
    GroundhogModel * model = getCurrentModel(L);
    Layer * layer = model->getLayerByName(layerName);
    
    if (layer == nullptr) {
        std::string errmsg = "Layer '" + *layerName + "' does not exist";
        sendError(L, "No Layer", &errmsg[0]);
    }
    
    return layer;
}


Layer * getLayerAccordingToTable(lua_State * L, int tableIndex)
{
    
    int fieldType = lua_getfield(L,1, "layer");
    if(fieldType == LUA_TSTRING){
        std::string layerName = std::string(lua_tostring(L,2));
        return getLayer(L, &layerName);
    }else{
        lua_pop(L,1);
        GroundhogModel * model = getCurrentModel(L);
        
        // Default to first layer... Create one if not.
        if(model->getNumLayers() == 0){
            std::string layerName = "DefaultLayer";
            model->addLayer(&layerName);
        }
        return model->getLayerRef(0);
        
    }
}
