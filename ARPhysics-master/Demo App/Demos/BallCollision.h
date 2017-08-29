//
//  BallCollision.h
//  Drawing
//
//  Created by Adrian Russell on 07/01/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__BallCollision__
#define __Drawing__BallCollision__

#include "PhysicsDemo.h"

class BallCollision : public PhysicsDemo
{
public:
    BallCollision();
    ~BallCollision();
    
    std::string name() { return "Selection of Features"; };
    
    void mouseMoved(int x, int y);
    void mouseEvent(int button, int state, int x, int y);
    
protected:
    Body   *mouseBody;
    Spring *mouseSpring;
};

#endif /* defined(__Drawing__BallCollision__) */
