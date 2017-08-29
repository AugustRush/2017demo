//
//  Pyramid.h
//
//  Created by Adrian Russell on 03/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__Pyramid__
#define __Drawing__Pyramid__

#include "PhysicsDemo.h"

class Pyramid : public PhysicsDemo
{
public:
    Pyramid();
    ~Pyramid();
    
    std::string name() { return "Pyramid"; };
};

#endif
