//
//  GravityForceGenerator.h
//  Drawing
//
//  Created by Adrian Russell on 02/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__GravityForceGenerator__
#define __Drawing__GravityForceGenerator__

#include "GroupForceGenerator.h"

class GravityForceGenerator : public GroupForceGenerator {
public:
    GravityForceGenerator(Vector2 g);
    
    void setForce(Vector2 g) { _gravity = g; }
    
    void applyToBody(Body *b, float dt);
    
private:
    Vector2 _gravity;
};


#endif
