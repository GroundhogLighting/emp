
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

#include "./metal.h"
#include "../../../utils/common.h"
#include "../../../utils/get_layer.h"
#include "../../../utils/create_material.h"

void fillData(Metal * m, lua_State * L, int tableIndex)
{
    getColorFromTableField(L, tableIndex,"color", &(m->r), &(m->g),&(m->b));
    m->specularity = getNumberFromTableField(L, tableIndex, "specularity");
    m->roughness = getNumberFromTableField(L, tableIndex, "roughness");
}

int createMetal(lua_State * L)
{
    return createMaterial(L,"metal");    
}






