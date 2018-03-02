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


GroundhogModel * getCurrentModel(lua_State * L)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
	
    lua_getglobal(L, LUA_MODEL_VARIABLE);
	GroundhogModel * model = (GroundhogModel *)lua_touserdata(L, lua_gettop(L));
	lua_pop(L, 1);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
	return model;
}

TaskManager * getCurrentTaskManager(lua_State * L)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    
	lua_getglobal(L, LUA_TASKMANAGER_VARIABLE);
	TaskManager * taskManager = (TaskManager *)lua_touserdata(L, lua_gettop(L));
	lua_pop(L, 1);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
	return taskManager;
}


std::map<std::string, TaskFactory> * getCurrentTaskDictionary(lua_State * L)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    
  lua_getglobal(L, LUA_TASKDICTIONARY_VARIABLE);
  std::map<std::string,TaskFactory> * taskDictionary = (std::map<std::string, TaskFactory> *)lua_touserdata(L, lua_gettop(L));
  lua_pop(L, 1);

#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
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
  sendError(L, "Execution error", err);
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


bool checkFieldType(lua_State * L, int tableIndex, const char * fieldName, int type, bool strict)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    // Ensure element in tableIndex is a Table
    checkArgType(L, LUA_TTABLE, tableIndex);
    
    
    int actualType = lua_getfield(L, tableIndex, fieldName);
    
    if(type == actualType){
        return true;
    }else if(actualType == LUA_TNIL){
        if(strict){
            missingOption(L, fieldName, lua_typename(L,type));
            return false;
        }else{
            return false;
        }
    }else {
        badOptionError(L, fieldName, lua_typename(L,actualType), lua_typename(L,type));
        return false;
    }
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    return true;
}

bool checkFieldType(lua_State * L, int tableIndex, const char * fieldName, int type)
{
    return checkFieldType(L, tableIndex, fieldName, type, true);
}

bool checkFieldType(lua_State * L, int tableIndex, int i, int type, bool strict)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    
    // Ensure element in tableIndex is a Table
    checkArgType(L, LUA_TTABLE, tableIndex);
    
    int actualType = lua_rawgeti(L,tableIndex,i);
    
    if(type == actualType){
        return true;
    }else if(actualType == LUA_TNIL){
        if(strict){
            missingOption(L, std::to_string(i), lua_typename(L,type));
            return false;
        }else{
            return false;
        }
    }else {
        badOptionError(L, std::to_string(i), lua_typename(L,actualType), lua_typename(L,type));
        return false;
    }
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    return true;
}

bool checkFieldType(lua_State * L, int tableIndex, int i, int type)
{
    return checkFieldType(L, tableIndex, i, type, true);
}

std::string requireNameFromTable(lua_State * L, int tableIndex)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    
    checkFieldType(L, tableIndex,"name",LUA_TSTRING);
    std::string ret = lua_tostring(L,lua_gettop(L));
    lua_pop(L,1);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    return ret;
}

std::string getNameFromTable(lua_State * L, int tableIndex)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    
    std::string ret;
    if(checkFieldType(L, tableIndex,"name",LUA_TSTRING,false)){
        ret = lua_tostring(L,lua_gettop(L));
    }else{
        ret = std::to_string(rand()%rand());
    }
    lua_pop(L,1);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    return ret;
    
}

Point3D getPointFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    
    int n = lua_gettop(L);
    checkFieldType(L, tableIndex, fieldName, LUA_TTABLE);
    n = lua_gettop(L);
    int newTableIndex = lua_gettop(L);
    
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
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    // ... stack == 1
    return Point3D(x,y,z);
    
}


Vector3D getVectorFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    
    checkFieldType(L, tableIndex, fieldName, LUA_TTABLE);
    
    int newTableIndex = tableIndex + 1;
    
    // Get the values ... stack == 3
    checkFieldType(L, newTableIndex, 1, LUA_TNUMBER);
    double x = lua_tonumber(L,lua_gettop(L));
    
    // ... stack == 4
    checkFieldType(L, newTableIndex, 2, LUA_TNUMBER);
    double y = lua_tonumber(L,lua_gettop(L));
    
    //... stack == 5
    checkFieldType(L, newTableIndex, 3, LUA_TNUMBER);
    double z = lua_tonumber(L,lua_gettop(L));
    
    lua_pop(L,4);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    // ... stack == 1
    return Vector3D(x,y,z);
    
    
}

