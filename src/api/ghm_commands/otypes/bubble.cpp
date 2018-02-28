
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

#include "./bubble.h"
#include "../../utils/common.h"
#include "../../utils/get_layer.h"
#include "../../utils/create_otype.h"

void fillData(Bubble * o, lua_State * L, int tableIndex)
{
    o->center = getPointFromTableField(L, tableIndex, "center");
    o->radius = getNumberFromTableField(L,tableIndex,"radius");
}

int createBubble(lua_State * L)
{
    createOtype(L,"bubble");        
    return 1;
}

