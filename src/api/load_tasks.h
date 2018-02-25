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

#ifndef API_LOAD_TASKS_H
#define API_LOAD_TASKS_H

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "./common.h"
#include "./tasks.h"



//! Adds a TaskFactory function to the Task Dictionary
/*!
 This allos addint tasks to the task manager from the API
 
 @author German Molina
 @param[in] L The lua_State * object
 @param[in] name The name of the task
 @param[in] f The TaskFactory
 */
void registerTask(lua_State * L, const char * name, TaskFactory f);


//! Registers all the available tasks in the API
/*!
@author German Molina
@param[in] L The lua_State * object
*/
void registerTasks(lua_State * L)
{
    registerTask(L, "workplane_illuminance", workplaneIlluminanceFactory);

    registerTask(L, "write_scene_file",writeRadSceneFile);
    
    registerTask(L,"write_model_info",writeRadModelInfo);
    
    registerTask(L,"write_rif_file",writeRadRifFile);
    
    registerTask(L,"write_components",writeRadComponentDefinitions);
    
    registerTask(L,"write_views",writeRadViews);
    
    registerTask(L,"write_current_sky",writeRadCurrentSky);
    
    registerTask(L,"write_current_weather",writeRadCurrentWeather);

    registerTask(L,"write_materials",writeRadMaterials);
    
    registerTask(L,"write_layers",writeRadLayers);

    registerTask(L,"write_photosensors",writeRadPhotosensors);

    registerTask(L,"write_workplane",writeRadWorkplane);
}

#endif
