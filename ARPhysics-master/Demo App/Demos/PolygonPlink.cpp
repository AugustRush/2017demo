//
//  PolygonPlink.cpp
//  Drawing
//
//  Created by Adrian Russell on 14/01/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "PolygonPlink.h"
#include "Shape_Utilities.h"

#define GRAVITY_FORCE   Vector2(0.05, -9.81)
#define PLINK_ROWS 14
#define PLINK_COLS 8

#define DROP_ROWS 11
#define DROP_COLS 12

PolygonPlink::PolygonPlink()
{
    BruteForceIndexing *bruteForce = new BruteForceIndexing();
    
    World *world = new World(320, 240, bruteForce);
    this->world = world;
    
    bruteForce->release();
    
    std::vector<Vector2> triangleVertices = regularPolygon(3, 5.0);
    PolygonPath *trianglePath = new PolygonPath(triangleVertices);
    for (unsigned int i = 0; i < PLINK_ROWS; i++) {
        for (unsigned int j = 0; j < PLINK_COLS; j++) {
            PolygonBody *peg = new PolygonBody(Vector2(9.0 * ((i*2)+1+(j%2))+4, 20.0 * (j+1)), 0.0, trianglePath);
            peg->setStatic();
            peg->setRotation(M_PI_2);
            world->addBody(peg);
            peg->release();
        }
    }
    trianglePath->release();
    
    std::vector<Vector2> pentagonVertices = regularPolygon(5, 3.0);
    PolygonPath *pentagonPath = new PolygonPath(pentagonVertices);
    for (unsigned int i = 0; i < DROP_COLS; i++) {
        for (unsigned int j = 0; j < DROP_ROWS; j++) {
            PolygonBody *ball = new PolygonBody(Vector2(12.0 * ((i*2)+1+(j%2)), 250.0 + 20.0 * (j+1)), 1.0, pentagonPath);
            ball->setRestitution(0.05);
            world->addBody(ball);
            ball->release();
        }
    }
    pentagonPath->release();
    
    PolygonBody *leftWall = new PolygonBody(Rect(0,0,1,500), 0);
    leftWall->setStatic();
    world->addBody(leftWall);
    leftWall->release();
    
    PolygonBody *rightWall = new PolygonBody(Rect(world->getWidth() - 18.0,0,1,500), 0);
    rightWall->setStatic();
    world->addBody(rightWall);
    rightWall->release();
    
    
    // add gravity
    GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravity);
    gravity->release();
}

void PolygonPlink::update(float dt)
{
    world->step(dt);
    
    for (unsigned int i = 0; i < world->getBodies()->count(); i++) {
        Body *b = (Body *)world->getBodies()->objectAtIndex(i);
        if (b->position().y < -20) {
            Vector2 p = b->position();
            p.y = 400;
            p.x = randomInRange(3.0, world->getWidth() - 40.0);
            b->setPosition(p);
        }
    }
}


PolygonPlink::~PolygonPlink()
{
    this->world->release();
}