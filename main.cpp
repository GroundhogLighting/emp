#include <string>
#include "./src/config_constants.h"
#include "./versions.h"
#include "./main.h"
#include <iostream>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "./src/api/load_commands.h"
#include "./src/api/load_tasks.h"
#include "./src/api/load_ghm_commands.h"

#include "./api.h"


int main(int argc, char* argv[]){
    
    if (argc == 1){
        FATAL(errmsg, "Incorrect emp usage\n");
        std::cout << USAGE << std::endl;
        return 1;
    }
    
    // Check if only some help is needed
    if ( strcmp(argv[1], "--help") == 0 || strcmp(argv[1] , "-h")== 0) {
        std::cout << USAGE << std::endl;
        return 0;
    }
    else if (strcmp(argv[1],"--about") == 0 || strcmp(argv[1],"-a") == 0) {
        std::cout << ABOUT << std::endl;
        return 0;
    }
    else if (strcmp(argv[1],"--version") == 0 || strcmp(argv[1],"-v") == 0) {
        std::cout << EMP_VERSION << std::endl;
        std::cout << EMP_CORE_VERSION << std::endl;
        std::cout << RADIANCE_VERSION << std::endl;
        std::cout << LUA_VERSION << std::endl;
        return 0;
    }
    else if (strcmp(argv[1], "--checkpath") == 0 ) {
        if (const char * glarepath = std::getenv(EMPATH)) {
            std::cout << glarepath << std::endl;
            return 0;
        }
        else {
            std::cout << "There is no "<< EMPATH << " variable stored" << std::endl;
            return 0;
        }
    }
    
     // Not just wanting for help... do something.
     else if (argc < 3) {
         FATAL(errmsg, "Incorrect emp usage\n");
         std::cout << USAGE << std::endl;
     }else{
         
         /* SEARCH FOR SCRIPT */
         std::string script = argv[2];
         // add the .lua if needed
         if (!stringInclude(script, ".lua")) {
             script = script + ".lua";
         }
         
         // check if script exists
         if (!fexists(script)) {
             // if it does not exist, we look into the EMPATH
             if (const char * glarepath = std::getenv(EMPATH)) {
                 if (fexists(std::string(glarepath) + "/" + script)) {
                     script = std::string(glarepath) + "/" + script;
                 }
                 else {
                     FATAL(errorMessage, "Lua script '" + std::string(script) + "' not found (not even in "+ EMPATH +")");
                     return 1;
                 }
             } else { // if there is no GLAREPATH variable, just error.
                 FATAL(errorMessage, "Lua script '" + std::string(script) + "' not found");
                 return 1;
             }
         }
         
         
         /* SEARCH FOR MODEL */
         if (!fexists(argv[1]) && strcmp(argv[1],"-") != 0 ) {
             FATAL(errorMessage,"File '" + std::string(argv[1]) + "' not found");
             return 1;
         }
         
         /* CREATE A GROUNDHOG MODEL */
         GroundhogModel model = GroundhogModel();
         TaskManager taskManager = TaskManager();
         
         /* CREATE A NEW LUA STATE */
         lua_State * L = luaL_newstate();
         luaL_openlibs(L);
         
         /* CREATE A TASK FACTORY DICTIONARY */
         std::map<std::string, TaskFactory> taskDictionary;
         
         /* INITIALIZE API */
         initAPI(L,&model, &taskDictionary, &taskManager,argc,argv);
         
         /* REGISTER COMMANDS */
         registerGHMCommands(L);
         
         /* LOAD THE MODEL */
         if(strcmp(argv[1],"-")==0){
             
         } else if(stringInclude(argv[1],".ghm") || stringInclude(argv[1],".lua")){
             /* GroundhogModels are actually Lua scripts */
             // Load script
             int s,r;
             s = luaL_loadfile(L,argv[1]);
             if (s) {
                 std::cerr <<  lua_tostring(L, -1) << std::endl;
                 return 1;
             }
             
             // Solve script
             r = lua_pcall(L, 0, LUA_MULTRET, 0);
             if (r) {
                 std::cerr << lua_tostring(L, -1) << std::endl;
                 return 1;
             }
             
             // Reset the auto_solve to true.
             lua_pushboolean(L,true);
             lua_setglobal(L, LUA_AUTOSOLVE_VARIABLE);
             
         } else if(stringInclude(argv[1],".skp")){
             SKPreader reader = SKPreader(&model,false); // not verbose
             reader.parseSKPModel(argv[1]);
         }else {
             FATAL(e,"Unrecognized model format");
             return 1;
         }
         
         /* REGISTER OTHER COMMANDS */
         registerCommands(L);
         
         /* REGISTER TASKS */
         registerTasks(L);
         
         
         // Process LUA script
         int status, result;
         
         // Load script
         status = luaL_loadfile(L, &script[0]);
         if (status) {
             std::cerr <<  lua_tostring(L, -1) << std::endl;
             return 1;
         }
         
         // Solve script
         result = lua_pcall(L, 0, LUA_MULTRET, 0);
         if (result) {
             std::cerr << lua_tostring(L, -1) << std::endl;
             return 1;
         }
         
         // Autosolve?
         bool autoSolve = true; // defaults to true
         lua_getglobal(L, LUA_AUTOSOLVE_VARIABLE);
         // Check type
         if (lua_type(L, 1) == LUA_TBOOLEAN) {
             autoSolve = lua_toboolean(L, 1);
         }
         
         // solve if required
         if (autoSolve) {
             nlohmann::json results = nlohmann::json();
             if(taskManager.countTasks() == 0){
                 WARN(x,"No tasks in TaskManager, so nothing to do... to avoid this message set 'auto_solve = false' in your script");
                 return 0;
             }
             taskManager.solve(&results);
             std::cout << results;
         }
         
     }
    
    return 0;
}



