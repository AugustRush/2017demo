//
//  Friction.cpp
//  Drawing
//
//  Created by Adrian Russell on 14/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "Friction.h"

#define GRAVITY_FORCE   Vector2(0.0, -10)

Friction::Friction()
{
    BruteForceIndexing *indexing = new BruteForceIndexing();
    world = new World(320, 240, indexing, 5);
    indexing->release();
    
    // add gravity force generator
    GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravity);
    gravity->release();
    
    for (int i = 0; i < 4; i++) {
        PolygonBody *slide = new PolygonBody(Rect(0.0, 0.0, 100.0, 5.0), 0.0);
        slide->setRotation(-M_PI / 12);
        slide->setPosition(Vector2(60.0, (60*i) + 20.0));
        slide->setStaticFriction(0.5);
        slide->setDynamicFriction(0.3);
        world->addBody(slide);
        slide->release();
        
        PolygonBody *block = new PolygonBody(Rect(0.0, 0.0, 8.0 ,8.0), 1.0);
        block->setPosition(Vector2(50.0, (60*i) + 40.0));
        block->setStaticFriction(0.2 + (i*0.2));
        block->setDynamicFriction(0.1 + (i*0.2));
        world->addBody(block);
        block->release();
    }
}


Friction::~Friction()
{
    world->release();
}