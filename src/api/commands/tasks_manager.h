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



extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//! Solves the current TaskManager
/*
@author German Molina
@param[in] L the lua_State object
@return the number of return values within the script
*/
int solveTaskManager(lua_State * L);


//! Prints the task manager
/*!
@author German Molina
@param[in] L the lua_State object
@return 0
*/
int printTaskManager(lua_State * L);

//! Removes the tasks from the current taskmanager
/*!
 @author German Molina
 @param[in] L the lua_State object
 @return 0
 */
int cleanTaskManager(lua_State * L);


//! Adds a task in the generic JSON form
/*!
 @author German Molina
 @param[in] L the lua_State object
 @return 0
 */
int pushJSONMetric(lua_State * L);

