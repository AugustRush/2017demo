//
//  GravityToPointForceGenerator.h
//
//  Created by Adrian Russell on 02/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __ARPhysics__GravityToPointForceGenerator_H_
#define __ARPhysics__GravityToPointForceGenerator_H_

#include "GroupForceGenerator.h"

class GravityToPointForceGenerator : public GroupForceGenerator {
public:
    GravityToPointForceGenerator(float f, Vector2 point);
    
    
    void applyToBody(Body *b, float dt);
    
    void setPoint(Vector2 point);
    
    void setForce(float force);
    
    Vector2 position()  { return _point; };
    float force() {return _force; };
    
private:
    float _force;
    Vector2 _point;
};


#endif
