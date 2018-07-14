
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


#include "./common.h"


int workplaneASE(lua_State * L)
{
    ENSURE_MINIMUM_WORKPLANE_METRIC_DATA
    ENSURE_WEATHER
  
    double minLux = getDoubleFromTableField(L,1,MIN_LUX_FIELD);
    double early = getDoubleFromTableField(L,1,EARLY_FIELD);
    double late = getDoubleFromTableField(L,1,LATE_FIELD);
    int firstMonth = getIntFromTableField(L,1,FIRST_MONTH_FIELD);
    int lastMonth = getIntFromTableField(L,1,LAST_MONTH_FIELD);
    float minTime  = getFloatFromTableField(L,1,MIN_TIME_FIELD);
    
    CheckASECompliance * t = new CheckASECompliance(name,model,rtraceOptions,wp,6,minLux,early,late,firstMonth,lastMonth,minTime);
    t->reportResults = true;
    
    // Get task manager
    tm->addTask(t);
    
    return 0;
}

