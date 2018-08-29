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
#ifndef API_COMMON_H
#define API_COMMON_H

#include "emp_core.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}


// I believe it is better that some functions return the Stack as they received it.
// This Macros will not really check the integrity of the stack, but at least
// they will test the number of element in it.
#ifdef _DEBUG

#define INIT_STACK_CHECK_STACK_SIZE int initial_stack_size = lua_gettop(L);
#define CHECK_STACK_SIZE if(lua_gettop(L) != initial_stack_size){ \
std::cerr << "STACK SIZE ERROR in line : "<< std::to_string(__LINE__) << " of file " << __FILE__  << std::endl; \
}

#endif


//! Retrieves the current EmpModel exposed to the API
/*!
@author German Molina
@param L The lua_State * object
@return The pointer to the current EmpModel
*/
EmpModel * getCurrentModel(lua_State * L);


//! Retrieves the current TaskManager exposed to the API
/*!
@author German Molina
@param L The lua_State * object
@return The pointer to the current TaskManager
*/
TaskManager * getCurrentTaskManager(lua_State * L);


//! Checks that the number of arguments matches a certain value
/*!

The number of arguments is obtained from the size of the Lua stack

@author German Molina
@param[in] L The lua_State * object
@param[in] nargs The number of expected arguments
*/
void checkNArguments(lua_State * L, int nargs);

//! Checks that the number of arguments matches a certain set of posibilities
/*
This is supposed to be used with functions with optional values

@author German Molina
@param[in] L The Lua state
@param[in] nArgs A pointer to an array with the allowable number of arguments
@param[in] length The number of options
@return the number of arguments given
*/
int checkNArguments(lua_State * L, int nArgs[], int length);

//! Throws a Lua error informing that the number of arguments is incorrect
/*!

The number of given arguments is obtained from the size of the Lua stack

@author German Molina
@param[in] L The lua_State * object
@param[in] nRequiredArgs The number of arguments expected in the Lua state
*/
void nArgumentError(lua_State * L, int nRequiredArgs);

//! Throws a Lua error informing that the number of arguments is incorrect
/*!

The number of given arguments is obtained from the size of the Lua stack

@author German Molina
@param[in] L The Lua state
@param[in] nArgs A pointer to an array with the allowable number of arguments
@param[in] length The number of options
*/
void nArgumentError(lua_State * L, int nArgs[], int length);

//! Throws a Lua error informing that a certain option was incorrectly input
/*!
@author German Molina
@param[in] L The lua_State * object
@param[in] optionName The name of the option
@param[in] receivedType The type of the received option
@param[in] expectedType The type that the option is supposed to be
*/
void badOptionError(lua_State * L, std::string optionName, const char * receivedType, const char * expectedType);


//! Throws a Lua error informing that a certain required option was not given
/*!
@author German Molina
@param[in] L The lua_State * object
@param[in] optionName The name of the option
@param[in] optionType The type of the option
*/
void missingOption(lua_State * L, std::string optionName,std::string optionType);


//! Checks if a certain argument (in the stack) is of a certain type
/*!
@author German Molina
@param[in] L The lua_State * object
@param[in] expectedType The expected lua_type 
@param[in] argPosition The position in the stack of the argument to check 
*/
void checkArgType(lua_State * L, int expectedType, int argPoisition);

//! Throws a Lua error informing that a certain argument is not of the expected type
/*!
@author German Molina
@param[in] L The lua_State * object
@param[in] expectedType The expected lua_type
@param[in] argPosition The position in the stack of the argument to check
*/
void argTypeError(lua_State * L, int expectedType, int argPoisition);

//! Sends an error that sais that some internal emp process failed
/*!
@author German Molina
@param[in] L The lua state
@param[in] msg The error message
*/
void executionError(lua_State * L, std::string err);

//! Sends an error that sais that some internal emp process failed
/*!
 @author German Molina
 @param[in] L The lua state
 @param[in] msg The error message
 */
void executionError(lua_State * L, const char * err);


//! Sends an error that sais that the user did something wrong
/*!
 @author German Molina
 @param[in] L The lua state
 @param[in] msg The error message
 */
void usageError(lua_State * L, std::string err);

//! Sends an error that sais that the user did something wrong
/*!
 @author German Molina
 @param[in] L The lua state
 @param[in] msg The error message
 */
void usageError(lua_State * L, const char * err);


//! Throws a Lua error
/*!
@author German Molina
@param[in] L The lua_State * object
@param[in] kind The kind of error (i.e. usage, number of arguments, etc.)
@param[in] err The error message
*/
void sendError(lua_State * L, const char * kind, const char * err);

//! Retrieves the string from the 'name' field in a table
/*!
 Throws an error if the field does not exist
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @return the name
 */
std::string requireNameFromTable(lua_State * L, int tableIndex);

//! Retrieves the string from the 'name' field in a table
/*!
 Generates a random integer if not available
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @return the name
 */
std::string getNameFromTable(lua_State * L, int tableIndex);

