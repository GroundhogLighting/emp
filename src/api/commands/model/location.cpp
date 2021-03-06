
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

#include "./layer.h"
#include "../../utils/common.h"


int getLocation(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 0);
    
    EmpModel * model = getCurrentModel(L);
    
    Location * l = model->getLocation();
    
    
    // Create the table
    lua_newtable(L); // index = 1
    
    // push fields
    lua_pushnumber(L, l->getLatitude());
    lua_setfield(L, 1, "latitude");
    
    lua_pushnumber(L, l->getLongitude());
    lua_setfield(L, 1, "longitude");
    
    lua_pushnumber(L, l->getTimeZone());
    lua_setfield(L, 1, "time zone");
    
    lua_pushnumber(L, l->getAlbedo());
    lua_setfield(L, 1, "albedo");
    
    lua_pushnumber(L, l->getElevation());
    lua_setfield(L, 1, "elevation");
    
    lua_pushstring(L, l->getCity().c_str());
    lua_setfield(L, 1, "city");
    
    lua_pushstring(L, l->getCountry().c_str());
    lua_setfield(L, 1, "country");
    
    lua_pushnumber(L, model->getNorthCorrection());
    lua_setfield(L, 1, "north correction");
    
    
    return 1;
}
