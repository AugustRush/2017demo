//
//  CircleBlink.h
//  Drawing
//
//  Created by Adrian Russell on 14/01/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__CircleBlink__
#define __Drawing__CircleBlink__

#include "PhysicsDemo.h"

class CirclePlink : public PhysicsDemo
{
public:
    CirclePlink();
    ~CirclePlink();
    
    void mouseMoved(int x, int y) {};
    
    void mouseEvent(int button, int state, int x, int y) {};
    
    void keyPressed(unsigned char key, int x, int y) {};
    
    void keyUnpressed(int key, int x, int y) {};
    
    std::string name() { return "Circle Plink"; };
    
    void update(float dt);
};


#endif /* defined(__Drawing__CircleBlink__) */
