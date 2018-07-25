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

int workplaneIlluminance(lua_State * L)
{
    ENSURE_MINIMUM_WORKPLANE_METRIC_DATA

    // Create OconvOptions
    OconvOptions oconvOptions = OconvOptions();
    
    // Fill options
    fillOptionsFromLuaTable(&oconvOptions, L, 1);

    
    std::string sky = getStringFromTableField(L, 1, "sky");
    double min = getDoubleFromTableField(L, 1, MIN_LUX_FIELD);
    double max = getDoubleFromTableField(L, 1, MAX_LUX_FIELD);
    
    CheckLUXCompliance * t = new CheckLUXCompliance(name,model, rtraceOptions, wp, &oconvOptions, sky, min, max);
    t->reportResults = true;
    
    // Get task manager
    tm->addTask(t);

    return 0;
}

#define GET_SKY_OPTIONS \
std::string month = std::to_string(getIntFromTableField(L, 1, "month"));\
std::string day = std::to_string(getIntFromTableField(L, 1, "day"));\
std::string hour = std::to_string(getFloatFromTableField(L, 1, "hour"));\
Location * location = model->getLocation();\
std::string latitude = std::to_string(location->getLatitude());\
std::string longitude = std::to_string(location->getLongitude());\
std::string meridian = std::to_string(-15*location->getTimeZone());\
std::string albedo = std::to_string(location->getAlbedo());\


#define PUSH_GENSKY(x) \
std::string sky = "gensky "+month+" "+day+" "+hour+" +s -g "+albedo+" -a "+latitude+" -o " + longitude +" -m "+meridian;\
lua_pushstring(L,sky.c_str());\
lua_setfield(L,1,"sky");

int clearSkyWorkplaneIlluminance(lua_State * L)
{
    ENSURE_MINIMUM_WORKPLANE_METRIC_DATA
    
    GET_SKY_OPTIONS
    
    PUSH_GENSKY(+s)
    
    return workplaneIlluminance(L);
}

int intermediateSkyWorkplaneIlluminance(lua_State * L)
{
    ENSURE_MINIMUM_WORKPLANE_METRIC_DATA
    
    GET_SKY_OPTIONS
    
    PUSH_GENSKY(+i)
    
    return workplaneIlluminance(L);
}

int overcastSkyWorkplaneIlluminance(lua_State * L)
{
    ENSURE_MINIMUM_WORKPLANE_METRIC_DATA
    
    GET_SKY_OPTIONS
    
    PUSH_GENSKY(-c)
    
    return workplaneIlluminance(L);
}

int perezSkyWorkplaneIlluminance(lua_State * L)
{
    ENSURE_MINIMUM_WORKPLANE_METRIC_DATA
    
    GET_SKY_OPTIONS
    
    ENSURE_WEATHER
    
    std::cout << "TODO: Allow location to find a certain time of day, for gendaylit... using -W 500 200 for now" << std::endl;
    
    std::string direct_normal = std::to_string(500);
    std::string diffuse_horizontal = std::to_string(200);
    
    std::string sky = "gendaylit "+month+" "+day+" "+hour+" -W "+direct_normal+" "+diffuse_horizontal+" -g "+albedo+" -a "+latitude+" -o " + longitude +" -m "+meridian;
    
    lua_pushstring(L,sky.c_str());
    lua_setfield(L,1,"sky");

    return workplaneIlluminance(L);
}
