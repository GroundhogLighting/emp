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

#pragma once


// Include LUA headers
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//! Retrieves a Layer from the current model
/*!
 Raises an error if it does not exist
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] layerName The name of the workplane
 @return The layer
 */
Layer * getLayer(lua_State * L, std::string * layerName);

//! Retrieves a Layer from the current model taking into account what a Lua table specifies
/*!
 Returns the first layer in the model if no 'layer' field exists in the table.
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @return The layer
 */
Layer * getLayerAccordingToTable(lua_State * L, int tableIndex);
