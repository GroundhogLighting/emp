
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


#include "./ghm_commands/options.h"
#include "./ghm_commands/gh_model.h"


//! Registers all the available commands in the API
/*!
 @author German Molina
 @param[in] L The lua_State * object
 */
void registerCommands(lua_State * L)
{
    
    
    /* ============================== */
    /* @APIgroup GROUNDHOG MODEL DATA */
    /* ============================== */
    
    /* @APIfunction
     
     Retrieves an array with the workplanes names in the model
     
     @return workplane_array An array with the workplanes names
     */
    lua_register(L, "get_workplanes_list", get_workplane_list);
    
    /* @APIfunction
     
     Checks if a workplane does exist in the model
     
     @param[required] workplane_name The name of the workplane
     @return exist? True or False
     */
    lua_register(L, "workplane_exist", workplane_exists);
    
    
    /* =============================== */
    /* @APIgroup SET-OPTIONS FUNCTIONS */
    /* =============================== */
    
    /* @APIfunction
     
     Modifies the ray-tracing options in the current GroundhogModel
     
     @param[required] options A Table with the ray-tracing options to set
     */
    lua_register(L, "ray_trace_options", set_rtrace_options);
    
    /* @APIfunction
     Prints the current ray-trace opcions. If a file is given, the options
     will be printed to such file. If not, the options will be printed
     to the Standard Output.
     
     @param[optional] file The name of the file to write
     */
    lua_register(L, "print_ray_trace_options", print_rtrace_options);
    
   
    
    
}

#endif
