//
//  DistanceForceGenerator.h
//
//  Created by Adrian Russell on 09/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__DistanceForceGenerator__
#define __Drawing__DistanceForceGenerator__

#include "ForceGenerator.h"

class DistanceForceGenerator : public ForceGenerator
{
public:
    DistanceForceGenerator(Vector2 position, float radius) : ForceGenerator()
    {
        _position = position;
        _radius   = radius;
    }
    
    virtual bool shouldApplyToBody(Body *b)
    {
        Vector2 bPos = b->position();
        return (Vector2::distance(bPos, _position) < _radius);
    }
    
    
protected:
    Vector2 _position;
    float   _radius;
};

#endif
