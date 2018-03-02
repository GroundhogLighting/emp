
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

 #include "./optionset_ext.h"


bool fillOptionsFromLuaTable(OptionSet * options, lua_State * L, int tablePosition)
{
#ifdef _DEBUG
    INIT_STACK_CHECK_STACK_SIZE
#endif
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
#ifdef _DEBUG
    CHECK_STACK_SIZE
#endif
    return true;
}
