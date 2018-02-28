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

#include "./common.h"
#include <iostream>
#include "../../config_constants.h"
#include <chrono>

GroundhogModel * getCurrentModel(lua_State * L)
{
	lua_getglobal(L, LUA_MODEL_VARIABLE);
	GroundhogModel * model = (GroundhogModel *)lua_touserdata(L, lua_gettop(L));
	lua_pop(L, 1);
	return model;
}

TaskManager * getCurrentTaskManager(lua_State * L)
{
	lua_getglobal(L, LUA_TASKMANAGER_VARIABLE);
	TaskManager * taskManager = (TaskManager *)lua_touserdata(L, lua_gettop(L));
	lua_pop(L, 1);
	return taskManager;
}


std::map<std::string, TaskFactory> * getCurrentTaskDictionary(lua_State * L)
{
  lua_getglobal(L, LUA_TASKDICTIONARY_VARIABLE);
  std::map<std::string,TaskFactory> * taskDictionary = (std::map<std::string, TaskFactory> *)lua_touserdata(L, lua_gettop(L));
  lua_pop(L, 1);
  return taskDictionary;
}

void checkNArguments(lua_State * L, int nRArgs)
{
	int nargs = lua_gettop(L);
	if (nargs != nRArgs) 
		nArgumentError(L, nRArgs);			
}


int checkNArguments(lua_State * L, int nArgs[],int length)
{
  int givenArgs = lua_gettop(L);
  for (int i = 0; i < length; i++) {
    if (givenArgs == nArgs[i])
      return givenArgs;
  }
  nArgumentError(L, nArgs, length);
  return -1;
}

void nArgumentError(lua_State * L, int nArgs[], int length)
{
  std::string allowable = "";
  for (int i = 0; i < length; i++) {
    std::string comma = i==(length-2) ? " or " : ", ";    
    if (i == length - 1)
      comma = "";

    allowable = allowable + std::to_string(nArgs[i]) + comma;
  }
  std::string errmsg = "Function allows receiving " + allowable + " arguments, but received " + std::to_string(lua_gettop(L));
  sendError(L, "Number of arguments", &errmsg[0]);
}


void nArgumentError(lua_State * L, int nRequiredArgs)
{
	std::string errmsg = "Function requires " + std::to_string(nRequiredArgs) + " but received " + std::to_string(lua_gettop(L));
	sendError(L, "Number of arguments", &errmsg[0]);
}

void checkArgType(lua_State * L, int expectedType, int argPoisition)
{
  if (lua_type(L, argPoisition) != expectedType)
    argTypeError(L, expectedType, argPoisition);
}


void argTypeError(lua_State * L, int expectedType, int argPoisition)
{
  std::string errmsg = "Argument "+std::to_string(argPoisition)+" should be a " + std::string(lua_typename(L,expectedType)) + " but a "+std::string(lua_typename(L,lua_type(L,argPoisition)))+" was received";
  sendError(L, "Argument type", &errmsg[0]);
}


void executionError(lua_State * L, const char * err)
{
  sendError(L, "Execition error", err);
}

void sendError(lua_State * L, const char * kind, const char * err)
{
	lua_Debug ar;
	lua_getstack(L, 1, &ar);
	lua_getinfo(L, "nSl", &ar);

	std::string errMsg = "'"+std::string(kind) + "' error in line " + std::to_string(ar.currentline) + ": " + std::string(err);
	lua_pushstring(L, &errMsg[0]);
	lua_error(L);
}


void badOptionError(lua_State * L, std::string optionName, const char * receivedType, const char * expectedType)
{
  std::string err = "Option '" + optionName + "' is not supposed to be a '"+ receivedType + "' but a '"+expectedType+"'";
  sendError(L, "Bad option type", &err[0]);
}


void missingOption(lua_State * L, std::string optionName, std::string optionType)
{
  std::string errmsg = "Required option '"+optionName+"' of type '"+optionType+"' was not given";
  sendError(L,"Missing option", &errmsg[0]);
}


std::string requireNameFromTable(lua_State * L, int tableIndex)
{
    if(lua_getfield(L,tableIndex, "name") == LUA_TSTRING){
        return std::string(lua_tostring(L,lua_gettop(L)));
    }else{
        missingOption(L,"name","string");
        lua_pop(L,1);
        return nullptr;
    }
}

std::string getNameFromTable(lua_State * L, int tableIndex)
{
    if(lua_getfield(L,tableIndex, "name") == LUA_TSTRING){
        return std::string(lua_tostring(L,lua_gettop(L)));
    }else{
        std::chrono::milliseconds ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch());
        
        lua_pop(L,1); // Remove the NIL value
        return std::to_string(ms.count());
    }
}

