

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "../common.h"

//! Fills the options on an OptionSet with the data in a Lua table
/*!
@author German Molina
 @param options A pointer to the options to fill
 @param[in] L the lua_State
 @param tablePosition The position of the table in the lua_State
 @return success
*/
bool fillOptionsFromLuaTable(OptionSet * options, lua_State * L, int tablePosition)
{
    for (json::iterator it = options->begin(); it != options->end(); ++it) {
        std::string optionName = it.key();
        auto value = it.value();
        
        // Now the value we are looking for is in the position 'tablePosition' of the stack
        int field = lua_getfield(L, tablePosition, &optionName[0]);
        
        // If the value is there (i.e. it is not nil)
        if (field != LUA_TNIL) {
            // Retrieve it and use it
            if (field == LUA_TNUMBER) {
                // Verify that the original value was a number as well
                if (value.is_number_integer()) {
                    options->setOption(optionName, (int)lua_tonumber(L, tablePosition+1));
                }
                else if (value.is_number() ){
                    options->setOption(optionName, lua_tonumber(L, tablePosition + 1));
                }
                else {
                    badOptionError(L, optionName, lua_typename(L, field),"number");
                }
            }
            else if (field == LUA_TSTRING) {
                if (!value.is_string()) {
                    badOptionError(L, optionName, lua_typename(L, field),"string");
                }
                options->setOption(optionName, lua_tostring(L, tablePosition + 1));
            }
            else if (field == LUA_TBOOLEAN ) {
                if (!value.is_boolean()) {
                    badOptionError(L, optionName, lua_typename(L, field),"boolean");
                }
                options->setOption(optionName, lua_toboolean(L, tablePosition + 1) ? true : false);
            }
            else {
                FATAL(errorMessage,"Unrecognized value type " + std::string(lua_typename(L, field)) + " of value for option " + optionName);
                return false;
            }
        }
        // remove one value from the stack (or nil, if it was not there)
        lua_pop(L, 1);
    }
    return true;
}
