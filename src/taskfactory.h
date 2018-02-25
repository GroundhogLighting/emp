#ifndef EMP_TASK_FACTORY_H
#define EMP_TASK_FACTORY_H

#include "../../emp_core/include/emp_core.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

using TaskFactory = Task* (*)(lua_State *L);

#endif
