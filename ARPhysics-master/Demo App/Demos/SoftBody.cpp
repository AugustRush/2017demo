//
//  SoftBody.cpp
//  Drawing
//
//  Created by Adrian Russell on 14/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "SoftBody.h"

#define GRAVITY_FORCE   Vector2(0.0, -20)

void addSoftBody(World *world, Vector2 origin, float radius, unsigned int width, unsigned int height, float totalMass);

SoftBody::SoftBody()
{
    mouseBody = NULL;
    mouseSpring = NULL;
    
    BruteForceIndexing *bruteForce = new BruteForceIndexing();
    World *world = new World(320, 240, bruteForce);
    this->world = world;
    bruteForce->release();
    addBorderWallsToWorld(world, 0.5);
    
    // add gravity force generator
    GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravity);
    gravity->release();
    
    addSoftBody(world, Vector2(45.0, 15.0), 5.0, 4, 4, 2.0*4*4);
    
    addSoftBody(world, Vector2(45.0, 85.0), 5.0, 8, 3, 2.0*8*3);
    
    addSoftBody(world, Vector2(45.0, 125.0), 5.0, 6, 6, 2.0*36);
    
}


void addSoftBody(World *world, Vector2 origin, float radius, unsigned int width, unsigned int height, float totalMass)
{
    std::vector<CircleBody *>bodies(0);
    
    float bodyMass = totalMass / (width * height);
    
    for (unsigned int y = 0; y < height; y++) {
        for (unsigned int x = 0; x < width; x++) {
            CircleBody *circle = new CircleBody(radius, Vector2(origin.x-radius + (x*(radius*2)), origin.y-radius + (y*(radius*2))), bodyMass);
            //circle->setInertia(0.0);
            
            if (x > 0) {
                CircleBody *c2 = (CircleBody *)bodies.back();
                Spring *spring = new Spring(circle, c2, 0.95, Vector2::distance(circle->position(), c2->position()));
                world->addConstraint(spring);
            }
            
            if (y > 0) {
                CircleBody *c2 = bodies[((y-1) * (width)) + x];
                Spring *spring = new Spring(circle, c2, 0.95, Vector2::distance(circle->position(), c2->position()));
                world->addConstraint(spring);
            }
            
            if (x > 0 && y > 0) {
                CircleBody *c2 = bodies[((y-1) * (width)) + x-1];
                Spring *spring = new Spring(circle, c2, 0.95, Vector2::distance(circle->position(), c2->position()));
                world->addConstraint(spring);
            }
            
            if (x < width-1 && y > 0) {
                CircleBody *c2 = bodies[((y-1) * (width)) + x+1];
                Spring *spring = new Spring(circle, c2, 0.95, Vector2::distance(circle->position(), c2->position()));
                world->addConstraint(spring);
            }
            
            bodies.push_back(circle);
        }
    }
    
    for (CircleBody *body : bodies) {
        world->addBody(body);
        body->release();
    }
}

SoftBody::~SoftBody()
{
    this->world->release();
}


void SoftBody::mouseMoved(int x, int y)
{
    if (mouseBody != NULL) {
        mouseBody->setPosition(Vector2(x,y));
    }
}


void SoftBody::mouseEvent(int button, int state, int x, int y)
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



