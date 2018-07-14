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

#include "./api.h"

std::vector< std::string > getEmpath()
{
    std::vector<std::string> ret =std::vector<std::string>();
    
    std::string empath = std::string(std::getenv(EMPATH));
    
    size_t start = 0;
    size_t found = empath.find(":", start);
    while (found != std::string::npos) {
        ret.push_back(empath.substr(start, found-start));
        start = found+1;
        found = empath.find(":", start+1);
    }
    
    if(empath.substr(start) != ""){
        ret.push_back(empath.substr(start));
    }
    
    return ret;
}

int main(int argc, char* argv[]){
    
    if (argc == 1){
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
        if (const char * empath = std::getenv(EMPATH)) {
            
            std::vector< std::string > emp_dirs = getEmpath();
            std::cout << "EMPATH is defined as the following directories:" << std::endl;
            
            for(auto s : emp_dirs)
                std::cout << "  "<< s << std::endl;
            
            return 0;
        }
        else {
            std::cout << "There is no "<< EMPATH << " variable stored" << std::endl;
            return 0;
        }
    }
    
     // Not just wanting for help... do something.
     else if (argc < 3) {
         std::cerr << "Incorrect emp usage\n" << std::endl;
         std::cerr << USAGE << std::endl;
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
             if (const char * aux = std::getenv(EMPATH)) {
                 
                 // Get the empath directories
                 std::vector< std::string > emp_dirs = getEmpath();
                 
                 bool found = false;
                 
                 // Find the script in those directories
                 for(auto p : emp_dirs){
                     if (fexists(p + "/" + script)) {
                         script = p + "/" + script;
                         found = true;
                     }
                 }
                 if(!found) {
                     std::cerr << "Lua script '" + std::string(script) + "' not found (not even in EMPATH)" << std::endl;
                     return 1;
                 }
                 
             } else { // if there is no EMPATH variable, just error.
                 std::cerr << "Lua script '" + std::string(script) + "' not found" << std::endl;
                 return 1;
             }
         }
         
         
         
         
         /* SEARCH FOR MODEL */
         if (!fexists(argv[1]) && strcmp(argv[1],"-") != 0 ) {
             std::cerr << "File '" + std::string(argv[1]) + "' not found" << std::endl;
             return 1;
         }
         
         /* CREATE A GROUNDHOG MODEL */
         GroundhogModel model = GroundhogModel();
         TaskManager taskManager = TaskManager();
         
         /* CREATE A NEW LUA STATE */
         lua_State * L = luaL_newstate();
         luaL_openlibs(L);
                  
         /* INITIALIZE API */
         initAPI(L,&model, &taskManager,argc,argv);
         
         /* REGISTER COMMANDS */
         registerCommands(L);
         
         /* LOAD THE MODEL */
         if(strcmp(argv[1],"-")==0){
             // No model to input... just script
             
         } else if(stringInclude(argv[1],".lua")){
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
             std::cerr << "Unrecognized model format" << std::endl;
             return 1;
         }
                                    
         
         
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
         lua_pop(L, 1); // Clean this variable
         
         
         // solve if required
         if (autoSolve) {
             nlohmann::json results = nlohmann::json();
             if(taskManager.countTasks() == 0){
                 WARN(x,"No tasks in TaskManager, so nothing to do... to avoid this message set 'auto_solve = false' in your script");
                 return 0;
             }
             
             taskManager.solve(&results);
             
             // print results?
             bool stdoutResults = true; // defaults to true
             lua_getglobal(L, LUA_STDOUT_RESULTS_VARIABLE);
             
             // Check type
             if (lua_type(L, 1) == LUA_TBOOLEAN) {
                 stdoutResults = lua_toboolean(L, 1);
             }
             lua_pop(L,1); // Clean stack
             if(!results.empty() && stdoutResults){
                 std::cout << results << std::endl;
             }
         }
     }
    
    
    
    
    return 0;
}



