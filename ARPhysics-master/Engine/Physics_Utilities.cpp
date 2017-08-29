//
//  Physics_Utilities.cpp
//  Drawing
//
//  Created by Adrian Russell on 04/12/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Physics_Utilities.h"
#include <assert.h>

float attrativeForce(float mass1, float mass2, float distance)
{
    assert(mass1 >= 0.0);
    assert(mass2 >= 0.0);
    assert(distance >= 0.0);
    return attrativeForce(mass1, mass2, distance, kGravitionalConstant);
}

float attrativeForce(float mass1, float mass2, float distance, float gravitationalConstant)
{
    assert(mass1 >= 0.0);
    assert(mass2 >= 0.0);
    assert(distance >= 0.0);
    assert(gravitationalConstant >= 0.0);
    return (gravitationalConstant * mass1 * mass2) / (distance * distance);
}


float gravityOfBody(float mass, float distance)
{
    return attrativeForce(1, mass, distance);
}

float gravityOfBody(float mass, float distance, float gravitationalConstant)
{
     return attrativeForce(1, mass, distance, gravitationalConstant);
}


