//
//  Beam.cpp
//  ARPhysics
//
//  Created by Adrian Russell on 28/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "Beam.h"

using namespace std::placeholders;


#define GRAVITY_FORCE   Vector2(0.0, -9.81)
//#define FLOOR_LEVEL 1
//#define BLOCK_LEVEL 2

Beam::Beam()
{
    BruteForceIndexing *indexing = new BruteForceIndexing();
    world = new World(320, 240, indexing);
    indexing->release();
    addBorderWallsToWorld(world, 1.0);

    
    GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravity);
    gravity->release();
    
    world->setDefaultCollisionHandler(std::bind(&Beam::blockHit, this, _1), NULL, NULL, NULL);
    
    
    PolygonBody *box = new PolygonBody(Rect(5,80,5,5), 1.0);
    world->addBody(box);
    _currentBody = box;
    box->release();
    
    
}

Beam::~Beam()
{
    world->release();
}

bool Beam::blockHit(Arbiter *arbiter)
{
    world->addPostStepCallback(std::bind(&Beam::makeBlockPostStep, this, _1, _2), arbiter);
    return true;
}

void Beam::makeBlockPostStep(World *world, void *key)
{
    int length = (random() % 3) * 5;
    
    int positionX = random() % (int)(world->getWidth() - 30.0) + 15.0;
    
    PolygonBody *box = new PolygonBody(Rect(positionX, 80, 5,length), 1.0);
    world->addBody(box);
    box->release();
    _currentBody = box;
}

void Beam::keyPressed(unsigned char key, int x, int y)
{
    printf("%c", key);
    if (key == GLUT_KEY_LEFT) {
        _currentBody->applyImpulse(Vector2(-3.0, 0.0), Vector2::Vector2Zero);
    } else if (key == GLUT_KEY_RIGHT) {
        _currentBody->applyImpulse(Vector2(3.0, 0.0), Vector2::Vector2Zero);
    }
}


/*
 
 BruteForceIndexing *indexing = new BruteForceIndexing();
 world = new World(32, 24, indexing, 5);
 indexing->release();
 
 // add gravity force generator
 GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
 world->addForceGenerator(gravity);
 gravity->release();
 
 CircleBody *c1 = new CircleBody(0.5, Vector2(5.0, 5.0), 0.0);
 world->addBody(c1);
 c1->release();
 
 CircleBody *c2 = new CircleBody(0.5, Vector2(5.0, 10.0), 0.0);
 world->addBody(c2);
 c2->release();
 
 int length = 5;
 for (unsigned int i = 0; i < length; i++) {
 CircleBody *c3 = new CircleBody(0.5, Vector2(10.0 + (5.0 * i), 5.0), 0.1);
 world->addBody(c3);
 
 CircleBody *c4 = new CircleBody(0.5, Vector2(10.0 + (5.0 * i), 10.0), 0.1);
 world->addBody(c4);
 
 
 c1 = (CircleBody *)world->getBodies()->objectAtIndex(world->getBodies()->count() - 4);
 c2 = (CircleBody *)world->getBodies()->objectAtIndex(world->getBodies()->count() - 3);
 
 Rod *r1 = new Rod(c1, c3, 5.0);
 world->addConstraint(r1);
 
 Rod *r2 = new Rod(c3, c4, 5.0);
 world->addConstraint(r2);
 
 Rod *r3 = new Rod(c2, c4, 5.0);
 world->addConstraint(r3);
 
 Rod *r5 = new Rod(c2, c3, std::sqrt(50));
 world->addConstraint(r5);
 
 Rod *r4 = new Rod(c1, c4, std::sqrt(50));
 world->addConstraint(r4);
 }
 
 */
