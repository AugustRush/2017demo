//
//  HillRoll.h
//  Drawing
//
//  Created by Adrian Russell on 07/03/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__HillRoll__
#define __Drawing__HillRoll__

#include "PhysicsDemo.h"

class HillRoll : public PhysicsDemo
{
public:
    HillRoll();
    ~HillRoll();
    
    void mouseMoved(int x, int y) {};
    
    void mouseEvent(int button, int state, int x, int y);
    
    void keyPressed(unsigned char key, int x, int y) {};
    
    void keyUnpressed(int key, int x, int y) {};
    
    std::string name() { return "Hill Roll"; };
};

#endif /* defined(__Drawing__HillRoll__) */
