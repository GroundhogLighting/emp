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

#include <iostream>
#include <map>

#include "emp_core.h"
#include "./tasks_manager.h"
#include "../utils/common.h"

#include "./tasks/df.h"
#include "./tasks/lux.h"
#include "./tasks/da.h"
#include "./tasks/udi.h"
#include "./tasks/ase.h"

int solveTaskManager(lua_State * L)
{
  json results = json();
  getCurrentTaskManager(L)->solve(&results);
  return 0;
}

int printTaskManager(lua_State * L)
{
  // Check if any input was given
  int nargs[2] = { 0, 1 };
  int n = checkNArguments(L, nargs, 2);

  // check type
  if (n == 1) {
    checkArgType(L, LUA_TSTRING, 1);
    std::string filename = std::string(lua_tostring(L, 1));
      
    getCurrentTaskManager(L)->print(&filename[0]);
  }
  else {
    getCurrentTaskManager(L)->print(NULL); // to STDOUT
  }

  return 0;
}

int cleanTaskManager(lua_State * L)
{
    getCurrentTaskManager(L)->clean();
    
    return 0;
}


int pushJSONMetric(lua_State * L)
{
    // Check number of arguments
    checkNArguments(L, 1);
    
    // Check type
    checkArgType(L, LUA_TTABLE, 1);
    
    // Get class field
    std::string className = getStringFromTableField(L, 1, "class");
    
    // Do what should be done
    if(className == "UDI" || className == "Useful Daylight Illuminance"){
        return workplaneUDI(L);
        
    }else if(className == "DA" || className == "Daylight Autonomy"){
        return workplaneDA(L);
        
    }else if(className == "Clear sky illuminance"){
        return clearSkyWorkplaneIlluminance(L);
        
    }else if(className == "Intermediate sky illuminance"){
        return intermediateSkyWorkplaneIlluminance(L);
        
    }else if(className == "Overcasts sky illuminance"){
        return overcastSkyWorkplaneIlluminance(L);
        
    }else if(className == "Weather sky illuminance"){
        return perezSkyWorkplaneIlluminance(L);
        
    }else if(className == "DF" || className == "Daylight Factor"){
        return workplaneDF(L);
        
    }else if(className == "ASE" || className == "Annual Sunlight Exposure"){
        return workplaneASE(L);
        
    }else {
        std::string err = "Unknown metric class '"+className+"'";
        usageError(L, err);
    }
    return 0;
}
