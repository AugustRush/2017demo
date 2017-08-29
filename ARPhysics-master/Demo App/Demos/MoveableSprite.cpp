//
//  MoveableSprite.cpp
//  Drawing
//
//  Created by Adrian Russell on 09/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "MoveableSprite.h"
#include "World_Utilities.h"

#define SPRITE_LAYER      1
#define COLLECTABLE_LAYER 2
#define FINAL_LAYER       4

using namespace std::placeholders;

MoveableSprite::MoveableSprite()
{
    BruteForceIndexing *bruteForce = new BruteForceIndexing();
    World *world = new World(320, 240, bruteForce);
    this->world = world;
    bruteForce->release();
    addBorderWallsToWorld(world, 1.0);
    
    // create floor
    PolygonBody *floor = new PolygonBody(Rect(10.0, 10.0, world->getWidth() - 20.0, 4.0), 0.0);
    floor->setDynamicFriction(0.95);
    floor->setStaticFriction(0.95);
    world->addBody(floor);
    floor->release();
    
    
    // create ramp
    Vector2 p[3] = {Vector2(90, -20), Vector2(90, 20), Vector2(-20, -20)};
    PolygonBody *ramp = new PolygonBody(Vector2(160,34.0), 0.0, p, 3);
    ramp->setDynamicFriction(0.95);
    ramp->setStaticFriction(0.95);
    this->world->addBody(ramp);
    ramp->release();
    
    
    // create block thing
    PolygonBody *block = new PolygonBody(Rect(250.0, 14.0, 50.0, 100.0), 0.0);
    block->setDynamicFriction(0.95);
    block->setStaticFriction(0.95);
    world->addBody(block);
    block->release();
    
    // create sprite
    PolygonBody *sprite = new PolygonBody(Rect(0.0, 0.0, 8.0, 8.0), 1.0);
    sprite->setPosition(Vector2(30.0, 30.0));
    sprite->setDynamicFriction(0.50);
    sprite->setStaticFriction(0.75);
    sprite->setRestitution(0.2);
    sprite->setLevels(SPRITE_LAYER);
    sprite->setGroups(SPRITE_LAYER);
    _sprite = sprite;
    world->addBody(sprite);
    
    
    // create tokens
    PolygonBody *tokenA = new PolygonBody(Rect(0.0, 0.0, 5.0, 5.0), 0.0);
    tokenA->setPosition(Vector2(275.0, 150.0));
    tokenA->setGroups(COLLECTABLE_LAYER);
    tokenA->setLevels(COLLECTABLE_LAYER);
    _tokenA = tokenA;
    world->addBody(tokenA);
    
    PolygonBody *tokenB = new PolygonBody(Rect(0.0, 0.0, 5.0, 5.0), 0.0);
    tokenB->setPosition(Vector2(275.0, 200.0));
    tokenB->setGroups(COLLECTABLE_LAYER);
    tokenB->setLevels(COLLECTABLE_LAYER);
    _tokenB = tokenB;
    world->addBody(tokenB);
    
    
    // add gravity
    GravityForceGenerator *gravity = new GravityForceGenerator(Vector2(0.0, -30));
    gravity->setGroups(SPRITE_LAYER);
    world->addForceGenerator(gravity);
    gravity->release();
    
    world->addCollisionHandler(SPRITE_LAYER, FINAL_LAYER, std::bind(&MoveableSprite::finalCollisionBegin, this, _1), NULL, NULL, NULL);
    
    world->addCollisionHandler(SPRITE_LAYER, COLLECTABLE_LAYER, std::bind(&MoveableSprite::tokenCollisionBegin, this, _1), NULL, NULL, NULL);
    
    
}

void MoveableSprite::keyPressed(unsigned char key, int x, int y)
{
    printf("%c", key);
    if (key == GLUT_KEY_LEFT) {
        _sprite->applyImpulse(Vector2(-3.0, 0.0), Vector2::Vector2Zero);
    } else if (key == GLUT_KEY_RIGHT) {
        _sprite->applyImpulse(Vector2(3.0, 0.0), Vector2::Vector2Zero);
    } else if (key == GLUT_KEY_UP) {
        _sprite->applyImpulse(Vector2(0.0, 15.0), Vector2::Vector2Zero);
    }
}


MoveableSprite::~MoveableSprite()
{
    this->world->release();
}

//------------------------------------------------------------------

void MoveableSprite::removeBodyCallback(World *world, void *key)
{
    Body *body = (Body *)key;
    world->removeBody(body);
    
    if (!world->getBodies()->containsObject(_tokenA) && !world->getBodies()->containsObject(_tokenB)) {
        _tokenC = new PolygonBody(Rect(0.0, 0.0, 5.0, 5.0), 0.0);
        _tokenC->setPosition(Vector2(30.0, 30.0));
        _tokenC->setGroups(FINAL_LAYER);
        _tokenC->setLevels(FINAL_LAYER);
        world->addBody(_tokenC);
    }
    
}

void MoveableSprite::removeFinalBodyCallback(World *world, void *key)
{
    Body *body = (Body *)key;
    world->removeBody(body);
}

#define CRASH_IT 0
bool MoveableSprite::tokenCollisionBegin(Arbiter *arbiter)
{
#if CRASH_IT
    removeBodyCallback(world, arbiter->bodyB());
#else
    world->addPostStepCallback( std::bind(&MoveableSprite::removeBodyCallback, this, _1, _2) , arbiter->bodyB());
#endif
    
    return false;
}

bool MoveableSprite::finalCollisionBegin(Arbiter *arbiter)
{
    world->addPostStepCallback(std::bind(&MoveableSprite::removeFinalBodyCallback, this, _1, _2), arbiter->bodyB());
    return false;
}

