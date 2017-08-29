//
//  BlackHoleDemo.cpp
//  Drawing
//
//  Created by Adrian Russell on 16/12/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "BlackHoleDemo.h"
//#include "TestingIndexing.h"

#define NUMBER_OF_PARTICLES 90
#define COLLISION_LEVEL 1

// TODO: add ball bounce demo, roll down hill then fall off and bounce on floor


BlackHoleDemo::BlackHoleDemo()
{
    BruteForceIndexing *bruteForce = new BruteForceIndexing();
    
    World *world = new World(320, 240, bruteForce);
    this->world = world;
    
    bruteForce->release();
    
    _particles = new Array();
    _blackHoles = new Array();
    
    //_blackHole = new CircleBody(6.0, Vector2(150.0, 130.0), 5.0);
    //world->addBody(_blackHole);
    
    GravityToPointForceGenerator *gravityGenerator = new GravityToPointForceGenerator(30.0, Vector2(150.0, 130.0));
    world->addForceGenerator(gravityGenerator);
    _blackHoles->addObject(gravityGenerator);
    gravityGenerator->release();
    
    //gravityGenerator = new GravityToPointForceGenerator(10.0, Vector2(140.0, 130.0));
    //world->addForceGenerator(gravityGenerator);
    //_blackHoles->addObject(gravityGenerator);
    
    
    for (unsigned int i = 0; i < NUMBER_OF_PARTICLES; i++) {
        CircleBody *particle = new CircleBody(1, Vector2(10.0, 2.0 + 3 * i), 1.0);
        particle->setGroups(COLLISION_LEVEL);
        world->addBody(particle);
        _particles->addObject(particle);
        particle->release();
    }
    
}


BlackHoleDemo::~BlackHoleDemo()
{
    this->world->release();
    
    _particles->release();
    
    _blackHoles->release();
}


void BlackHoleDemo::mouseEvent(int button, int state, int x, int y)
{
    if (button == 0 && state == 0) {
        GravityToPointForceGenerator *gravityGenerator = (GravityToPointForceGenerator *)_blackHoles->objectAtIndex(0);
        gravityGenerator->setPoint(Vector2(x, y));
    } else if (button == 2 && state == 0) {
        GravityToPointForceGenerator *gravityGenerator = new GravityToPointForceGenerator(30.0, Vector2(x, y));
        world->addForceGenerator(gravityGenerator);
        _blackHoles->addObject(gravityGenerator);
        gravityGenerator->release();
    }
    
    
    // create a new circle
    
    // or delete a circle
}


void BlackHoleDemo::mouseMoved(int x, int y)
{
    
}

void BlackHoleDemo::keyPressed(unsigned char key, int x, int y)
{
    if (key == '1') {
        for (unsigned int i = 0; i < _particles->count(); i++) {
            CircleBody *particle = (CircleBody *)_particles->objectAtIndex(i);
            if (particle->collisionGroups() == COLLISION_LEVEL) {
                particle->setGroups(0);
            } else {
                particle->setGroups(COLLISION_LEVEL);
            }
        }
    }
}


void BlackHoleDemo::draw()
{
    for (unsigned int i = 0; i < _blackHoles->count(); i++) {
        GravityToPointForceGenerator *gravityGenerator = (GravityToPointForceGenerator *)_blackHoles->objectAtIndex(i);
        drawCircle(gravityGenerator->position(), gravityGenerator->force() / 5.0, 0.0, kBlackColor, kNoColor);
    }
    
    for (unsigned int i = 0; i < _particles->count(); i++) {
        CircleBody *particle = (CircleBody *)_particles->objectAtIndex(i);
        drawCircle(particle->position(), particle->radius(), particle->rotation(), kWhiteColor, kWhiteColor);
    }
    
}
