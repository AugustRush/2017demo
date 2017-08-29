//
//  LinearForceGenerator.h
//
//  Created by Adrian Russell on 02/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__LinearForceGenerator_H_
#define __Drawing__LinearForceGenerator_H_

#include "GroupForceGenerator.h"

/*! Applies a linear force to a body. */
class LinearForceGenerator : public GroupForceGenerator {
public:
    
    /*!
     
     @param f
            ...
     */
    LinearForceGenerator(Vector2 f);
    
    void setForce(Vector2 f) {_force = f;}
    
    void applyToBody(Body *b, float dt);
    
private:
    Vector2        _force;  // the force to be applied to bodies.
    CollisionGroup _groups; // the collision groups to apply the force
};

#endif