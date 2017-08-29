//
//  Rod.cpp
//  Drawing
//
//  Created by Adrian Russell on 09/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "Rod.h"

Rod::Rod(Body *a, Body *b, float length) : Constraint(a, b)
{
    _length = length;
}


Rod::~Rod()
{
}

void Rod::solve(float dt)
{
    //Vector2 rodVector = this->a->position() - this->b->position();
    Vector2 rodVector = this->b->position() - this->a->position();
    float d = rodVector.length();
    Vector2 unitAxis = rodVector.normalise();
    
    float relVel = (Vector2::dotProduct( (b->velocity() - a->velocity()), unitAxis));
    
    float relDistance = d - _length;
    
    float remove = (relVel + relDistance);
    float impulse = remove / (a->invMass() + b->invMass());
    
    Vector2 impulseVec = unitAxis * impulse * dt;
    
    this->a->applyImpulse( impulseVec, Vector2(0.0,0.0));
    this->b->applyImpulse(-impulseVec, Vector2(0.0,0.0));
}