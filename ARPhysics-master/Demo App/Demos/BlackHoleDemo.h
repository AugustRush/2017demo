//
//  BlackHoleDemo.h
//  Drawing
//
//  Created by Adrian Russell on 16/12/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__BlackHoleDemo__
#define __Drawing__BlackHoleDemo__

#include "PhysicsDemo.h"
#include "ForceGenerator.h"

class BlackHoleDemo : public PhysicsDemo {
    
public:
    BlackHoleDemo();
    ~BlackHoleDemo();
    
    //void update();
    
    void mouseMoved(int x, int y);
    
    void mouseEvent(int button, int state, int x, int y);
    
    void keyPressed(unsigned char key, int x, int y);
    
    void keyUnpressed(int key, int x, int y) {};
    
    std::string name() { return "Black Hole"; };
    
    void draw();
    
private:
    Array *_blackHoles;
    Array *_particles;
};

#endif /* defined(__Drawing__BlackHoleDemo__) */
