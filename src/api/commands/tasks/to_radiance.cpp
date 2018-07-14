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

#include "./to_radiance.h"
#include "../../utils/common.h"
#include "../../utils/optionset_ext.h"
#include "../../utils/get_workplane.h"

int writeRadSceneFile(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("filename","scene.rad"); // The name of the scene file
    options.addOption("layers_directory","Geometry"); // The directory where the Layers are located
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Add the task
    tm->addTask(new WriteRadianceSceneFile(options.getOption<std::string>("filename"), model, &options));

    return 0;
    
}


int writeRadRifFile(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("filename","scene.rif"); // The name of the RIF file
    options.addOption("layers_directory","Geometry"); // The directory where the Layers are located
    options.addOption("views_directory","Views"); // The directory where the Views are located
    options.addOption("skies_directory","Skies"); // The directory where the Skies and Weathers are located
    options.addOption("materials_directory","Materials"); // The directory where the Materials are located
    options.addOption("materials_file","materials.mat"); // The name of the file that references all materials
    options.addOption("scene_file","scene.rad"); // The name of the scene file
    options.addOption("components_directory","Components"); // The directory where the Components are located
    options.addOption("windows_directory","Windows"); // The directory where the Windows are located
    options.addOption("illums_directory","Illums"); // The directory where the Illums are located
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm->addTask(new WriteRadianceRifFile(options.getOption<std::string>("filename"), model, &options));
    
    return 0;
}



int writeRadModelInfo(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("filename","modelinfo.txt"); // The file to write the model info.
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm->addTask(new WriteModelInfo(options.getOption<std::string>("filename"),model));
    
    return 0;
    
}


int writeRadComponentDefinitions(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("directory","Components"); // The directory to write the Components
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm->addTask( new WriteComponentDefinitions(options.getOption<std::string>("directory"),model));
    
    return 0;
    
}


int writeRadViews(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("directory","Views"); // The directory to write the Views
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm->addTask( new WriteViews(options.getOption<std::string>("directory"),model) );
    
    return 0;
    
}


int writeRadCurrentSky(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("directory","Skies"); // The directory to write the Views
    options.addOption("filename","Sky.rad"); // The name of the file
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm->addTask( new WriteCurrentSky(options.getOption<std::string>("directory"), options.getOption<std::string>("filename"),model) );
    
    return 0;
}



int writeRadCurrentWeather(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("directory","Skies"); // The directory to write the weather
    options.addOption("filename","Sky.rad"); // The name of the file
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm->addTask( new WriteCurrentWeather(options.getOption<std::string>("directory"), options.getOption<std::string>("filename"),model) );
    
    return 0;
}


int writeRadMaterials(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("directory","Materials"); // The directory to write the Materials
    options.addOption("filename","materials.mat"); // The name of the file that references all Materials
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm->addTask( new WriteMaterials(options.getOption<std::string>("directory"), options.getOption<std::string>("filename"),model) );
    
    return 0;
}



int writeRadLayers(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("directory","Geometry"); // The directory to write the Materials
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm->addTask( new WriteLayers(options.getOption<std::string>("directory"), model) );
    
    return 0;
}



int writeRadPhotosensors(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("directory","Photosensors"); // The directory to write the Materials
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
    
    // Get current model
    GroundhogModel * model = getCurrentModel(L);
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm->addTask( new WritePhotosensors(options.getOption<std::string>("directory"), model) );
    
    return 0;
}


int writeRadWorkplane(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Build options
    OptionSet options = OptionSet();
    options.addOption("directory","Workplanes"); // The directory to write the Materials
    options.addOption("workplane","none"); // The name of the workplane to write
    options.addOption("filename","none"); // The name of the resulting file
    
    // Fill the options
    fillOptionsFromLuaTable(&options, L, 1);
        
    // Get the workplane
    std::string wpName = options.getOption<std::string>("workplane");
    Workplane * wp = getWorkplane(L,&wpName);
        
    std::string name = options.getOption<std::string>("filename");
    
    if(name == "none")
        name = wp->getName();
    
    std::string aux = options.getOption<std::string>("directory") + "/" +name;
    
    // Get the Task Manager
    TaskManager * tm = getCurrentTaskManager(L);
    
    // Build the task
    tm -> addTask( new WriteWorkplane(wp, aux) );
    
    return 0;
}
