//
//  Cloth.h
//  Drawing
//
//  Created by Adrian Russell on 10/03/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__Cloth__
#define __Drawing__Cloth__

#include "PhysicsDemo.h"

class Cloth : public PhysicsDemo
{
public:
    Cloth();
    ~Cloth();
    
    std::string name() { return "Cloth"; };
    void keyPressed(unsigned char key, int x, int y);
    
    void update(float dt) { world->step(1.0/30.0); }
    
    void draw();
    
    void mouseEvent(int button, int state, int x, int y);
    void mouseMoved(int x, int y);
    
    
    
private:
    float _gravityDirection;
    GravityForceGenerator *_gravityForceGenerator;
    
    std::unordered_map<Body *, std::vector<DampedSpring *>> _constraintsForBodies;
    
    
    void springFailFunc(DampedSpring *spring);
    
    bool leftMousePressed;
    bool rightMousePressed;
    
    Body   *mouseBody;
    Spring *mouseSpring;
};

#endif
