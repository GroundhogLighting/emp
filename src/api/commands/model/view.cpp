
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

#include "./view.h"
#include "../../utils/common.h"
//#include "../utils/get_view.h"




int getViewsList(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 0);
    
    GroundhogModel * model = getCurrentModel(L);
    size_t nwps = model->getNumViews();
    
    // Create the table
    lua_newtable(L); // index = 1
    
    // push view names
    for (size_t i = 0; i < nwps; i++) {
        std::string * name = model->getViewRef(i)->getName();
        lua_pushstring(L, &name->at(0));
        lua_seti(L, 1, i+1);
    }
    
    return 1;
}

int viewExists(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string viewName = lua_tostring(L, 1);
    
    GroundhogModel * model = getCurrentModel(L);
    
    // Check if workplane exists
    bool exists = (model->getViewByName(&viewName) != nullptr);
    
    // Push the result
    lua_pushboolean(L, exists);
    
    // return
    return 1;
}

int createView(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
        
    // Check the type of argument
    checkArgType(L, LUA_TTABLE, 1);
    
    // Get name
    std::string viewName = requireNameFromTable(L, 1);
    
    // Get the View Direction
    Vector3D viewDirection = getVectorFromTableField(L, 1, "direction");
    
    // Get the View Point
    Point3D viewPoint = getPointFromTableField(L, 1, "position");
    
    // Create the view
    View * view = new View();
    view->setName(&viewName);
    view->viewPoint = viewPoint;
    view-> viewDirection = viewDirection;
    
    // Optional parameters
    if(fieldExists(L, 1, "up")){
        view->viewUp=getVectorFromTableField(L, 1, "up");
    }
    if(fieldExists(L, 1, "horizontal")){
        view->viewHorizontal=getNumberFromTableField(L, 1, "horizontal");
    }
    if(fieldExists(L, 1, "vertical")){
        view->viewVertical=getNumberFromTableField(L, 1, "vertical");
    }
    if(fieldExists(L, 1, "type")){
        std::string type = getStringFromTableField(L, 1, "type");
        const char * c_type = type.c_str();
        
        if(strcmp(c_type,"perspective") == 0 || strcmp(c_type,"v")== 0){
            view->viewType = PERSPECTIVE_VIEW;
        }else if(strcmp(c_type,"parallel")== 0 || strcmp(c_type,"l")== 0){
            view->viewType = PARALLEL_VIEW;
        }else if(strcmp(c_type,"cylindrical")== 0 || strcmp(c_type,"c")== 0){
            view->viewType = CYLINDRICAL_VIEW;
        }else if(strcmp(c_type,"hemispherical")== 0 || strcmp(c_type,"h")== 0){
            view->viewType = HEMISPHERICAL_VIEW;
        }else if(strcmp(c_type,"angular")== 0 || strcmp(c_type,"a")== 0){
            view->viewType = ANGULAR_VIEW;
        }else if(strcmp(c_type,"stereographic")== 0 || strcmp(c_type,"s")== 0){
            view->viewType = STEREOGRAPHIC_VIEW;
        }else {
            std::string errMsg = "Unknown view type '"+type+"'";            
            usageError(L, errMsg);
        }
    }
    if(fieldExists(L, 1, "fore_clipping")){
        view->foreClippingDistance=getNumberFromTableField(L, 1, "fore_clipping");
    }
    if(fieldExists(L, 1, "aft_clipping")){
        view->aftClippingDistance=getNumberFromTableField(L, 1, "aft_clipping");
    }
    
    // Add it to the model
    GroundhogModel * model = getCurrentModel(L);
    model->addView(view);
    
    // Return the view name
    lua_pushstring(L,viewName.c_str());
    
    // and the table
    lua_pushvalue(L,1);
    
    int tableIndex = lua_gettop(L);
    
    // But lets fill that table with the default fields first
    putVectorIntoTable(L, tableIndex, "up", view->getViewUp());
    
    lua_pushnumber(L,view->viewHorizontal);
    lua_setfield(L, tableIndex, "horizontal");
    
    lua_pushnumber(L,view->viewVertical);
    lua_setfield(L, tableIndex, "vertical");
    
    const char * inverseViewType[6] = {"perspective","parallel","cylindrical","hemispherical","angular","stereographic"};
    lua_pushstring(L, inverseViewType[view->viewType]);
    lua_setfield(L, tableIndex, "type");
    
    lua_pushnumber(L,view->foreClippingDistance);
    lua_setfield(L, tableIndex, "fore_clipping");
    
    lua_pushnumber(L,view->aftClippingDistance);
    lua_setfield(L, tableIndex, "aft_clipping");
    
    return 2;
}

