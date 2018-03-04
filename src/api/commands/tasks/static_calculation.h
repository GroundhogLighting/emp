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

#pragma once

#include "emp_core.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


//! Register a WorkplaneIlluminance tasl
/*!
Allows calculating the luminance or illuminance of a scene by using a certain sky

@author German Molina
@param[in] L The lua_State * object
@return Number of returned values to the lua script
*/
int workplaneIlluminance(lua_State * L);

//! Register an Daylight Factor task
/*!
 Allows calculating the luminance or illuminance of a scene by using a certain sky
 
 @author German Molina
 @param[in] L The lua_State * object
 @return Number of returned values to the lua script
 */
int daylightFactor(lua_State * L);
