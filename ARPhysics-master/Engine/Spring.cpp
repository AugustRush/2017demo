//
//  Spring.cpp
//  ARPhysics
//
//  Created by Adrian Russell on 25/03/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "Spring.h"

const float Spring::SpringDoNotFail = INFINITY;

Spring::Spring(Body *a, Body *b, float stiffness, float restLength, float failLength) : Constraint(a, b)
{
    this->stiffness  = stiffness;
    this->restLength = restLength;
    this->failLength = failLength;
    this->failCallBack = NULL;
}



Spring::~Spring()
{
}


void Spring::setCallBack(std::function<void(Spring *)> failCallBack)
{
    this->failCallBack = failCallBack;
}

void Spring::solve(float dt)
{
    // apply forces to bodies
    
    Vector2 springVector = this->a->position() - this->b->position();
    float d = springVector.length();
    
    if (d > this->failLength) {
        //*** REMOVE CONSTRAINT ***
        if (this->failCallBack != NULL) this->failCallBack(this);
    }
    
    Vector2 bVelocity = b->velocity();
    
    Vector2 force = (springVector / d) * (d - restLength) * -stiffness;
    force += -(a->velocity() - bVelocity) * 0.01;
    
    // update position of body A
    this->a->applyImpulse(force, Vector2(0.0,0.0));
    
    if (this->b) {
        this->b->applyImpulse(-force, Vector2(0.0,0.0));
    }
    
}