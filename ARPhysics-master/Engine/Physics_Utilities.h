//
//  Physics_Utilities.h
//  Drawing
//
//  Created by Adrian Russell on 04/12/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __ARPhysics__Physics_Utilities__
#define __ARPhysics__Physics_Utilities__

#include "types.h"
#include "Vector2.h"

/*! The real gravitational constant */
static const float kGravitionalConstant = 6.67284e-11;

float attrativeForce(float mass1, float mass2, float distance);

/**
 Work out the attractive force of two bodies over a specified distance but using a custom gravitational constant.
 */
float attrativeForce(float mass1, float mass2, float distance, float gravitationalConstant);


float gravityOfBody(float mass, float distance);


float gravityOfBody(float mass, float distance, float gravitationalConstant);


#endif
