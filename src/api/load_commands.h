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
#ifndef API_LOAD_COMMANDS_H
#define API_LOAD_COMMANDS_H

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


// Other
#include "./commands/tasks_manager.h"
#include "./commands/rvu.h"

// Tasks
#include "./commands/tasks/to_radiance.h"
#include "./commands/tasks/df.h"
#include "./commands/tasks/lux.h"
#include "./commands/tasks/udi.h"
#include "./commands/tasks/ase.h"
#include "./commands/tasks/da.h"
#include "./commands/tasks/cumulative_sky.h"

// Basic IO
#include "./commands/io/api_io.h"

// EmpModel data
#include "./commands/model/componentdefinition.h"
#include "./commands/model/componentinstance.h"
#include "./commands/model/layer.h"
#include "./commands/model/workplane.h"
#include "./commands/model/location.h"
#include "./commands/model/material.h"
#include "./commands/model/otype.h"
#include "./commands/model/rtraceoptions.h"
#include "./commands/model/view.h"
#include "./commands/model/workplane.h"
#include "./commands/model/tasks.h"


// Otype
#include "./commands/model/otypes/bubble.h"
#include "./commands/model/otypes/cone.h"
#include "./commands/model/otypes/cup.h"
#include "./commands/model/otypes/cylinder.h"
#include "./commands/model/otypes/face.h"
#include "./commands/model/otypes/ring.h"
#include "./commands/model/otypes/source.h"
#include "./commands/model/otypes/sphere.h"
#include "./commands/model/otypes/tube.h"

// Materials
#include "./commands/model/materials/dielectric.h"
#include "./commands/model/materials/glass.h"
#include "./commands/model/materials/glow.h"
#include "./commands/model/materials/interface.h"
#include "./commands/model/materials/light.h"
#include "./commands/model/materials/metal.h"
#include "./commands/model/materials/plastic.h"
#include "./commands/model/materials/spotlight.h"
#include "./commands/model/materials/trans.h"

// Generators
#include "./commands/model/generators/genbox.h"



