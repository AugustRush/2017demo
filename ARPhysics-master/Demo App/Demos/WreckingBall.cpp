//
//  WreckingBall.cpp
//  Drawing
//
//  Created by Adrian Russell on 14/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "WreckingBall.h"

#define GRAVITY_FORCE   Vector2(0.0, -20)

WreckingBall::WreckingBall()
{
    mouseBody = NULL;
    mouseSpring = NULL;
    
    BruteForceIndexing *indexing = new BruteForceIndexing();
    world = new World(320, 240, indexing, 20);
    indexing->release();
    
    // add gravity force generator
    GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravity);
    gravity->release();
    
    // add floor
    PolygonBody *floor = new PolygonBody(Rect(0.0, -2.0, 320.0, 2.0), 0.0);
    world->addBody(floor);
    floor->release();
    
    // add right wall
    PolygonBody *wall = new PolygonBody(Rect(320.0, 0.0, 2.0, 240.0), 0.0);
    world->addBody(wall);
    wall->release();
    
    // add left wall
    wall = new PolygonBody(Rect(-2.0, 0.0, 2.0, 240.0), 0.0);
    world->addBody(wall);
    wall->release();
    
    // add blocks
    for (int y = 0; y < 12; y++) {
        for (int x = 0; x < 6; x++) {
            PolygonBody *block = new PolygonBody(Rect(150 + x*10, y*10, 10, 10), 0.5);
            world->addBody(block);
            block->release();
        }
    }
    
    
    // add wrecking ball
    CircleBody *circle = new CircleBody(20.0, Vector2(30.0, 125.0), 70.0);
    world->addBody(circle);
    
    PolygonBody *staticBlock = new PolygonBody(Rect(124.5, 124.5, 1.0, 1.0), 0.0);
    world->addBody(staticBlock);
    Rod *rod = new Rod(circle, staticBlock, 100.0);
    world->addConstraint(rod);
    circle->release();
    staticBlock->release();
    rod->release();
    
}

WreckingBall::~WreckingBall()
{
    world->release();
}

void WreckingBall::mouseMoved(int x, int y)
{
    if (mouseBody != NULL) {
        mouseBody->setPosition(Vector2(x,y));
    }
}


void WreckingBall::mouseEvent(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        
        
        if (mouseSpring == NULL) {
            
            Body *bodyB = world->indexing()->closestBodyToPoint(Vector2(x, y));
            if (bodyB) {
                if (mouseBody == NULL) {
                    mouseBody = new PolygonBody(Rect(x-0.5,y-0.5,1.0,1.0), 0.0);
                    world->addBody(mouseBody);
                }
                
                mouseSpring = new Spring(mouseBody, bodyB, 0.9, 0.0);
                world->addConstraint(mouseSpring);
            }
        }
    }
    
    if (state == GLUT_UP) {
        if (mouseBody != NULL) {
            world->removeBody(mouseBody);
            mouseBody->release();
            mouseBody = NULL;
        }
        
        if (mouseSpring != NULL) {
            world->removeConstraint(mouseSpring);
            mouseSpring->release();
            mouseSpring = NULL;
        }
    }
}

