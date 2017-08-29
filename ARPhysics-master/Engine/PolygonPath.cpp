//
//  PolygonPath.cpp
//
//  Created by Adrian Russell on 31/03/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "PolygonPath.h"
#include "Shape_Utilities.h"

PolygonPath::PolygonPath(Vector2 vertices[], unsigned int vertexCount)
{
    assert(vertexCount >= 3);
    _vertices    = convexHull(vertices, vertexCount);
    _faceNormals = calculateFaceNormals(_vertices);
    calculateMomentOfInertia();
}

PolygonPath::PolygonPath(std::vector<Vector2> vertices)
{
    assert(vertices.size() >= 3);
    _vertices    = convexHull(&(vertices[0]), (unsigned int)vertices.size());
    _faceNormals = calculateFaceNormals(_vertices);
    calculateMomentOfInertia();
}

PolygonPath::PolygonPath(Rect rect)
{
    _faceNormals  = std::vector<Vector2>(4);
    _vertices     = std::vector<Vector2>(4);
    
    float halfWidth  = rect.width()  / 2.0;
    float halfHeight = rect.height() / 2.0;
    
    _vertices[0] = Vector2(-halfWidth, -halfHeight);
    _vertices[1] = Vector2( halfWidth, -halfHeight);
    _vertices[2] = Vector2( halfWidth,  halfHeight);
    _vertices[3] = Vector2(-halfWidth,  halfHeight);
    
    _faceNormals[0] = Vector2( 0.0f, -1.0f);
    _faceNormals[1] = Vector2( 1.0f,  0.0f);
    _faceNormals[2] = Vector2( 0.0f,  1.0f);
    _faceNormals[3] = Vector2(-1.0f,  0.0f);
    
    calculateMomentOfInertia();
}


void PolygonPath::calculateMomentOfInertia()
{
    // Calculate moment of interia
    float area = calculateArea(_vertices);
    float I = 0.0f;
    const float k_inv3 = 1.0f / 3.0f;
    
    for(unsigned int i1 = 0; i1 < _vertices.size(); i1++)
    {
        // Triangle vertices, third vertex implied as (0, 0)
        Vector2 p1(_vertices[i1]);
        unsigned int i2 = i1 + 1 < _vertices.size() ? i1 + 1 : 0;
        Vector2 p2(_vertices[i2]);
        
        float D = Vector2::dotProduct( p1.perpendicular(), p2 );
        
        float intx2 = p1.x * p1.x + p2.x * p1.x + p2.x * p2.x;
        float inty2 = p1.y * p1.y + p2.y * p1.y + p2.y * p2.y;
        I += (0.25f * k_inv3 * D) * (intx2 + inty2);
    }
    
    _area = area;
    _momentOfInertia = I;
}