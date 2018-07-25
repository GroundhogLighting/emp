
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

#ifndef OPTIONSET_EXTENSION_H
#define OPTIONSET_EXTENSION_H


extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "../utils/common.h"

//! Fills the options on an OptionSet with the data in a Lua table
/*!
@author German Molina
 @param options A pointer to the options to fill
 @param[in] L the lua_State
 @param tablePosition The position of the table in the lua_State
 @return success
*/
bool fillOptionsFromLuaTable(OptionSet * options, lua_State * L, int tablePosition);

#endif
