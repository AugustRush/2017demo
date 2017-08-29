//
//  HillRoll.cpp
//  Drawing
//
//  Created by Adrian Russell on 07/03/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "HillRoll.h"
#include "PolygonBody_Utilities.h"

#define GRAVITY_FORCE   Vector2(0.0, -69.81)

#define STATIC_COLLISION_LEVEL (1)
#define OTHER_COLLISION_LEVEL (2)

bool beginStep(Arbiter *arbiter)
{
    return true;
}

HillRoll::HillRoll()
{
    BruteForceIndexing *bruteForce = new BruteForceIndexing();
    World *world = new World(320, 240, bruteForce);
    this->world = world;
    bruteForce->release();
    
    GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravity);
    gravity->release();
    
    Vector2 p[3] = {Vector2(-10, -10), Vector2(-10, 20), Vector2(90, -10)};
    PolygonBody *b = new PolygonBody(Vector2(50,50), 3.0, p, 3);
    b->setStatic();
    b->setLevels(STATIC_COLLISION_LEVEL);
    this->world->addBody(b);
    b->release();
    
    
    PolygonBody *floor = new PolygonBody(Rect(4,4,world->getWidth() - 8, 4), 0.0);
    floor->setStatic();
    floor->setLevels(STATIC_COLLISION_LEVEL);
    world->addBody(floor);
    floor->release();
    
    world->addCollisionHandler(STATIC_COLLISION_LEVEL, OTHER_COLLISION_LEVEL, beginStep, NULL, NULL, NULL);
    
}

HillRoll::~HillRoll()
{
    this->world->release();
}

void HillRoll::mouseEvent(int button, int state, int x, int y)
{
    if (state == 0) {
        if (button == 0) {
            PolygonBody *b = randomShapedBody(5.0, 10.0, Vector2(x, y), 2.0);
            b->setStaticFriction(0.9);
            b->setDynamicFriction(0.8);
            b->setLevels(OTHER_COLLISION_LEVEL);
            world->addBody(b);
            b->release();
        } else {
            CircleBody *c = new CircleBody(5.0, Vector2(x, y), 3.0);
            c->setLevels(OTHER_COLLISION_LEVEL);
            world->addBody(c);
            c->release();
        }
    }
        
}


