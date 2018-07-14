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
#include "../../utils/get_workplane.h"
#include "../../utils/common.h"
#include "../../utils/optionset_ext.h"

#define ENSURE_MINIMUM_WORKPLANE_METRIC_DATA \
    checkNArguments(L, 1); \
    checkArgType(L, LUA_TTABLE, 1); \
    std::string name = getStringFromTableField(L, 1, "name"); \
    std::string wpName = getStringFromTableField(L, 1, "workplane"); \
    Workplane * wp = getWorkplane(L,&wpName); \
    GroundhogModel * model = getCurrentModel(L); \
    RTraceOptions * rtraceOptions = model->getRTraceOptions(); \
    TaskManager * tm = getCurrentTaskManager(L);

#define ENSURE_WEATHER if(!model->getLocation()->hasWeather()){usageError(L,"The model has no weather, but user is trying to simulate a Climate Based Daylight Metric");}

#define FIRST_MONTH_FIELD "first_month"
#define LAST_MONTH_FIELD "last_month"
#define EARLY_FIELD "early"
#define LATE_FIELD "late"
#define MIN_LUX_FIELD "min_lux"
#define MAX_LUX_FIELD "max_lux"
#define MIN_TIME_FIELD "expected_time"
