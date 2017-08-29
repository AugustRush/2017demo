//
//  PolygonPath.h
//  Drawing
//
//  Created by Adrian Russell on 31/03/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__PolygonPath__
#define __Drawing__PolygonPath__

#include "Object.h"
#include "Vector2.h"
#include "Rect.h"
#include <vector>

class PolygonPath : public Object
{
public:
    
    PolygonPath(Vector2 vertices[], unsigned int vertexCount);
                
    PolygonPath(std::vector<Vector2> vertices);
    
    PolygonPath(Rect rect);
    
    std::vector<Vector2>& faceNormals() { return _faceNormals; }
    std::vector<Vector2>& vertices()    { return _vertices;    }
    
    float area() { return _area; }
    
    float momentOfIntertia() { return _momentOfInertia; }
    
    //split function
    
    
    
private:
    std::vector<Vector2> _vertices;
    std::vector<Vector2> _faceNormals;
    float _area;
    float _momentOfInertia; // times by density to get thing for body
    
    void calculateMomentOfInertia();
};



#endif /* defined(__Drawing__PolygonPath__) */
