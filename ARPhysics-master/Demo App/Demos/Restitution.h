//
//  Restitution.h
//  Drawing
//
//  Created by Adrian Russell on 14/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__Restitution__
#define __Drawing__Restitution__

#include "PhysicsDemo.h"

class Restitution : public PhysicsDemo
{
public:
    Restitution();
    ~Restitution();
    
    std::string name() { return "Restitution"; };
};

#endif /* defined(__Drawing__Restitution__) */
