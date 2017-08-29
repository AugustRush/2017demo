//
//  BallCollision.cpp
//  Drawing
//
//  Created by Adrian Russell on 07/01/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "BallCollision.h"
#include "Shape_Utilities.h"

#define NUMBER_OF_BALLS 4
#define GRAVITY_FORCE   Vector2(0.0, -9.81)

BallCollision::BallCollision()
{
    mouseSpring = NULL;
    mouseBody = NULL;
    
    BruteForceIndexing *bruteForce = new BruteForceIndexing();
    
    World *world = new World(160, 120, bruteForce);
    this->world = world;
    
    bruteForce->release();
    
    // floor
    
    PolygonBody *floor = new PolygonBody(Rect(4,4,world->getWidth() - 8, 4), 0.0);
    floor->setStatic();
    world->addBody(floor);
    floor->release();
    
    // first triangle
    Vector2 points[3] = {Vector2(-3, -3), Vector2(-3, 3), Vector2(3,3)};
    PolygonBody *triangle = new PolygonBody(Vector2(50.0, 50.0), 3.0, points, 3);
    triangle->setRotation(0.3);
    world->addBody(triangle);
    triangle->release();
    
//    CircleBody *ball1 = new CircleBody(5.0, Vector2(10.0, 20.0), 0.0);
//    world->addBody(ball1);
//    ball1->release();
//    
//    CircleBody *ball2 = new CircleBody(5.0, Vector2(25.0, 20.0), 0.0);
//    world->addBody(ball2);
//    ball2->release();
//    
    for (unsigned int i = 0; i < NUMBER_OF_BALLS; i++) {
        CircleBody *ball = new CircleBody(5.0, Vector2(11.0 + (i * 11.0), 70), 3.0);
        world->addBody(ball);
        ball->release();
    }
    
    // shapes on springs
    for (unsigned int i = 3; i < 10; i++) {
        std::vector<Vector2> polygonFaces = regularPolygon(i, 5.0);
        PolygonBody *polygon = new PolygonBody(Vector2(50.0 + (i * 12) - 5.0, 100.0), 3.0, polygonFaces);
        world->addBody(polygon);
        
        Vector2 rodPosition = Vector2(50.0 + (i * 12), 110.0);
        PolygonPath *boxPath = new PolygonPath(Rect(0.0, 0.0, 1.0, 1.0));
        PolygonBody *anchor = new PolygonBody(rodPosition, 0.0, boxPath);
        world->addBody(anchor);
        
        
        DampedSpring *spring = new DampedSpring(polygon, anchor, 0.5, i*5.0, 100.0);
        world->addConstraint(spring);
        spring->release();
        
        polygon->release();
        anchor->release();
        boxPath->release();
    }
    
    // shapes on rods
    for (unsigned int i = 4; i < 9; i++) {
        std::vector<Vector2> polygonFaces = regularPolygon(i, 5.0);
        PolygonBody *polygon = new PolygonBody(Vector2(-35.0 + (i * 12) - 5.0, 80.0), 3.0, polygonFaces);
        world->addBody(polygon);
        
        Vector2 rodPosition = Vector2(-30.0 + (i * 12), 110.0);
        PolygonPath *boxPath = new PolygonPath(Rect(0.0, 0.0, 1.0, 1.0));
        PolygonBody *anchor = new PolygonBody(rodPosition, 0.0, boxPath);
        world->addBody(anchor);
        
        float dist = Vector2::distance(polygon->position(), anchor->position());
        Rod *rod = new Rod(polygon, anchor, dist);
        world->addConstraint(rod);
        rod->release();
        
        polygon->release();
        anchor->release();
        boxPath->release();
    }
    
    
    
    GravityForceGenerator *gravity = new GravityForceGenerator(GRAVITY_FORCE);
    world->addForceGenerator(gravity);
    gravity->release();
}

BallCollision::~BallCollision()
{
    this->world->release();
}



void BallCollision::mouseMoved(int x, int y)
{
    if (mouseBody != NULL) {
        mouseBody->setPosition(Vector2(x,y));
    }
}


void BallCollision::mouseEvent(int button, int state, int x, int y)
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


