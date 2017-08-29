//
//  BruteForceIndexing.cpp
//
//  Created by Adrian Russell on 10/10/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "BruteForceIndexing.h"
#include "Collision.h"
#include "World.h"

#define SEPERATION_STEP_COUNT 10

BruteForceIndexing::BruteForceIndexing(BodyCollisionFunc bodyCollisionFunc) : SpatialIndexing(bodyCollisionFunc)
{
    _bodies     = new Array();
    _collisions = new Array();
}

BruteForceIndexing::~BruteForceIndexing()
{
    // release all the arbiters
    for (std::pair<ArbiterKey, Arbiter *> kv : _arbiters) {
        Arbiter *arbiter = kv.second;
        arbiter->release();
    }
    
    if (_bodies != NULL) {
        _bodies->release();
    }
}

void BruteForceIndexing::setBodies(Array *bodies)
{
    if (_bodies != NULL) {
        _bodies->release();
    }
    bodies->retain();
    _bodies = bodies;
}


void BruteForceIndexing::addBody(Body *body)
{
    _bodies->addObject(body);
}

void BruteForceIndexing::removeBody(Body *body)
{
    _bodies->removeObject(body);
}

void BruteForceIndexing::removeAllBodies()
{
    _bodies->empty();
}

unsigned int BruteForceIndexing::numberOfBodies()
{
    return (unsigned int)_bodies->count();
}


Array *BruteForceIndexing::bodies()
{
    return _bodies;
};

#define HASH_COEF (3344921057ul)
#define HASH_PAIR(A, B) (ArbiterKey)(((uintptr_t)A * HASH_COEF) ^ ((uintptr_t)B * HASH_COEF))

Array * BruteForceIndexing::calculateCollisions(World *world, float dt)
{
    if (_collisions) {
        _collisions->empty();
        delete _collisions;
        _collisions = NULL;
    }
    
    
    Array *collisions = new Array();
    
    unsigned long count = this->_bodies->count();
    for (unsigned long i = 0; i < count; i++) {
        for (unsigned long j = i+1; j < count; j++) {
            Body *a = (Body *)this->_bodies->objectAtIndex(i);
            Body *b = (Body *)this->_bodies->objectAtIndex(j);
            
            // if both objects are static then skip
            if (a->invMass() == 0.0 && b->invMass() == 0.0) {
                continue;
            }
            
            if (a->collisionGroups() && b->collisionGroups() && (a->collisionGroups() & b->collisionGroups())) {
                continue;
            }
            
            
            // swap the types if necessary
            if (a->bodyType() > b->bodyType()) {
                Body *c = a;
                a = b;
                b = c;
            }
            
            bool exists = true;
            
            // get the arbiter if it exists
            Arbiter *arbiter = NULL;
            ArbiterKey key = HASH_PAIR(a, b);
            std::unordered_map<ArbiterKey, Arbiter *>::const_iterator got = _arbiters.find(key);
            if (got != _arbiters.end()) {
                arbiter = got->second;
                arbiter->retain();
            } else {
                arbiter = new Arbiter(a, b);
                exists = false;
                
            }
            
            _bodyCollisionFunc(a, b, arbiter);
            
            World::CollisionHandler handler = world->collisionHandlerForBodies(a, b);
            
            if (arbiter->contact_count) {
                
                
                bool shouldBeIgnored = (arbiter->state == Arbiter::ArbiterStateIgnoring);
                
                if (arbiter->state == Arbiter::ArbiterStateNoCollision) {
                    arbiter->state = Arbiter::ArbiterStateFirstContact;
                    shouldBeIgnored = !handler.begin(arbiter);
                    arbiter->state = Arbiter::ArbiterStateContact;
                } else if (!shouldBeIgnored) {
                    arbiter->state = Arbiter::ArbiterStateContact;
                }
                
                if (shouldBeIgnored) {
                    arbiter->state = Arbiter::ArbiterStateIgnoring;
                }
                
                
                if (arbiter->state == Arbiter::ArbiterStateContact && handler.presolve(arbiter)) {
                    collisions->addObject(arbiter);
                }
                
                
                
                if (!exists) {
                    std::pair<ArbiterKey, Arbiter *> pair (key, arbiter);
                    _arbiters.insert(pair);
                    arbiter->retain();
                }
                
            } else {
                
                
                if (arbiter->state == Arbiter::ArbiterStateContact || arbiter->state == Arbiter::ArbiterStateIgnoring) {
                    arbiter->state = Arbiter::ArbiterStateSeparated;
                    handler.end(arbiter);
                }
                
                
            }
            
            arbiter->release();
            
            
            if (exists) {
                unsigned int seperationCount = arbiter->increaseStepCount();
                if (seperationCount >= SEPERATION_STEP_COUNT) {
                    _arbiters.erase(key);
                    arbiter->release();
                }
            }
            
        }
    }
    
    
    _collisions = collisions;
    
    return collisions;
}

Array *BruteForceIndexing::arbiters(bool includeIngnored)
{
    return _collisions;
}

Arbiter *BruteForceIndexing::collisionForBodies(Body *a, Body *b)
{
    Arbiter *arbiter = NULL;
    ArbiterKey key = HASH_PAIR(a, b);
    std::unordered_map<ArbiterKey, Arbiter *>::const_iterator got = _arbiters.find(key);
    if (got != _arbiters.end()) {
        arbiter = got->second;
    }
    
    return arbiter;
}

Array *BruteForceIndexing::bodiesInCircularArea(Vector2 center, float radius)
{
    Array *array = new Array();
    for (unsigned int i = 0; i < _bodies->count(); i++) {
        Body *b = (Body *)_bodies->objectAtIndex(i);
        
        if (circleVSbodyIntersection(center, radius, b)) {
            array->addObject(b);
        }
    }
    return array;
}

Array *BruteForceIndexing::bodiesInRectanglarArea(Rect rect)
{
    return nullptr;
}


Body *BruteForceIndexing::closestBodyToPoint(Vector2 point)
{
    Body *closestBody     = NULL;
    float closestDistance = INFINITY;
    for (unsigned int i = 0; i < _bodies->count(); i++) {
        Body *b = (Body *)_bodies->objectAtIndex(i);
        float distance = Vector2::distance(point, b->position());
        if (distance < closestDistance) {
            closestBody = b;
            closestDistance = distance;
        }
    }
    return closestBody;
}


