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

#ifndef EMP_CONFIG_CONSTANTS_H
#define EMP_CONFIG_CONSTANTS_H

#include "./versions.h"
//#include "emp_core.h"


/// The 'usage' message
#define USAGE "\n " << EMP_VERSION << " usage options: \n\n" \
" emp {--help | -h}\t\t: prints this message \n" \
" emp {--version | -v}\t\t: prints version \n" \
" emp {--about | -a}\t\t: prints about \n" \
" emp --checkpath\t\t: prints the EMPATH variable\n" \
" emp inputFile script.lua\t: applies a lua script over an input file.\n" \
" emp - script.lua\t: runs a lua script that generates geometry and material as needed \n"

/// The 'about' message
#define ABOUT "\n\n Copyright (C) 2018 German Molina (germolinal@gmail.com) \n\n" \
" This program is free software : you can redistribute it and/or modify it under the \n"\
" terms of the GNU General Public License as published by the Free Software Foundation,\n"\
" either version 3 of the License, or (at your option) any later version. \n\n" \
" This program is distributed in the hope that it will be useful, but WITHOUT ANY \n"\
" WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A \n"\
" PARTICULAR PURPOSE.See the GNU General Public License for more details. \n\n"\
" You should have received a copy of the GNU General Public License along with \n"\
" this program.If not, see http ://www.gnu.org/licenses/.\n\n"

/// Name of the global variable pointing to the EmpModel in the Lua API
#define LUA_MODEL_VARIABLE "currentmodel"

/// Name of the global variable pointing to the TaskManager in the Lua API
#define LUA_TASKMANAGER_VARIABLE "currenttaskmanager"

/// Name of the variable defining the TaskManager's autoSolve option
#define LUA_AUTOSOLVE_VARIABLE "auto_solve"

/// Name of the variable controlling whether to print the results to screen or not
#define LUA_STDOUT_RESULTS_VARIABLE "print_results"

#endif
