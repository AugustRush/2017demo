//
//  NewtonsCradle.cpp
//  Drawing
//
//  Created by Adrian Russell on 27/03/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "NewtonsCradle.h"

#define GRAVITY_FORCE   Vector2(0.0, -9.81)
#define NUMBER_OF_BALLS 5
#define BALL_RADIUS     1.0

NewtonsCradle::NewtonsCradle()
{
    
    SpatialIndexing *bruteForce = new BruteForceIndexing();
    World *world = new World(62, 48, bruteForce, 20);
    this->world = world;
    bruteForce->release();
    //addBorderWallsToWorld(world, 0.5);
    
    GravityForceGenerator *gravityForceGenerator = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravityForceGenerator);
    gravityForceGenerator->release();
    
    
    for (unsigned int i = 0; i < NUMBER_OF_BALLS; i++) {
        
        CircleBody *b = new CircleBody(BALL_RADIUS, Vector2(10 + i * (BALL_RADIUS*2), 20), 1.0);
        b->setStaticFriction(0.0);
        b->setDynamicFriction(0.0);
        b->setRestitution(1.0);
        world->addBody(b);
        
        
        PolygonPath *path = new PolygonPath(Rect(0.0, 0.0, 0.5, 0.5));
        PolygonBody *anchor = new PolygonBody(Vector2(10 + i * (BALL_RADIUS*2), 30), 0.0, path);
        world->addBody(anchor);
        path->release();
        
        Rod *rod = new Rod(b, anchor, 10.0);
        world->addConstraint(rod);
        rod->release();
        anchor->release();
        b->release();
    }
    
    CircleBody *b = new CircleBody(BALL_RADIUS, Vector2(10 + ((NUMBER_OF_BALLS) * (BALL_RADIUS*2)) + 10.0 , 30.0), 1.0);
    b->setStaticFriction(0.0);
    b->setDynamicFriction(0.0);
    b->setRestitution(1.0);
    world->addBody(b);
    
    
    PolygonPath *path = new PolygonPath(Rect(0.0, 0.0, 0.5, 0.5));
    PolygonBody *anchor = new PolygonBody(Vector2(10 + ((NUMBER_OF_BALLS) * (BALL_RADIUS*2)), 30), 0.0, path);
    world->addBody(anchor);
    path->release();
    
    Rod *rod = new Rod(b, anchor, 10.0);
    world->addConstraint(rod);
    rod->release();
    anchor->release();
    b->release();
}

NewtonsCradle::~NewtonsCradle()
{
    this->world->release();
}




