//
//  CircleBlink.cpp
//  Drawing
//
//  Created by Adrian Russell on 14/01/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "CirclePlink.h"


#define NUMBER_OF_BALLS 4
#define GRAVITY_FORCE   Vector2(0.05, -9.81)
#define PLINK_ROWS 15
#define PLINK_COLS 8

#define DROP_ROWS 12
#define DROP_COLS 20

CirclePlink::CirclePlink()
{
    BruteForceIndexing *bruteForce = new BruteForceIndexing();
    
    World *world = new World(320, 240, bruteForce);
    this->world = world;
    
    bruteForce->release();
    
    
    for (unsigned int i = 0; i < PLINK_ROWS; i++) {
        for (unsigned int j = 0; j < PLINK_COLS; j++) {
            CircleBody *peg = new CircleBody(5.0, Vector2(10.0 * ((i*2)+1+(j%2)), 20.0 * (j+1)), 0.0);
            world->addBody(peg);
            peg->release();
        }
    }
    
    for (unsigned int i = 0; i < DROP_COLS; i++) {
        for (unsigned int j = 0; j < DROP_ROWS; j++) {
            CircleBody *ball = new CircleBody(2.0, Vector2(12.0 * ((i*2)+1+(j%2)), 250.0 + 20.0 * (j+1)), 1.0);
            world->addBody(ball);
            ball->release();
        }
    }

    
    // add gravity
    GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravity);
    gravity->release();
}

CirclePlink::~CirclePlink()
{
    this->world->release();
}

void CirclePlink::update(float dt)
{
    world->step(dt);
    //Array *bodies = world->getBodies();
//    for (unsigned int i = 0; i < bodies->count(); i++) {
//        Body *b = (Body *)bodies->objectAtIndex(i);
//        if (b->isStatic()) {
//            continue;
//        }
//        Vector2 position = b->getPosition();
//        if (position.y < -10.0 || position.x < -10.0 || position.x > world->getWidth() + 10.0) {
//            position.y = 300.0;
//            position.x = (float)(std::rand() % (int)world->getWidth());
//            b->setPosition(position);
//            b->setVelocity(Vector2::Vector2Zero);
//        }
//    }
    
}