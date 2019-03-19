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

#include "./rvu.h"
#include "emp_core.h"
#include "../utils/common.h"

int review(lua_State * L)
{
    
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check the type of argument
    checkArgType(L, LUA_TSTRING, 1);
    
    // Retrieve the first argument
    std::string viewName = lua_tostring(L, 1);
    
    // Get the model
    EmpModel * model = getCurrentModel(L);
    
    // Get the View
    View * view = model->getViewByName(&viewName);
    
    // Build the view options
    const std::string blank = std::string(" ");
    Point3D p = view->getViewPoint();
    Vector3D d = view->getViewDirection();
    Vector3D u = view->getViewUp();
    double vh = view->getViewHorizontal();
    double vv = view->getViewVertical();
    int type = view->getViewType();
    double va = view->aftClippingDistance;
    double vo = view->foreClippingDistance;
    
    const char * inverseViewType[6] = {"v","l","c","h","a","s"};
    
    std::string viewOptions =
    std::string("-vp")+ blank + std::to_string(p.getX()) + blank + std::to_string(p.getY()) + blank + std::to_string(p.getZ()) + blank +
    std::string("-vd")+ blank + std::to_string(d.getX()) + blank + std::to_string(d.getY()) + blank + std::to_string(d.getZ()) + blank +
    std::string("-vu")+ blank + std::to_string(u.getX()) + blank + std::to_string(u.getY()) + blank + std::to_string(u.getZ()) + blank +
    
    std::string("-vh ") + std::to_string(vh) + blank +
    std::string("-vv ") + std::to_string(vv) + blank +
    std::string("-vt") + std::string(inverseViewType[type]) + blank +
    std::string("-va ") + std::to_string(va) + blank +
    std::string("-vo ") + std::to_string(vo) ;
    
    // Create some OconvOptions
    OconvOptions oconvOptions = OconvOptions();
    
    // Create a Task Manager
    TaskManager tm = TaskManager();
    
    // Build sky
    Date * date = model->getDate();
    std::string month = std::to_string(date->getMonth());
    std::string day = std::to_string(date->getDay());
    std::string hour = std::to_string(date->getHour());
    
    Location * l = model->getLocation();
    std::string lat = std::to_string(l->getLatitude());
    std::string lon = std::to_string(l->getLongitude());
    std::string albedo = std::to_string(l->getAlbedo());
    std::string meridian = std::to_string(-15*l->getTimeZone());
    
    std::string sky = "gensky "+month+" "+day+" "+hour+" -a "+lat+" -o "+lon+" -m " + meridian + " -g "+albedo;
    
    // Create and add an Oconv task
    AddSkyToOctree * oconvTask = new AddSkyToOctree(model, &oconvOptions, sky);
    tm.addTask(oconvTask);
    
    // Solve the model, so the
    tm.solve();
    
    // Retrieve the Octree Name
    std::string octname = oconvTask -> octreeName;
    
    // Create some RTrace options
    RTraceOptions options = RTraceOptions();
    options.setOption("ab", 2);
    std::string inlineOptions = options.getInlineVersion();
    
    // Build and run the command
    std::string command = std::string("rvu ") + inlineOptions + blank + viewOptions + blank + octname;
    
    FILE *rvu = POPEN(&command[0], "w");
    PCLOSE(rvu);
    
    
    return 0;
}
