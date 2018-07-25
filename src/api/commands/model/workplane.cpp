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

#include "./workplane.h"
#include "../../utils/common.h"
#include "../../utils/get_workplane.h"


int getWorkplanesList(lua_State * L)
{
    // Check nuber of arguments
    checkNArguments(L, 0);
    
	GroundhogModel * model = getCurrentModel(L);
	size_t nwps = model->getNumWorkplanes();

	// Create the table
	lua_newtable(L); // index = 1
	
	// push workplane names
	for (size_t i = 0; i < nwps; i++) {
        std::string name = model->getWorkplaneRef(i)->getName();
		lua_pushstring(L, &name[0]);
		lua_seti(L, 1, i+1); 
	}

	return 1;
}


int getWorkplanesData(lua_State * L)
{
    // Check nuber of arguments
    checkNArguments(L, 0);
    
    GroundhogModel * model = getCurrentModel(L);
    size_t nwps = model->getNumWorkplanes();
    
    // Create the table
    lua_newtable(L); // stack = 1
    
    // push workplane names
    for (size_t i = 0; i < nwps; i++) {
        // Retrive workplane
        const Workplane * wp = model->getWorkplaneRef(i);
        
        // Create a table that will contain this workplane
        lua_newtable(L); // stack = 2
        
        // Push name
        std::string name = wp->getName();
        lua_pushstring(L, &name[0]);
        lua_setfield(L, 2, "name");
        
        // Push maxArea
        double maxArea = wp->getMaxArea();
        lua_pushnumber(L, maxArea);
        lua_setfield(L, 2, "pixel_size");

        // Push tasks
        const std::vector<std::string> * tasks = wp->getTasks();
        size_t nTasks = tasks->size();
        lua_newtable(L); // stack = 3
        for(size_t j = 1; j <= nTasks; j++){
            std::string task = tasks->at(j-1);
            lua_pushstring(L, task.c_str());
            lua_seti(L,3,j);
        }
        
        lua_setfield(L, 2, "tasks");
        
        // Put the table in the array
        lua_seti(L,1,i+1);
        
    }
    
    return 1;
}


int countWorkplanePolygons(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string wpName = lua_tostring(L, 1);
    
    // Check if workplane exists
    Workplane * wp = getWorkplane(L,&wpName);
    
    lua_pushnumber(L,wp->getNumPolygons());
    
    
    return 1;
}

int workplaneExists(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);

    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);

    // Retrieve the first argument
	std::string wpName = lua_tostring(L, 1);

    GroundhogModel * model = getCurrentModel(L);
    
    // Check if workplane exists
	bool exists = (model->getWorkplaneByName(&wpName) != nullptr);
	
    // Push the result
	lua_pushboolean(L, exists);

    // return
	return 1;
}

int createWorkplane(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Get name
    std::string name = requireNameFromTable(L,1);
    
    // Get model
    GroundhogModel * model = getCurrentModel(L);

    // Create a new polygon
    Polygon3D * polygon = new Polygon3D();
    
    
    /* FILL EXTERIOR LOOP */
    Loop * exterior = polygon->getOuterLoopRef();
    
    std::vector <Point3D> extPoints = getVectorOfPointsFromTableField(L, 1, "vertices");
    
    size_t nExtPoints = extPoints.size();
    
    if(nExtPoints < 3){
        std::string eMsg = "Exterior loop of a Workplane requires at least three vertices... only "+std::to_string(nExtPoints) + " were given";        
        usageError(L, eMsg);
    }
    
    for(size_t i = 0; i<nExtPoints; i++){
        Point3D p = extPoints.at(i);
        exterior->addVertex(new Point3D(p.getX(),p.getY(),p.getZ()));
    }
    
    /* FILL INTERIOR LOOPS, IF THEY EXSIST */
    size_t innerLoopCount = 0;
    while(fieldExists(L, 1, "hole"+std::to_string(++innerLoopCount))){
        
        // Build the name of the field
        std::string loopName = "hole"+std::to_string(innerLoopCount);
        
        // Add the loop to the polygon
        Loop * loop = polygon->addInnerLoop();
        
        // Retrieve the points in that loop
        std::vector <Point3D> points = getVectorOfPointsFromTableField(L, 1, loopName.c_str());
        
        // Check number of points
        size_t nPoints = points.size();
        if(nPoints < 3){
            std::string eMsg = "Holes in a Workplane require at least three vertices... only "+std::to_string(nPoints) + " were given";
            usageError(L, eMsg);
        }
        
        // Add them
        for(size_t i = 0; i<nPoints; i++){
            Point3D p = points.at(i);
            loop->addVertex(new Point3D(p.getX(),p.getY(),p.getZ()));
        }
        
    }
    
    if(fieldExists(L, 1, "normal")){
        polygon->setNormal(getVectorFromTableField(L,1,"normal"));
    }else{
        // Try to calculate the normal
        polygon->setNormal();
        putVectorIntoTable(L,1,"normal",polygon->getNormal());
    }
    
    model->addPolygonToWorkplane(&name, polygon);
    
    // return name
    lua_pushstring(L,name.c_str());
    
    // And the table
    lua_pushvalue(L,1);
    
    
    return 2;
}
