//
//  Friction.h
//  Drawing
//
//  Created by Adrian Russell on 14/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__Friction__
#define __Drawing__Friction__

#include "PhysicsDemo.h"

class Friction : public PhysicsDemo
{
public:
    Friction();
    ~Friction();
    
    std::string name() { return "Friction"; };
};

#endif /* defined(__Drawing__Friction__) */
