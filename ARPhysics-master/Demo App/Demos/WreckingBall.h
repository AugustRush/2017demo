//
//  WreckingBall.h
//  Drawing
//
//  Created by Adrian Russell on 14/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__WreckingBall__
#define __Drawing__WreckingBall__

#include "PhysicsDemo.h"

class WreckingBall : public PhysicsDemo
{
public:
    
    WreckingBall();
    ~WreckingBall();
    
    std::string name() { return "Wrecking Ball"; };
    
    void mouseMoved(int x, int y);
    void mouseEvent(int button, int state, int x, int y);
    
protected:
    Body   *mouseBody;
    Spring *mouseSpring;
};

#endif /* defined(__Drawing__WreckingBall__) */
