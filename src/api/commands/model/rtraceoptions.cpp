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


#include "config_constants.h"
#include "emp_core.h"
#include "../../utils/optionset_ext.h"
#include "./api/utils/common.h"


#include <iostream>
#include <fstream>

int printRtraceOptions(lua_State * L)
{
    

    // Check if any input was given
    int nargs[2] = { 0, 1 };
    int n = checkNArguments(L, nargs,2);

    EmpModel * model = getCurrentModel(L);
    RTraceOptions * options = model->getRTraceOptions();

    // check type
    if (n == 1) {
      checkArgType(L, LUA_TSTRING, 1);
      std::string filename = std::string(lua_tostring(L, 1));
      options->print(&filename[0]);
    }
    else {
	  options->print(NULL); // to STDOUT
    }

	return 0;	
}

int setRtraceOptions(lua_State *L)
{
	// Check nuber of arguments
    checkNArguments(L, 1);

	// Check type
    checkArgType(L, LUA_TTABLE, 1);
    
    EmpModel * model = getCurrentModel(L);
    RTraceOptions * options = model->getRTraceOptions();
    
    // Fill the table
    fillOptionsFromLuaTable(options, L, 1);

	return 0;
	
}
