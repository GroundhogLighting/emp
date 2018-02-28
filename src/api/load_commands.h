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
#ifndef API_LOAD_COMMANDS_H
#define API_LOAD_COMMANDS_H

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}



#include "./commands/tasks_manager.h"
#include "./commands/rvu.h"

//! Registers all the available commands in the API
/*!
@author German Molina
@param[in] L The lua_State * object
*/
void registerCommands(lua_State * L)
{
  

    /* ====================== */
    /* @APIgroup TASK MANAGER */
    /* ====================== */
    
    /* @APIfunction
     
     Solves the task manager
     */
    lua_register(L, "review", review);

    /* ====================== */
    /* @APIgroup TASK MANAGER */
    /* ====================== */

    /* @APIfunction

    Solves the task manager
    */
    lua_register(L, "solve", solveTaskManager);

    /* @APIfunction

    Prints the current task flow to the standard output
    */
    lua_register(L, "print_task_flow", printTaskManager);

    /* @APIfunction

    Removes current tasks from Task Manager
    */
    lua_register(L, "purge_tasks", solveTaskManager);

    /* @APIfunction

    Adds a task to the task manager

    @param[required] task_name The name of the task to add
    @param[required] options The options given
    */
    lua_register(L, "task", addTask);




  


}

#endif
