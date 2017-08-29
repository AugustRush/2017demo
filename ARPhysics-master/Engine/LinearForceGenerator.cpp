//
//  LinearForceGenerator.cpp
//  Drawing
//
//  Created by Adrian Russell on 02/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "LinearForceGenerator.h"

LinearForceGenerator::LinearForceGenerator(Vector2 f) : GroupForceGenerator()
{
    this->_force = f;
}

void LinearForceGenerator::applyToBody(Body *b, float dt)
{
    if (b->invMass() == 0.0) return;
    
    Vector2 f = _force * (dt / 2.0);
    
    b->applyImpulse(f, Vector2());
}
