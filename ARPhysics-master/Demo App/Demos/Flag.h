//
//  Flag.h
//  ARPhysics
//
//  Created by Adrian Russell on 29/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __ARPhysics__Flag__
#define __ARPhysics__Flag__

#include "PhysicsDemo.h"

class Flag : public PhysicsDemo
{
public:
    Flag();
    ~Flag();
    
    std::string name() { return "Flag"; };
    void keyPressed(unsigned char key, int x, int y);
    
    void update(float dt) { world->step(1.0/30.0); }
    
    void draw();
    
    void mouseEvent(int button, int state, int x, int y);
    void mouseMoved(int x, int y);
    
    
    
private:
    float _gravityDirection;
    GravityForceGenerator *_gravityForceGenerator;
    LinearForceGenerator  *_wind;
    bool _blowWind;
    
    std::unordered_map<Body *, std::vector<DampedSpring *>> _constraintsForBodies;
    
    
    void springFailFunc(DampedSpring *spring);
    
    bool leftMousePressed;
    bool rightMousePressed;
    
    Body   *mouseBody;
    Spring *mouseSpring;
};

#endif /* defined(__ARPhysics__Flag__) */
