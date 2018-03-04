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

#include "./static_calculation.h"
#include "../../utils/common.h"
#include "../../utils/optionset_ext.h"
#include "../../utils/get_workplane.h"

int workplaneIlluminance(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Get the name
    std::string wpName = getStringFromTableField(L, 1, "workplane");
    
    // Get workplane
    Workplane * wp = getWorkplane(L,&wpName);

    // Get the model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the RTrace options
    RTraceOptions * rtraceOptions = model->getRTraceOptions();

    // Create OconvOptions
    OconvOptions oconvOptions = OconvOptions();
    
    // Create Other Options
    OptionSet otherOptions = OptionSet();
    otherOptions.addOption("workplane", "none");
    otherOptions.addOption("sky", "gendaylit -ang 50 50 -W 500 200");
  
    // Fill options
    fillOptionsFromLuaTable(&otherOptions, L, 1);
    fillOptionsFromLuaTable(&oconvOptions, L, 1);

    // Check that the workplane exists    
    std::string sky = otherOptions.getOption<std::string>("sky");
    

    RTraceTask * t = new RTraceTask(model, rtraceOptions, wp, &oconvOptions, sky);
    t->reportResults = true;
    
    // Get task manager
    TaskManager * tm = getCurrentTaskManager(L);
    tm->addTask(t);

    return 0;
}

int daylightFactor(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Get the name
    std::string wpName = getStringFromTableField(L, 1, "workplane");
    
    // Get workplane
    Workplane * wp = getWorkplane(L,&wpName);
    
    // Retrieve model
    GroundhogModel * model = getCurrentModel(L);

    // Get the RTrace options
    RTraceOptions * rtraceOptions = model->getRTraceOptions();

    // Get TaskManager
    TaskManager * tm = getCurrentTaskManager(L);
    
    CalculateDaylightFactor * t = new CalculateDaylightFactor(model, rtraceOptions, wp);
    t->reportResults = true;
    
    tm->addTask( t );
    
    return 0;
}
