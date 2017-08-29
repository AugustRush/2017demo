//
//  PolygonBody.h
//  Drawing
//
//  Created by Adrian Russell on 31/12/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__PolygonBody__
#define __Drawing__PolygonBody__

#include "Body.h"
#include "PolygonPath.h"

class PolygonBody : public Body
{
public:
    
    /*!
     @param position    ...
     @param mass        ...
     @param vertices    ...
     @param vertexCount ...
     @discussion Note that the verticies you input may not all be used or may not be in the same order. 
     This function runs a convex hull function on the input points what will convert the points into a convex body shape.
     If less than 3 vertices are input then this method will raise an assertion.
     */
    PolygonBody(Vector2 position, float mass, Vector2 vertices[], unsigned int vertexCount);
    
    PolygonBody(Vector2 position, float mass, std::vector<Vector2> vertices);
    
    PolygonBody(Vector2 position, float mass, PolygonPath *path);
    
    ~PolygonBody();
    
    
    /*! Produces a rectangular polygon body with the size and position set from a specified Rect.
     @param rect ...
     @param mass The mass of the body;
     */
    PolygonBody(Rect rect, float mass);
    
    BodyType bodyType() { return BodyTypePolygon; }
    
    bool intersectsRay(const Vector2& a, const Vector2& b);
    
    bool intersectsRay(const Vector2& ray);
    
    bool containsPoint(const Vector2& point);
    
    
    
    unsigned int vertexCount();
    const std::vector<Vector2> &vertices() const;
    const std::vector<Vector2> &normals() const;
    
private:
    PolygonPath *_polygonPath;
    Rect recalculateAABB();
};

#endif
