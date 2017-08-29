//
//  Shape_Utilities.cpp
//  Drawing
//
//  Created by Adrian Russell on 07/01/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "Shape_Utilities.h"
#include <assert.h>

float massMomentForCircle(float mass, float radius)
{
    return massMomentForCircle(mass, 0.0, radius);
}

float massMomentForCircle(float mass, float innerRadius, float outerRadius)
{
    return mass * 0.5f * (innerRadius * innerRadius + outerRadius + outerRadius);
}

float areaOfCircle(float radius)
{
    return M_PI * radius * radius;
}


bool pointInCircle(Vector2 circlePosition, double radius, Vector2 point)
{
    bool inRect = (point.x >= circlePosition.x - radius && point.x <= circlePosition.x + radius && point.y >= circlePosition.y - radius && point.y <= circlePosition.y + radius);
    if(inRect) {
        double distanceSquared = sqr(circlePosition.x - point.x) + sqr(circlePosition.y - point.y);
        return distanceSquared <= sqr(radius);
    }
    return false;
}






std::vector<Vector2> convexHull(Vector2 vertices[], unsigned int count)
{
    // No hulls with less than 3 vertices (ensure actual polygon)
    assert(count >= 3);
    
    // Find the right most point on the hull
    int rightMost = 0;
    float highestXCoord = vertices[0].x;
    for(unsigned int i = 1; i < count; ++i)
    {
        float x = vertices[i].x;
        if(x > highestXCoord)
        {
            highestXCoord = x;
            rightMost = i;
        }
        
        // If matching x then take farthest negative y
        else if(x == highestXCoord)
            if(vertices[i].y < vertices[rightMost].y)
                rightMost = i;
    }
    
    int hull[count];
    int outCount = 0;
    int indexHull = rightMost;
    
    for (;;)
    {
        hull[outCount] = indexHull;
        
        // Search for next index that wraps around the hull
        // by computing cross products to find the most counter-clockwise
        // vertex in the set, given the previos hull index
        int nextHullIndex = 0;
        for(int i = 1; i < (int)count; ++i)
        {
            // Skip if same coordinate as we need three unique
            // points in the set to perform a cross product
            if(nextHullIndex == indexHull)
            {
                nextHullIndex = i;
                continue;
            }
            
            // Cross every set of three unique vertices
            // Record each counter clockwise third vertex and add
            // to the output hull
            // See : http://www.oocities.org/pcgpe/math2d.html
            Vector2 e1 = vertices[nextHullIndex] - vertices[hull[outCount]];
            Vector2 e2 = vertices[i] - vertices[hull[outCount]];
            float c = Vector2::dotProduct( e1.perpendicular(), e2 );
            if(c < 0.0f)
                nextHullIndex = i;
            
            // Cross product is zero then e vectors are on same line
            // therefor want to record vertex farthest along that line
            if(c == 0.0f && e2.squareLength( ) > e1.squareLength( ))
                nextHullIndex = i;
        }
        
        ++outCount;
        indexHull = nextHullIndex;
        
        // Conclude algorithm upon wrap-around
        if(nextHullIndex == rightMost) {
            break;
        }
    }
    
    std::vector<Vector2> m_v_vertices = std::vector<Vector2>(outCount);
    
    
    // Copy vertices into shape's vertices
    for(unsigned int i = 0; i < outCount; ++i)
        m_v_vertices[i] = vertices[hull[i]];
    
    
    return m_v_vertices;
}

std::vector<Vector2> calculateFaceNormals(std::vector<Vector2> vertices)
{
    unsigned int vertexCount = (unsigned int)vertices.size();
    
    std::vector<Vector2> normals = std::vector<Vector2>(vertexCount);
    
    
    for(unsigned int i1 = 0; i1 < vertexCount; i1++)
    {
        unsigned int i2 = i1 + 1 < vertexCount ? i1 + 1 : 0;
        
        // create face of body from 2 adjasent vertices;
        Vector2 face = vertices[i2] - vertices[i1];
        
        // assert that all faces have a length larger than 0;
        assert( face.squareLength() > sqr(EPSILON) );
        
        // Calculate the normal by fetching perpendicular of face then normalising vector;
        normals[i1] =  face.reversePerpendicular().normalise();
    }
    return normals;
}



std::vector<Vector2> regularPolygon(unsigned int vertexCount, float radius)
{
    std::vector<Vector2> points(0);
    
    for (unsigned int i = 0; i < vertexCount; i++) {
        //calculate one numther degree and then make point radius away from center
        float angle = (-2 * M_PI * i) / (float)vertexCount;
        Vector2 v = Vector2(radius * cos(angle), radius * sin(angle));
        points.push_back(v);
    }
    return points;
}

float calculateArea(std::vector<Vector2> vertices)
{
    unsigned int vertexCount = (unsigned int)vertices.size();
    float area = 0.0f;
    
    for (unsigned int i = 0; i < vertexCount; i++) {
        // Triangle vertices, third vertex implied as (0, 0)
        Vector2 p1( vertices[i] );
        unsigned int j = (i + 1 < vertexCount) ? i + 1 : 0;
        Vector2 p2( vertices[j] );
        
        float D = Vector2::dotProduct( p1.perpendicular(), p2 );
        float triangleArea = 0.5f * D;
        area += triangleArea;
    }
    return area;
}


std::vector<Vector2> randomShape(float minimumRadius, float maximumRadius)
{
    unsigned int count = (unsigned int)randomInRange(3, 30);
    Vector2 *vertices = new Vector2[count];
    float e = randomInRange(minimumRadius, maximumRadius);
    for(unsigned int i = 0; i < count; ++i)
        vertices[i] = Vector2( randomInRange(-e, e), randomInRange(-e, e) );
    
    std::vector<Vector2> final = convexHull(vertices, count);
    delete[] vertices;
    return final;
}