Point3D getPointFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
    // stack top == 1
    int type = lua_getfield(L,tableIndex,fieldName);
    
    // stack top == 2
    if(type == LUA_TTABLE){
        int newTableIndex = tableIndex + 1;
        
        // Get the values ... stack == 3
        lua_rawgeti(L,newTableIndex,1);
        double x = lua_tonumber(L,lua_gettop(L));
        
        // ... stack == 4
        lua_rawgeti(L,newTableIndex,2);
        double y = lua_tonumber(L,lua_gettop(L));
        
        //... stack == 5
        lua_rawgeti(L,newTableIndex,3);
        double z = lua_tonumber(L,lua_gettop(L));
        
        lua_pop(L,4);
        // ... stack == 1
        return Point3D(x,y,z);
        
    }else if(type == LUA_TNIL){
        missingOption(L,std::string(fieldName),"table");
        return Point3D(0,0,0);
    }else{
        badOptionError(L,std::string(fieldName),lua_typename(L, type),"table");
        return Point3D(0,0,0);
    }
}


Vector3D getVectorFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
    // stack top == tableIndex
    int type = lua_getfield(L,tableIndex,fieldName);
    
    // stack top == tableIndex + 1
    if(type == LUA_TTABLE){
        int newTableIndex = tableIndex + 1;
        
        // Get the values ... stack == tableIndex + 2
        lua_rawgeti(L,newTableIndex,1);
        double x = lua_tonumber(L,lua_gettop(L));
        
        // ... stack == tableIndex + 3
        lua_rawgeti(L,newTableIndex,2);
        double y = lua_tonumber(L,lua_gettop(L));
        
        //... stack == tableIndex + 4
        lua_rawgeti(L,newTableIndex,3);
        double z = lua_tonumber(L,lua_gettop(L));
        
        lua_pop(L,4);
        // ... stack == tableIndex
        return Vector3D(x,y,z);
        
    }else if(type == LUA_TNIL){
        missingOption(L,std::string(fieldName),"table");
        return Vector3D(0,0,0);
    }else{
        badOptionError(L,std::string(fieldName),lua_typename(L, type),"table");
        return Vector3D(0,0,0);
    }
}

bool getPointFromTableIndex(lua_State * L, Point3D * p, int tableIndex, int i)
{
    // stack top == tableIndex
    int type = lua_rawgeti(L, tableIndex, i);
    
    // stack top == tableIndex + 1
    if(type == LUA_TTABLE){
        int newTableIndex = tableIndex + 1;
        
        // Get the values ... stack == tableIndex + 2
        lua_rawgeti(L,newTableIndex,1);
        double x = lua_tonumber(L,lua_gettop(L));
        
        // ... stack == tableIndex + 3
        lua_rawgeti(L,newTableIndex,2);
        double y = lua_tonumber(L,lua_gettop(L));
        
        //... stack == tableIndex + 4
        lua_rawgeti(L,newTableIndex,3);
        double z = lua_tonumber(L,lua_gettop(L));
        
        lua_pop(L,4);
        *p = Point3D(x,y,z);
        
        // ... stack == tableIndex
        return true;
        
    }else if(type == LUA_TNIL){
        lua_pop(L,1);
        return false;
    }else{
        badOptionError(L,std::to_string(i),lua_typename(L, type),"table");
    }
    
}


std::vector<Point3D> getVectorOfPointsFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
    std::vector<Point3D> res = std::vector<Point3D>();
    
    // stack top == tableIndex
    int type = lua_getfield(L,tableIndex,fieldName);
    
    // stack top == tableIndex + 1
    if(type == LUA_TTABLE){
        int newTableIndex = tableIndex + 1;
        Point3D p = Point3D(0,0,0);
        int pCount = 0;
        int n = lua_gettop(L);
        while(getPointFromTableIndex(L,&p,newTableIndex,++pCount)){
            res.push_back(p);
            n = lua_gettop(L);
        }
        n = lua_gettop(L);
        lua_pop(L,1);
        n = lua_gettop(L);
    }else if(type == LUA_TNIL){
        missingOption(L,std::string(fieldName),"table");
    }else{
        badOptionError(L,std::string(fieldName),lua_typename(L, type),"table");
    }
    int n = lua_gettop(L);
    return res;
}

double getNumberFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
    // stack top == tableIndex
    int type = lua_getfield(L,tableIndex,fieldName);
    
    // stack top == tableIndex + 1
    if(type == LUA_TNUMBER){
        double ret = lua_tonumber(L,tableIndex + 1);
        lua_pop(L,1);
        return ret;
    }else if(type == LUA_TNIL){
        missingOption(L,std::string(fieldName),"number");
        return 0;
    }else{
        badOptionError(L,std::string(fieldName),lua_typename(L, type),"number");
        return 0;
    }
}

std::string getStringFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
    // stack top == tableIndex
    int type = lua_getfield(L,tableIndex,fieldName);
    
    // stack top == tableIndex + 1
    if(type == LUA_TSTRING){
        std::string ret = lua_tostring(L,tableIndex + 1);
        lua_pop(L,1);
        return ret;
    }else if(type == LUA_TNIL){
        missingOption(L,std::string(fieldName),"string");
        return 0;
    }else{
        badOptionError(L,std::string(fieldName),lua_typename(L, type),"string");
        return 0;
    }
}

bool fieldExists(lua_State * L, int tableIndex, std::string fieldName)
{
    // stack top == tableIndex
    int type = lua_getfield(L,tableIndex,fieldName.c_str());
    
    bool res = (type != LUA_TNIL);
    lua_pop(L,1);
    return res;    
}


