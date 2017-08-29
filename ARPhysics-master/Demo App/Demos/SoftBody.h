//
//  SoftBody.h
//  Drawing
//
//  Created by Adrian Russell on 14/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__SoftBody__
#define __Drawing__SoftBody__

#include "PhysicsDemo.h"

class SoftBody : public PhysicsDemo
{
public:
    SoftBody();
    ~SoftBody();
    
    std::string name() { return "Soft Body"; };
    
    void mouseMoved(int x, int y);
    void mouseEvent(int button, int state, int x, int y);
    
protected:
    Body   *mouseBody;
    Spring *mouseSpring;
};

#endif /* defined(__Drawing__SoftBody__) */
