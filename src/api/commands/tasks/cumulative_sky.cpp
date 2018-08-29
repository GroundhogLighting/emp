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

#include "./cumulative_sky.h"
#include "./common.h"

int workplaneSolarIrradiation(lua_State * L)
{
    ENSURE_MINIMUM_WORKPLANE_METRIC_DATA
    
    // Create OconvOptions
    OconvOptions oconvOptions = OconvOptions();
    
    // Fill options
    fillOptionsFromLuaTable(&oconvOptions, L, 1);
    
    
    double min = getDoubleFromTableField(L, 1, MIN_LUX_FIELD);
    double max = getDoubleFromTableField(L, 1, MAX_LUX_FIELD);
    
    
    CheckSolarIrradiationCompliance * t = new CheckSolarIrradiationCompliance(name, model,rtraceOptions,wp,min,max);
    
    t->reportResults = true;
    
    // Get task manager
    tm->addTask(t);
    
    return 0;
}


int workplaneDaylightExposure(lua_State * L)
{
    ENSURE_MINIMUM_WORKPLANE_METRIC_DATA
    
    // Create OconvOptions
    OconvOptions oconvOptions = OconvOptions();
    
    // Fill options
    fillOptionsFromLuaTable(&oconvOptions, L, 1);
    
    
    double min = getDoubleFromTableField(L, 1, MIN_LUX_FIELD);
    double max = getDoubleFromTableField(L, 1, MAX_LUX_FIELD);
    
    
    CheckDaylightExposureCompliance * t = new CheckDaylightExposureCompliance(name, model,rtraceOptions,wp,min,max);
    
    t->reportResults = true;
    
    // Get task manager
    tm->addTask(t);
    
    return 0;
}