//! Retrieves a Point3D stored in a certain field in a Lua table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Point3D is located
 @return the Point3D
 */
Point3D getPointFromTableField(lua_State * L, int tableIndex, const char * fieldName);


//! Retrieves a Vector3D stored in a certain field in a Lua table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @return the Vector3D
 */
Vector3D getVectorFromTableField(lua_State * L, int tableIndex, const char * fieldName);

//! Retrieves a Vector3D stored in a certain field in a Lua table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @return A vector with all the points there
 */
std::vector<Point3D> getVectorOfPointsFromTableField(lua_State * L, int tableIndex, const char * fieldName);

//! Retrieves R, G, and B values stored in the 'color' field in a Lua table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the color is located
 @param[out] r The pointer to the red component of the color
 @param[out] g The pointer to the green component of the color
 @param[out] b The pointer to the blue component of the color
 @return A vector with all the points there
 */
void getColorFromTableField(lua_State * L, int tableIndex, const char * fieldName, double * r, double * g, double * b);


//! Pushes a table of three numbers to a field in another table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D will be located
 @param[in] v The vector to push
 */
void putVectorIntoTable(lua_State * L, int tableIndex, const char * fieldName, Vector3D v);

//! Pushes a table of three numbers to a field in another table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D will be located
 @param[in] p The point to push
 */
void putPointIntoTable(lua_State * L, int tableIndex, const char * fieldName, Point3D p);

//! Retrieves a Point3D stored in a certain index of a Lua table
/*!
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @return true if there was a point at that index, false if not.
 */
bool getPointFromTableIndex(lua_State * L, Point3D * p, int tableIndex, int i);

//! Retrieves a double stored in a certain field in a Lua table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @return the number
 */
double getNumberFromTableField(lua_State * L, int tableIndex, const char * fieldName);

//! Retrieves a string stored in a certain field in a Lua table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @return the string
 */
std::string getStringFromTableField(lua_State * L, int tableIndex, const char * fieldName);

//! Retrieves a double stored in a certain field in a Lua table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @return the string
 */
double getDoubleFromTableField(lua_State * L, int tableIndex, const char * fieldName);


//! Retrieves a Int stored in a certain field in a Lua table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @return the string
 */
int getIntFromTableField(lua_State * L, int tableIndex, const char * fieldName);


//! Retrieves a float stored in a certain field in a Lua table
/*!
 Throws an error if something is wrong
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @return the string
 */
float getFloatFromTableField(lua_State * L, int tableIndex, const char * fieldName);


//! Checks if a certain field has something or not in a  table
/*!
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field to check
 @return exists?
 */
bool fieldExists(lua_State * L, int tableIndex, std::string fieldName);


//! Checks if a certain field has something or not in a  table
/*!
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The index of the field to check
 @return exists?
 */
bool fieldExists(lua_State * L, int tableIndex, int fieldName);

//! Checks if a certain field in a table matches a certain type
/*!
 Throws an error when the types do not match. Will also throw an error if
 the Strict input is set to true, and the field does not exist
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @param[in] type The expected type
 @param[in] string If true, throw an error when the field is inexistent
 @return matches?
 @note THIS METHOD PUSHES THE FIELD INTO THE STACK.
 */
bool checkFieldType(lua_State * L, int tableIndex, const char * fieldName, int type, bool strict);

//! Checks if a certain field in a table matches a certain type... throws an error when not,
/*!
 Throws an error when the types do not match of ig the field does not exist
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] fieldName The name of the field where the Vector3D is located
 @param[in] type The expected type
 @return exists?
 @note THIS METHOD PUSHES THE FIELD INTO THE STACK.
 */
bool checkFieldType(lua_State * L, int tableIndex, const char * fieldName, int type);


//! Checks if a certain field in a table matches a certain type
/*!
 Throws an error when the types do not match. Will also throw an error if
 the Strict input is set to true, and the field does not exist
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] i The position in the table to check
 @param[in] type The expected type
 @param[in] string If true, throw an error when the field is inexistent
 @return matches?
 @note THIS METHOD PUSHES THE FIELD INTO THE STACK.
 */
bool checkFieldType(lua_State * L, int tableIndex, int i, int type, bool strict);

//! Checks if a certain field in a table matches a certain type... throws an error when not,
/*!
 Throws an error when the types do not match of ig the field does not exist
 
 @author German Molina
 @param[in] L The lua_State
 @param[in] tableIndex The location of the table in the stack
 @param[in] i The position in the table to check
 @param[in] type The expected type
 @return exists?
 @note THIS METHOD PUSHES THE FIELD INTO THE STACK.
 */
bool checkFieldType(lua_State * L, int tableIndex, int i, int type);

//! Builds a new JSON from a Lua table
/*!
 @author German Molina
 */
void tableToJson(lua_State * L, int tablePosition, json * j);

void tableToJsonArray(lua_State * L, int tablePosition, json * j);

void jsonToTable(lua_State * L, const json * j);

#endif
