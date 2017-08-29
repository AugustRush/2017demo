//
//  ClothWithBalls.h
//  ARPhysics
//
//  Created by Adrian Russell on 25/06/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __ARPhysics__ClothWithBalls__
#define __ARPhysics__ClothWithBalls__

#include "PhysicsDemo.h"

class ClothWithBalls : public PhysicsDemo
{
public:
    ClothWithBalls();
    ~ClothWithBalls();
    
    std::string name() { return "Cloth With Balls"; };
    void keyPressed(unsigned char key, int x, int y);
    
    void update(float dt);
    
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
    Array *balls;
    unsigned long _simCount;
};

#endif /* defined(__ARPhysics__ClothWithBalls__) */
