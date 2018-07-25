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


#include "./common.h"
#include "./df.h"



int workplaneDF(lua_State * L)
{
    ENSURE_MINIMUM_WORKPLANE_METRIC_DATA
    
    double min = getDoubleFromTableField(L, 1, "min_percent");
    double max = getDoubleFromTableField(L, 1, "max_percent");
    
    CheckDFCompliance * t = new CheckDFCompliance(name,model, rtraceOptions, wp,min,max);
    t->reportResults = true;
    
    tm->addTask( t );
    
    return 0;
}