//! Registers all the available commands in the API
/*!
@author German Molina
@param[in] L The lua_State * object
*/
void registerCommands(lua_State * L)
{
  

    

    /* ======================== */
    // @APIgroup INPUT / OUTPUT
    /* ======================== */
    
    
    /* @APIfunction
     
     Prints a warning to the standard error, but continues processing the
     script. This function can be used for informing the user of any
     possible anomaly or probable misstake.
     
     @param[required] message The message to warn
     */
    lua_register(L, "warn", warn);
    
    /* @APIfunction
     
     Transforms a certain value into a detailed string. This works
     very simply for strings and numbers. Tables are transformed
     into JSON. However, Lua tables are more flexible
     than JSON objects... so take care of that.
     
     @param[required] value The value to inspect
     @return stringified The object in string format
     
     @example
     r = inspect("car")
     print( r )
     
     --[[
     
     "car"
     
     ]]
     @endexample
     
     @example
     r = inspect(1)
     print( r )
     
     --[[
     
     1
     
     ]]
     @endexample
     
     @example
     r = inspect({1,2,3})
     print( r )
     --[[
     
     [
     1.0,
     2.0,
     3.0
     ]
     
     ]]
     @endexample
     
     @example
     r = inspect({
     a = 1; b = 2; c = 3;
     })
     print( r )
     --[[
     
     {
     "a": 1.0,
     "b": 2.0,
     "c": 3.0
     }
     
     ]]
     @endexample
     */
    lua_register(L, "inspect", printValue);
    
    
    /* ====================== */
    // @APIgroup TASK MANAGER
    /* ====================== */

    /* @APIfunction

     Solves the task manager and prints the JSON results into a file.
     If no file name is provided, the results are put in the stdout.

     The tasks are not purged after solving... you may want to use the purge_tasks
     method for that.
     
    @param[optional] The name of the file to put the results.
    */
    lua_register(L, "solve", solveTaskManager);

    /* @APIfunction

    Prints the current task flow to the standard output
    */
    lua_register(L, "print_task_flow", printTaskManager);

    /* @APIfunction

    Removes all tasks from the Task Manager
    */
    lua_register(L, "purge_tasks", cleanTaskManager);

    
    
    
    /* ============================== */
    // @APIgroup EMP MODEL DATA
    /* ============================== */
    
    /* @APIfunction
     
     Retrieves an array with the workplanes names in the model
     
     @return workplanes An array with the workplanes names
     */
    lua_register(L, "get_workplanes_list", getWorkplanesList);
    
    /* @APIfunction
     
     Retrieves a table with the workplane information in the model.
     That is, name, maximum size of pixel (triangulation), tasks, etc.
     
     @return workplanes An array with the workplanes names
     */
    lua_register(L, "get_workplanes_data", getWorkplanesData);
    
    /* @APIfunction
     
     Checks if a workplane does exists in the model
     
     @param[required] workplane_name The name of the workplane
     @return exist True or False
     */
    lua_register(L, "is_workplane", workplaneExists);
    
    /* @APIfunction
     
     Counts the number of polygons in a workplane
     
     @param[required] workplane_name The name of the workplane
     @return n_polygons The number of polygons
     */
    lua_register(L, "count_workplane_polygons",countWorkplanePolygons);
    
    /* @APIfunction
     
     Creates a new Workplane
     
     @param[required] workplane_name The name of the workplane
     */
    lua_register(L, "workplane",createWorkplane);
    
    /* @APIfunction
     
     Retrieves an array with the metrics
     
     @return metrics The metrics
     */
    lua_register(L, "get_metrics",getTasks);
    
    /* @APIfunction
     
     Retrieves a single metric
     
     @param[required] name The name of the metric to retrieve
     @return a_metric The metric
     */
    lua_register(L, "get_metric",getTask);
    
    /* @APIfunction
     
     Retrieves an array with the layer names in the model
     
     @return layer_names An array with the layer names
     */
    lua_register(L, "get_layers_list", getLayersList);
    
    /* @APIfunction
     
     Checks if a layer does exist in the model
     
     @param[required] layer_name The name of the workplane
     @return exist True or False
     */
    lua_register(L, "is_layer", layerExists);
    
    /* @APIfunction
     
     Counts the number of objects in a layer
     
     @param[required] layer_name The name of the layer
     @return count The number of objects
     */
    lua_register(L, "count_layer_objects",countLayerObjects);
    
    /* @APIfunction
     
     Counts the number of ComponentInstances in a layer
     
     @param[required] layer_name The name of the layer
     @return count The number of ComponentInstances
     */
    lua_register(L, "count_layer_instances",countLayerInstances);
    
    
    /* @APIfunction
     
     Retrieves an array with the ComponentDefinition names in the model
     
     @return definitions An array with the ComponentDefinition names
     */
    lua_register(L, "get_component_definitions_list", getComponentDefinitionsList);
    
    /* @APIfunction
     
     Checks if a ComponentDefinition does exist in the model
     
     @param[required] name The name of the ComponentDefinition
     @return exist True or False
     */
    lua_register(L, "is_component_definition", componentDefinitionExists);
    
    /* @APIfunction
     
     Adds a Component Definition to the model
     
     @param[required] name The name of the ComponentDefinition
     @return a_component The name of the component definition
     */
    lua_register(L, "component", createComponentDefinition);
    
    
    /* @APIfunction
     
     Counts the number of objects in a ComponentDefinition
     
     @param[required] name The name of the ComponentDefinition
     @return count The number of objects
     */
    lua_register(L, "count_component_definition_objects",countComponentDefinitionObjects);
    
    /* @APIfunction
     
     Counts the number of ComponentInstances in a ComponentDefinition
     
     @param[required] name The name of the ComponentDefinition
     @return count The number of ComponentInstances
     */
    lua_register(L, "count_component_definition_instances",countComponentDefinitionInstances);
    
    /* @APIfunction
     
     Retrieves a table with the location of the model, containing: latitude, longitude,
     time_zone, city, country, albedo and elevation fields.
     
     @return location A table with the location data
     */
    lua_register(L, "get_location_data",getLocation);
    
    /* @APIfunction
     
     Retrieves a list of all the material names in the model
     
     @return materials A list with all the names of the materials
     */
    lua_register(L, "get_materials_list",getMaterialsList);
    
    
    /* @APIfunction
     
     Checks if a material exists in the model
     
     @param[required] name The name of the material
     @return is_material A list with all the names of the materials
     */
    lua_register(L, "is_material", materialExists);
    
    /* @APIfunction
     
     Gets the class of a certain material
     
     @param[required] name The name of the material
     @return mat_class A list with all the names of the materials
     */
    lua_register(L, "get_material_class", getMaterialType);
    
    /* @APIfunction
     
     Checks if an object exists in the model
     
     @param[required] name The name of the object
     @return is_object Is it?
     */
    lua_register(L, "is_object", otypeExists);
    
    /* @APIfunction
     
     Gets the class of a certain object
     
     @param[required] name The name of the material
     @return obj_class A list with all the names of the materials
     */
    lua_register(L, "get_object_class", getOtypeType);
    
    /* @APIfunction
     
     Adds a new Layer object to the EmpModel
     
     @param[required] name The name of the layer
     @return layer The name of the created layer
     */
    lua_register(L, "layer", createLayer);
    
    
    /* @APIfunction
     
     Adds a new Bubble object to the EmpModel
     
     @param[required] data The table with the data
     @return a_bubble A table with the object information at time of creation
     */
    lua_register(L, "bubble", createBubble);
    
    /* @APIfunction
     
     Adds a new Cone object to the EmpModel
     
     @param[required] data The table with the data
     @return a_cone A table with the object information at time of creation
     */
    lua_register(L, "cone", createCone);
    
    /* @APIfunction
     
     Adds a new Cup object to the EmpModel
     
     @param[required] data The table with the data
     @return a_cup A table with the object information at time of creation
     */
    lua_register(L, "cup", createCup);
    
    /* @APIfunction
     
     Adds a new Cylinder object to the EmpModel
     
     @param[required] data The table with the data
     @return a_cylinder A table with the object information at time of creation
     */
    lua_register(L, "cylinder", createCylinder);
    
    /* @APIfunction
     
     Adds a new Polygon object to the EmpModel
     
     @param[required] data The table with the data
     @return a_polygon A table with the object information at time of creation
     */
    lua_register(L, "polygon", createFace);
    
    /* @APIfunction
     
     Adds a new Ring object to the EmpModel
     
     @param[required] data The table with the data
     @return a_ring A table with the object information at time of creation
     */
    lua_register(L, "ring", createRing);
    
    /* @APIfunction
     
     Adds a new Source object to the EmpModel
     
     @param[required] data The table with the data
     @return a_source A table with the object information at time of creation
     */
    lua_register(L, "source", createSource);
    
    /* @APIfunction
     
     Adds a new Sphere object to the EmpModel
     
     @param[required] data The table with the data
     @return a_sphere A table with the object information at time of creation
     */
    lua_register(L, "sphere", createSphere);
    
    /* @APIfunction
     
     Adds a new Tube object to the EmpModel
     
     @param[required] data The table with the data
     @return a_tube A table with the object information at time of creation
     */
    lua_register(L, "tube", createTube);
    
    /* @APIfunction
     
     Adds a new Dielectric material to the EmpModel
     
     @param[required] data The table with the data
     @return a_dielectric The name of the material
     */
    lua_register(L, "dielectric", createDielectric);
    
    /* @APIfunction
     
     Adds a new Glass material to the EmpModel
     
     @param[required] data The table with the data
     @return a_glass The name of the material
     */
    lua_register(L, "glass", createGlass);
    
    /* @APIfunction
     
     Adds a new Glow material to the EmpModel
     
     @param[required] data The table with the data
     @return a_glow The name of the material
     */
    lua_register(L, "glow", createGlow);
    
    /* @APIfunction
     
     Adds a new Interface material to the EmpModel
     
     @param[required] data The table with the data
     @return an_interface The name of the material
     */
    lua_register(L, "interface", createInterface);
    
    /* @APIfunction
     
     Adds a new Light material to the EmpModel
     
     @param[required] data The table with the data
     @return a_light The name of the material
     */
    lua_register(L, "light", createLight);
    
    /* @APIfunction
     
     Adds a new Metal material to the EmpModel
     
     @param[required] data The table with the data
     @return a_metal The name of the material
     */
    lua_register(L, "metal", createMetal);
    
    
    /* @APIfunction
     
     Adds a new Plastic material to the EmpModel
     
     @param[required] data The table with the data
     @return a_plastic The name of the material
     */
    lua_register(L, "plastic", createPlastic);
    
    /* @APIfunction
     
     Adds a new Spotlight material to the EmpModel
     
     @param[required] data The table with the data
     @return a_spotlight The name of the material
     */
    lua_register(L, "spotlight", createSpotlight);
    
    /* @APIfunction
     
     Adds a new Trans material to the EmpModel
     
     @param[required] data The table with the data
     @return a_trans The name of the material
     */
    lua_register(L, "trans", createTrans);
    
    /* @APIfunction
     
     Adds a new View to the EmpModel
     
     @param[required] data The table with the data
     @return view The name of the view
     */
    lua_register(L, "view", createView);
    
    /* @APIfunction
     
     Returns a list of the views' names
     
     @param[required] data The table with the data
     @return views An array with the names of the views in the model
     */
    lua_register(L, "get_views_list", getViewsList);
    
    /* @APIfunction
     
     Returns a list of the views' names
     
     @param[required] data The table with the data
     @return is_a_view Does the view exist in the model?
     */
    lua_register(L, "is_view", viewExists);
    
    /* @APIfunction
     
     Returns a list of the views' names
     
     @param[required] data The table with the data
     */
    lua_register(L, "box", genBox);
    
    /* @APIfunction
     
     Creates a new ComponentInstancex
     
     @param[required] data The table with the data
     */
    lua_register(L, "instance", createComponentInstance);
    
    
    /* =============================== */
    // @APIgroup SET-OPTIONS FUNCTIONS
    /* =============================== */
    
    /* @APIfunction
     
     Modifies the ray-tracing options in the current EmpModel
     
     @param[required] options A Table with the ray-tracing options to set
     */
    lua_register(L, "ray_trace_options", setRtraceOptions);
    
    /* @APIfunction
     Prints the current ray-trace opcions. If a file is given, the options
     will be printed to such file. If not, the options will be printed
     to the Standard Output.
     
     @param[optional] file The name of the file to write
     */
    lua_register(L, "print_ray_trace_options", printRtraceOptions);
    
    
    /* ============================ */
    // @APIgroup EXPORT TO RADIANCE
    /* ============================ */

    /* @APIfunction

    Adds a task to the task manager

    @param[required] task_name The name of the task to add
    @param[required] options The options given
    */
    lua_register(L,"write_scene_file", writeRadSceneFile);

    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_model_info", writeRadModelInfo);
    
    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_rif_file", writeRadRifFile);

    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_components", writeRadComponentDefinitions);
    
    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_views", writeRadViews);
    
    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_current_sky", writeRadCurrentSky);
    
    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_current_weather", writeRadCurrentWeather);
    
    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_materials", writeRadMaterials);
    
    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_layers", writeRadLayers);
    
    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_photosensors", writeRadPhotosensors);
    
    /* @APIfunction
     
     Adds a task to the task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"write_workplane", writeRadWorkplane);
    
    
    /* ===================== */
    // @APIgroup RAY-TRACING
    /* ===================== */
    
    /* @APIfunction
     
     Pushes a Calculate Workplane Illuminance task to the
     task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"workplane_illuminance", workplaneIlluminance);
    
    /* @APIfunction
     
     Pushes a Calculate Workplane Daylight Factor task to the
     task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"workplane_df", workplaneDF);
    
    /* @APIfunction
     
     Pushes a Calculate Workplane Useful Daylight Illuminance task to the
     task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"workplane_udi", workplaneUDI);
    
    /* @APIfunction
     
     Pushes a Calculate Workplane Daylight Autonomy task to the
     task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"workplane_da", workplaneDA);
    
    /* @APIfunction
     
     Pushes a Calculate Workplane Annual Sunlight Exposure task to the
     task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"workplane_ase", workplaneASE);
    
    /* @APIfunction
     
     Pushes a Calculate Annual Solar Irradiation task to the
     task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"workplane_solar_irradiation", workplaneSolarIrradiation);
    
    /* @APIfunction
     
     Pushes a Calculate Annual Daylight Exposure task to the
     task manager
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"workplane_daylight_exposure", workplaneDaylightExposure);
    
    
    
    /* @APIfunction
     
     Pushes a generic Workplane metric to the Task Manager. This is an
     alternative method to workplane_ase, workplane_da, etc.
     
     @param[required] task_name The name of the task to add
     @param[required] options The options given
     */
    lua_register(L,"push_metric", pushJSONMetric);
    
    
    /* ====================== */
    // @APIgroup OTHER
    /* ====================== */
    
    /* @APIfunction
     
     Calls RVU program
     */
    lua_register(L, "review", review);
    
    
    
    

  


}

#endif
