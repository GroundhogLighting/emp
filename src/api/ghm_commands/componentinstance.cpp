
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

#include "./componentinstance.h"
#include "../utils/common.h"
#include "../utils/get_componentdefinition.h"
#include "../utils/get_layer.h"
#include "../utils/get_componentdefinition.h"


int createComponentInstance(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Get the definition name
    checkFieldType(L, 1, "definition", LUA_TSTRING);
    std::string definitionName = lua_tostring(L, 2);
    
    // Get layer
    Layer * layer = getLayerAccordingToTable(L,1);
    
    // Get the component definition
    ComponentDefinition * definition = getComponentDefinition(L, &definitionName);
    
    // Create a Component instance
    ComponentInstance * instance = new ComponentInstance(definition);
    
    // Add it
    layer->addComponentInstance(instance);
    
    // Check location
    if(checkFieldType(L, 1, "position", LUA_TTABLE, false)){
        lua_pop(L,1);
        Point3D p = getPointFromTableField(L, 1, "position");
        instance->setX(p.getX());
        instance->setY(p.getY());
        instance->setZ(p.getZ());
    }
    
    if(checkFieldType(L, 1, "scale", LUA_TNUMBER, false)){
        lua_pop(L,1);
        instance->setScale(getNumberFromTableField(L, 1, "scale"));
        
        std::cout << instance->getScale() << std::endl;
    }
    if(checkFieldType(L, 1, "rx", LUA_TNUMBER, false)){
        lua_pop(L,1);
        instance->setRotationX(getNumberFromTableField(L, 1, "rx"));
    }
    
    if(checkFieldType(L, 1, "ry", LUA_TNUMBER, false)){
        lua_pop(L,1);
        instance->setRotationY(getNumberFromTableField(L, 1, "ry"));
    }
    
    if(checkFieldType(L, 1, "rz", LUA_TNUMBER, false)){
        lua_pop(L,1);
        instance->setRotationZ(getNumberFromTableField(L, 1, "rz"));
    }
    
    return 0;
}

