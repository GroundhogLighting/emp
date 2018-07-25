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

#include "emp_core.h"
#include "./get_otype.h"
#include "./common.h"

const Otype * const getOtype(lua_State * L, std::string * objectName)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    GroundhogModel * model = getCurrentModel(L);
    const Otype * object = model->getOtypeByName(objectName);
    
    if (object == nullptr) {
        std::string errmsg = "Object '" + *objectName + "' does not exist";
        sendError(L, "No Object", &errmsg[0]);
    }
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    return object;
}
