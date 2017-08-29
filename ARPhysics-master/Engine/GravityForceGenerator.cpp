//
//  GravityForceGenerator.cpp
//  Drawing
//
//  Created by Adrian Russell on 02/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "GravityForceGenerator.h"

GravityForceGenerator::GravityForceGenerator(Vector2 g) : GroupForceGenerator()
{
    _gravity = g;
}

void GravityForceGenerator::applyToBody(Body *b, float dt)
{
    if (b->invMass() == 0.0) return;
    
    Vector2 force = (_gravity * b->mass()) * dt;
    b->applyImpulse(force, Vector2::Vector2Zero);
}