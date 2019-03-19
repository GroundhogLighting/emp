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

#include "./tasks.h"
#include "../../utils/common.h"

int getTasks(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 0);
    
    // Get model
    EmpModel * model = getCurrentModel(L);
    
    size_t nTasks = model->countTasks();
    
    json j = json::array();
    
    for(size_t i=0; i<nTasks; i++){
        const json * task = model->getTask(i);
        j.push_back(*task);
    }
    
    jsonToTable(L, &j);
    
    return 1;
}

int getTask(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check argument type
    checkArgType(L, LUA_TSTRING, 1);
    
    // Get argument
    const char * taskName = lua_tostring(L,1);
    
    // Get model
    EmpModel * model = getCurrentModel(L);
    
    const json * task = model->getTask(taskName);
    if(task == nullptr){
        std::string err = "Task "+std::string(taskName) + " does not exist in the model.";
        usageError(L, err);
    }
    
    // Build table
    jsonToTable(L, task);
    
    return 1;
}



