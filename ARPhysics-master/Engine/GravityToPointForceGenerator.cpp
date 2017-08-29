//
//  GravityToPointForceGenerator.cpp
//  Drawing
//
//  Created by Adrian Russell on 02/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "GravityToPointForceGenerator.h"

GravityToPointForceGenerator::GravityToPointForceGenerator(float f, Vector2 point) : GroupForceGenerator()
{
    _point = point;
    _force = f;
}

void GravityToPointForceGenerator::setPoint(Vector2 point)
{
    _point = point;
}

void GravityToPointForceGenerator::setForce(float force)
{
    _force = force;
}


void GravityToPointForceGenerator::applyToBody(Body *b, float dt)
{
    if (b->invMass() == 0.0) return;
    
    Vector2 distance = _point - b->position();
    
    Vector2 gravity = distance.relativeDirection() * _force;
    
    Vector2 force = (gravity * b->mass()) * dt;
    b->applyImpulse(force, b->position());
}