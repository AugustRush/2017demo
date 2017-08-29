//
//  PolygonPlink.h
//  Drawing
//
//  Created by Adrian Russell on 14/01/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__PolygonPlink__
#define __Drawing__PolygonPlink__

#include <iostream>

#include "PhysicsDemo.h"

class PolygonPlink : public PhysicsDemo
{
public:
    PolygonPlink();
    ~PolygonPlink();
    
    void mouseMoved(int x, int y) {};
    
    void mouseEvent(int button, int state, int x, int y) {};
    
    void keyPressed(unsigned char key, int x, int y) {};
    
    void keyUnpressed(int key, int x, int y) {};
    
    std::string name() { return "Polygon Plink"; };
    
    void update(float dt);
};

#endif /* defined(__Drawing__PolygonPlink__) */
