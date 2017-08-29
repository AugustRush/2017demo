//
//  ClothWithBalls.cpp
//  ARPhysics
//
//  Created by Adrian Russell on 25/06/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "ClothWithBalls.h"
#include "World_Utilities.h"

#define GRAVITY_FORCE   Vector2(0.1, -20)
#define CLOTH_LEVEL     1
#define BALL_LEVEL      2
#define WIDTH           32

using namespace std::placeholders;

void ClothWithBalls::springFailFunc(DampedSpring *spring)
{
    this->world->removeConstraint(spring);
}


ClothWithBalls::ClothWithBalls()
{
    _simCount = 0;
    mouseBody = NULL;
    mouseSpring = NULL;
    
    leftMousePressed = false;
    rightMousePressed = false;
    
    _gravityDirection = 1.0;
    
    
    
    BruteForceIndexing *bruteForce = new BruteForceIndexing();
    World *world = new World(640, 480, bruteForce);
    this->world = world;
    bruteForce->release();
    
    
    
    _gravityForceGenerator = new GravityForceGenerator(GRAVITY_FORCE * _gravityDirection);
    _gravityForceGenerator->setGroups(CLOTH_LEVEL);
    world->addForceGenerator(_gravityForceGenerator);
    
    for (unsigned int y = 0; y < WIDTH; y++) {
        for (unsigned int x = 0; x < WIDTH; x++) {
            
            CircleBody *b = new CircleBody(1.0, Vector2(100 + x*10, 210+((WIDTH-y)*8)), 0.2);
            b->setGroups(CLOTH_LEVEL);
            b->setLevels(CLOTH_LEVEL);
            
            std::vector<DampedSpring *> springs(0);
            
            
            if (x != 0) {
                CircleBody *b2 = (CircleBody *)world->getBodies()->lastObject();
                DampedSpring *spring = new DampedSpring(b, b2, 0.3, 10.0, 60.0);
                spring->setCallBack(std::bind(&ClothWithBalls::springFailFunc, this, _1));
                world->addConstraint(spring);
                
                springs.push_back(spring);
                
                std::unordered_map<Body *, std::vector<DampedSpring *>>::const_iterator got = _constraintsForBodies.find(b2);
                if (got != _constraintsForBodies.end()) {
                    std::vector<DampedSpring *> springsB = got->second;
                    springsB.push_back(spring);
                    
                    _constraintsForBodies.erase(b2);
                    _constraintsForBodies.insert({ b2, springsB });
                }
            }
            
            if (y != 0) {
                CircleBody *b2 = (CircleBody *)world->getBodies()->objectAtIndex(((y-1) * (WIDTH)) + x);
                DampedSpring *spring = new DampedSpring(b, b2, 0.3, 10.0, 60.0);
                spring->setCallBack(std::bind(&ClothWithBalls::springFailFunc, this, _1));
                world->addConstraint(spring);
                
                springs.push_back(spring);
                
                std::unordered_map<Body *, std::vector<DampedSpring *>>::const_iterator got = _constraintsForBodies.find(b2);
                if (got != _constraintsForBodies.end()) {
                    std::vector<DampedSpring *> springsB = got->second;
                    springsB.push_back(spring);
                    
                    _constraintsForBodies.erase(b2);
                    _constraintsForBodies.insert({ b2, springsB });
                }
            }
            
            if (y == 0) {
                b->setStatic();
            }
            
            
            _constraintsForBodies.insert({ b, springs });
            
            world->addBody(b);
            b->release();
        }
    }
    
    addBorderWallsToWorld(world, 4.0, 0.1);
    
    balls = new Array();
    for (int i = 0; i < 12; i++) {
        //
        CircleBody *c = new CircleBody(10.0, Vector2(25.0*i, 15.0), 1.0);
        c->setLevels(BALL_LEVEL);
        world->addBody(c);
        c->applyImpulse(Vector2(120.0,100.0), Vector2());
        balls->addObject(c);
        c->release();
    }
}

void ClothWithBalls::update(float dt)
{
    _simCount++;
    if ((_simCount % 300) == 0) {
        for (unsigned int i = 0; i < balls->count(); i++) {
            CircleBody *b = (CircleBody *)balls->objectAtIndex(i);
            b->applyImpulse(Vector2(randomInRange(-150.0, 150.0), randomInRange(-150.0, 150.0)), Vector2());
        }
    }
    world->step(1.0/30.0);
}

void ClothWithBalls::draw()
{
    Array *constraints = world->getConstraints();
    for (unsigned int i = 0; i < constraints->count(); i++) {
        Constraint *spring = (Constraint *)constraints->objectAtIndex(i);
        
        Color springColor = (spring == mouseSpring) ? kGreenColor : kWhiteColor;
        
        drawLine(spring->getA()->position(), spring->getB()->position(), springColor);
    }
    
    for (unsigned int i = 0; i < balls->count(); i++) {
        CircleBody *b = (CircleBody *)balls->objectAtIndex(i);
        drawCircleBody(b, kRedColor, kWhiteColor, false);
    }
}

void ClothWithBalls::keyPressed(unsigned char key, int x, int y)
{
    if (key =='1') {
        _gravityDirection *= -1.0;
        _gravityForceGenerator->setForce(GRAVITY_FORCE * _gravityDirection);
    }
}

void ClothWithBalls::mouseEvent(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON) {
        rightMousePressed = (state == GLUT_DOWN);
    }
    
    if (button == GLUT_LEFT_BUTTON) {
        leftMousePressed = (state == GLUT_DOWN);
        
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
}

void ClothWithBalls::mouseMoved(int x, int y)
{
    if (rightMousePressed) {
        Array *bodies = world->indexing()->bodiesInCircularArea(Vector2(x, y), 3.0);
        for (unsigned int i = 0; i < bodies->count(); i++) {
            Body *b = (Body *)bodies->objectAtIndex(i);
            std::unordered_map<Body *, std::vector<DampedSpring *>>::const_iterator got = _constraintsForBodies.find(b);
            if (got != _constraintsForBodies.end()) {
                std::vector<DampedSpring *> springs = got->second;
                
                _constraintsForBodies.erase(b);
                
                for (DampedSpring *spring : springs) {
                    world->removeConstraint(spring);
                    world->removeBody(b);
                }
            }
        }
    }
    
    if (mouseBody != NULL) {
        mouseBody->setPosition(Vector2(x,y));
    }
}

ClothWithBalls::~ClothWithBalls()
{
    _gravityForceGenerator->release();
    this->world->release();
}




