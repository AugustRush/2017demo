//
//  Beam.h
//  ARPhysics
//
//  Created by Adrian Russell on 28/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __ARPhysics__Beam__
#define __ARPhysics__Beam__

#include "PhysicsDemo.h"

class Beam : public PhysicsDemo
{
public:
    Beam();
    ~Beam();
    
    std::string name() { return "Beam"; };
    
    void keyPressed(unsigned char key, int x, int y);
    
    bool blockHit(Arbiter *arbiter);
    void makeBlockPostStep(World *world, void *key);
    Body *_currentBody;
};

#endif /* defined(__ARPhysics__Beam__) */
