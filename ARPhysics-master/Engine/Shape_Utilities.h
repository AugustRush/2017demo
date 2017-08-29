//
//  Shape_Utilities.h
//  Drawing
//
//  Created by Adrian Russell on 07/01/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__Shape_Utilities__
#define __Drawing__Shape_Utilities__

#include "types.h"
#include "Vector2.h"
#include <vector>

float massMomentForCircle(float mass, float radius);

float massMomentForCircle(float mass, float innerRadius, float outerRadius);

float areaOfCircle(float radius);

//float areaOfPolygon(Vector2 vertices[], size_t vertexCount);

std::vector<Vector2> convexHull(Vector2 vertices[], unsigned int count);

std::vector<Vector2> calculateFaceNormals(std::vector<Vector2> vertices);

bool pointInCircle(Vector2 circlePosition, double radius, Vector2 point);

float calculateArea(std::vector<Vector2> vertices);


/*!
 @param vertexCount
        ...
 @param radius
        ..
 @return
 */
std::vector<Vector2> regularPolygon(unsigned int vertexCount, float radius);

std::vector<Vector2> randomShape(float minimumRadius, float maximumRadius);


#endif
