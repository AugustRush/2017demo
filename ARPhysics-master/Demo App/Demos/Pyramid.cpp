//
//  Pyramid.cpp
//  Drawing
//
//  Created by Adrian Russell on 03/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "Pyramid.h"
#include "World_Utilities.h"

#define GRAVITY_FORCE   Vector2(0.0, -9.81)
#define NUMBER_OF_ROWS  9

Pyramid::Pyramid()
{
    BruteForceIndexing *bruteForce = new BruteForceIndexing();
    World *world = new World(160, 120, bruteForce, 5);
    this->world = world;
    bruteForce->release();
    addBorderWallsToWorld(world, 1.0);
    
    GravityForceGenerator *gravityForceGenerator = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravityForceGenerator);
    gravityForceGenerator->release();
    
    
    PolygonPath *boxPath = new PolygonPath(Rect(0.0, 0.0, 10.0, 10.0));
    
    for (unsigned int i = NUMBER_OF_ROWS; i > 0; i--) {
        for (unsigned int j = 0; j < i; j++) {
            float xPos = 20 + (j * 10) + ((9-i) * 5);
            float yPos = 100 - (i * 10);
            PolygonBody *body = new PolygonBody(Vector2(xPos, yPos), 2.0, boxPath);
            body->setDynamicFriction(0.8);
            body->setStaticFriction(0.9);
            world->addBody(body);
            body->release();
        }
    }
    boxPath->release();
}


Pyramid::~Pyramid()
{
    this->world->release();
}