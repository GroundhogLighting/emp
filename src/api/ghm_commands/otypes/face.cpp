
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

#include "./face.h"
#include "../../utils/common.h"
#include "../../utils/get_layer.h"
#include "../../utils/create_otype.h"

void fillData(Face * o, lua_State * L, int tableIndex)
{
    
    Polygon3D * polygon = o->polygon;
    
    /* FILL EXTERIOR LOOP */
    Loop * exterior = polygon->getOuterLoopRef();
    std::vector <Point3D> extPoints = getVectorOfPointsFromTableField(L, tableIndex, "vertices");
    size_t nExtPoints = extPoints.size();
    
    if(nExtPoints < 3){
        std::string eMsg = "Exterior loop of a polygon requires at least three vertices... only "+std::to_string(nExtPoints) + " were given";
        sendError(L, "Usage", eMsg.c_str());
    }
    
    for(size_t i = 0; i<nExtPoints; i++){
        Point3D p = extPoints.at(i);
        exterior->addVertex(new Point3D(p.getX(),p.getY(),p.getZ()));
    }
    
    /* FILL INTERIOR LOOPS, IF THEY EXSIST */
    size_t innerLoopCount = 0;
    while(fieldExists(L, tableIndex, "hole"+std::to_string(++innerLoopCount))){
        
        // Build the name of the field
        std::string loopName = "hole"+std::to_string(innerLoopCount);
        
        // Add the loop to the polygon
        Loop * loop = polygon->addInnerLoop();
        
        // Retrieve the points in that loop
        std::vector <Point3D> points = getVectorOfPointsFromTableField(L, tableIndex, loopName.c_str());
        
        // Check number of points
        size_t nPoints = points.size();
        if(nPoints < 3){
            std::string eMsg = "Holes in a polygon require at least three vertices... only "+std::to_string(nPoints) + " were given";
            sendError(L, "Usage", eMsg.c_str());
        }
        
        // Add them
        for(size_t i = 0; i<nPoints; i++){
            Point3D p = points.at(i);
            loop->addVertex(new Point3D(p.getX(),p.getY(),p.getZ()));
        }
        
    }
    
}

int createFace(lua_State * L)
{
    return createOtype(L,"polygon");    
}




