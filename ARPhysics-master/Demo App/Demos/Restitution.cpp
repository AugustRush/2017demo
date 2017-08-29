//
//  Restitution.cpp
//  Drawing
//
//  Created by Adrian Russell on 14/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "Restitution.h"

#define GRAVITY_FORCE   Vector2(0.0, -10)

Restitution::Restitution()
{
    BruteForceIndexing *indexing = new BruteForceIndexing();
    world = new World(160, 120, indexing, 5);
    indexing->release();
    
    // add gravity force generator
    GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravity);
    gravity->release();
    
    // add floor
    PolygonBody *floor = new PolygonBody(Rect(0.0, -2.0, 320.0, 2.0), 0.0);
    world->addBody(floor);
    floor->release();
    
    for (int i = 0; i <= 10; i++) {
        //PolygonBody *bouncer = new PolygonBody(Rect(15 * (i+1), 50.0, 5.0, 5.0), 1.0);
        CircleBody *bouncer = new CircleBody(5.0, Vector2(13 * (i+1), 100.0), 1.0);
        bouncer->setRestitution(0.1 * i);
        world->addBody(bouncer);
        bouncer->release();
    }
}

Restitution::~Restitution()
{
    world->release();
}