bool getPointFromTableIndex(lua_State * L, Point3D * p, int tableIndex, int i)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    if(!checkFieldType(L, tableIndex, i, LUA_TTABLE, false)){
        return false;
    }
    
    int newTableIndex = lua_gettop(L);
    
    
    checkFieldType(L, newTableIndex, 1, LUA_TNUMBER);
    double x = lua_tonumber(L,lua_gettop(L));
    
    checkFieldType(L, newTableIndex, 2, LUA_TNUMBER);
    double y = lua_tonumber(L,lua_gettop(L));
    
    checkFieldType(L, newTableIndex, 3, LUA_TNUMBER);
    double z = lua_tonumber(L,lua_gettop(L));
    
    lua_pop(L,4);
    *p = Point3D(x,y,z);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    // ... stack == tableIndex
    return true;
    
    
}



std::vector<Point3D> getVectorOfPointsFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    std::vector<Point3D> res = std::vector<Point3D>();
    
    checkFieldType(L, tableIndex, fieldName, LUA_TTABLE);
    
    int newTableIndex = lua_gettop(L);
    Point3D p = Point3D(0,0,0);
    int pCount = 0;
    
    while(getPointFromTableIndex(L,&p,newTableIndex,++pCount)){
        res.push_back(p);
        n = lua_gettop(L);
    }
    
    lua_pop(L,2);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    return res;
}

double getNumberFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    // stack top == tableIndex
    checkFieldType(L, tableIndex, fieldName, LUA_TNUMBER);
    double ret = lua_tonumber(L,lua_gettop(L));
    lua_pop(L,1);
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    return ret;
    
}

std::string getStringFromTableField(lua_State * L, int tableIndex, const char * fieldName)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    checkFieldType(L, tableIndex, fieldName, LUA_TSTRING);
    std::string ret = std::string(lua_tostring(L,lua_gettop(L)));
    lua_pop(L,1);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    return ret;
    
}

bool fieldExists(lua_State * L, int tableIndex, std::string fieldName)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    // stack top == tableIndex
    int type = lua_getfield(L,tableIndex,fieldName.c_str());
    
    bool res = (type != LUA_TNIL);
    lua_pop(L,1);
    
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    
    return res;    
}

void putVectorIntoTable(lua_State * L, int tableIndex, const char * fieldName, Vector3D v)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    int n = lua_gettop(L);
    
    // Create a new table.
    lua_newtable(L); // index == n+1
    
    
    // Add X, Y and Z to that table
    lua_pushnumber(L,v.getX()); // index == n+2
    lua_seti(L, n+1, 1);
    
    lua_pushnumber(L,v.getY()); // index == n+3
    lua_seti(L, n+1, 2);
    
    lua_pushnumber(L,v.getZ()); // index == n+4
    lua_seti(L, n+1, 3);
    
    lua_setfield(L, tableIndex, fieldName);
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    return;
}

void putPointIntoTable(lua_State * L, int tableIndex, const char * fieldName, Point3D p)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    int n = lua_gettop(L);
    
    // Create a new table.
    lua_newtable(L); // index == n+1
    
    
    // Add X, Y and Z to that table
    lua_pushnumber(L,p.getX()); // index == n+2
    lua_seti(L, n+1, 1);
    
    lua_pushnumber(L,p.getY()); // index == n+3
    lua_seti(L, n+1, 2);
    
    lua_pushnumber(L,p.getZ()); // index == n+4
    lua_seti(L, n+1, 3);
    
    lua_setfield(L, tableIndex, fieldName);
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    return;
}

void getColorFromTableField(lua_State * L, int tableIndex, const char * fieldName, double * r, double * g, double * b)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
    checkFieldType(L, tableIndex, fieldName, LUA_TTABLE);
    
    int newTableIndex = lua_gettop(L);
    
    // Get the values ... stack == tableIndex + 2
    checkFieldType(L, newTableIndex, 1, LUA_TNUMBER);
    *r = lua_tonumber(L,lua_gettop(L));
    
    // ... stack == tableIndex + 3
    checkFieldType(L, newTableIndex, 2, LUA_TNUMBER);
    *g = lua_tonumber(L,lua_gettop(L));
    
    //... stack == tableIndex + 4
    checkFieldType(L, newTableIndex, 3, LUA_TNUMBER);
    *b = lua_tonumber(L,lua_gettop(L));
    
    lua_pop(L,4);
    // ... stack == tableIndex
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
}

