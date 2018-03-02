
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

#include "./genbox.h"
#include "../../utils/common.h"
#include "../../utils/get_material.h"
#include "../../utils/get_layer.h"



int genBox(lua_State * L)
{
    // Check the number of arguments
    checkNArguments(L, 1);
    
    // Check type
    checkArgType(L, LUA_TTABLE, 1);
    
    // Identify name
    std::string name = getNameFromTable(L,1);
    
    // get Size
    double x, y, z;
    if(fieldExists(L,1, "size")){
        getColorFromTableField(L, 1, "size", &x, &y, &z);
    }else{
        missingOption(L,"size", "table");
    }
    
    // Identify Material
    std::string materialName;
    Material * material = nullptr;
    if(fieldExists(L,1, "material")){
        materialName = getStringFromTableField(L, 1, "material");
        material = getMaterial(L,&materialName);
    }
    
    // Get the Layer
    Layer * layer = getLayerAccordingToTable(L, 1);
    
    /* CREATE THE FACES */
    Face * face; Loop * loop;int fIndex = 0;
    
    // First, bottom:
    std::string faceName = name+std::to_string(++fIndex);
    face = new Face(&faceName);
    face->setMaterial(material);
    loop = face->getOuterLoopRef();
    loop->addVertex(new Point3D(0,0,0));
    loop->addVertex(new Point3D(0,y,0));
    loop->addVertex(new Point3D(x,y,0));
    loop->addVertex(new Point3D(x,0,0));
    layer->addObject(face);
    
    
    // Top:
    faceName = name+std::to_string(++fIndex);
    face = new Face(&faceName);
    face->setMaterial(material);
    loop = face->getOuterLoopRef();
    loop->addVertex(new Point3D(0,0,z));
    loop->addVertex(new Point3D(x,0,z));
    loop->addVertex(new Point3D(x,y,z));
    loop->addVertex(new Point3D(0,y,z));
    layer->addObject(face);
    
    // Front:
    faceName = name+std::to_string(++fIndex);
    face = new Face(&faceName);
    face->setMaterial(material);
    loop = face->getOuterLoopRef();
    loop->addVertex(new Point3D(0,0,0));
    loop->addVertex(new Point3D(x,0,0));
    loop->addVertex(new Point3D(x,0,z));
    loop->addVertex(new Point3D(0,0,z));
    layer->addObject(face);
    
    // Back:
    faceName = name+std::to_string(++fIndex);
    face = new Face(&faceName);
    face->setMaterial(material);
    loop = face->getOuterLoopRef();
    loop->addVertex(new Point3D(0,y,0));
    loop->addVertex(new Point3D(0,y,z));
    loop->addVertex(new Point3D(x,y,z));
    loop->addVertex(new Point3D(x,y,0));
    layer->addObject(face);
    
    // Right:
    faceName = name+std::to_string(++fIndex);
    face = new Face(&faceName);
    face->setMaterial(material);
    loop = face->getOuterLoopRef();
    loop->addVertex(new Point3D(x,0,0));
    loop->addVertex(new Point3D(x,y,0));
    loop->addVertex(new Point3D(x,y,z));
    loop->addVertex(new Point3D(x,0,z));
    layer->addObject(face);
    
    // left:
    faceName = name+std::to_string(++fIndex);
    face = new Face(&faceName);
    face->setMaterial(material);
    loop = face->getOuterLoopRef();
    loop->addVertex(new Point3D(0,0,0));
    loop->addVertex(new Point3D(0,0,z));
    loop->addVertex(new Point3D(0,y,z));
    loop->addVertex(new Point3D(0,y,0));
    layer->addObject(face);
    
    
    // Push the name
    lua_pushstring(L, name.c_str());
    
    return 1;
    
}




