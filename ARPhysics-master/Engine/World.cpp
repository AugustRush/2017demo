//
//  World.cpp
//  Drawing
//
//  Created by Adrian Russell on 10/9/13.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//
//  This software is provided 'as-is', without any express or implied
//  warranty. In no event will the authors be held liable for any damages
//  arising from the use of this software. Permission is granted to anyone to
//  use this software for any purpose, including commercial applications, and to
//  alter it and redistribute it freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source
//     distribution.
//

#include "World.h"

static bool AlwaysCollide(Arbiter *collision) { return true; };
static void Nothing(Arbiter *collision) {};
//static const World::CollisionHandler defaultCollisionHandler = (World::CollisionHandler){ 0, 0, &AlwaysCollide, AlwaysCollide, Nothing, Nothing };
typedef std::pair<World::CollisionKey, World::CollisionHandler> CollisionPair;




World::World(float width, float height, SpatialIndexing *indexing, unsigned int numberOfIterations)
{
    _width  = width;
    _height = height;
    
    assert(indexing);
    indexing->retain();
    _indexing = indexing;
    
    _forceGenerators = new Array();
    
    _constraints = new Array();
    
    _defaultHandler = (World::CollisionHandler){ 0, 0, &AlwaysCollide, &AlwaysCollide, &Nothing, &Nothing };
    _numberOfIterations = numberOfIterations;
    
    _damping = 1.0;
    
    //stepsToKeepArbiters = 10;
}


World::~World()
{
    _indexing->release();
    _forceGenerators->empty();
    _forceGenerators->release();
    _constraints->empty();
    _constraints->release();
}



void World::step(float dt)
{
    // if there is no time step then don't bother
    if (dt == 0.0f) return;
    
    // if there are no bodies then don't bother
    if (_indexing->numberOfBodies() == 0) return;
    
    
    
    // == integreate forces
    for (unsigned int i = 0; i < _indexing->numberOfBodies(); i++) {
        Body *body = (Body *)_indexing->bodies()->objectAtIndex(i);
        
        // if the object is static then there are no forces to resolve.
        if (body->isStatic()) continue;
        
        // intergrate the forces here
        body->integrateForces(dt, _damping);
    }
    
    // == apply all force generators
    for (unsigned int i = 0; i < _forceGenerators->count(); i++) {
        ForceGenerator *f = (ForceGenerator *)_forceGenerators->objectAtIndex(i);
        
        Array *bodies = _indexing->bodies();
        for (unsigned int i = 0; i < bodies->count(); i++) {
            Body *body = (Body *)bodies->objectAtIndex(i);
            if (f->shouldApplyToBody(body)) {
                f->applyToBody(body, dt);
            }
        }
    }
    
    //  == detetmine colliding bodies == get all arbiters - also handles begin / seperate callbacks
    Array *arbiters = _indexing->calculateCollisions(this, dt);
    
    for (unsigned int i = 0; i < _numberOfIterations; i++) {
        
        //== abiters apply impulses
        for (unsigned int i = 0; i < arbiters->count(); i++) {
            Arbiter *c = (Arbiter *)arbiters->objectAtIndex(i);
            c->applyImpulse();
        }
        
        //== constraints apply impulses
        for (unsigned int i = 0; i < _constraints->count(); i++) {
            Constraint *c = (Constraint *)_constraints->objectAtIndex(i);
            c->solve(dt);
        }
    }
    
    
    

    
    // == arbiters poststep callback
    for (unsigned int i = 0; i < arbiters->count(); i++) {
        Arbiter *c = (Arbiter *)arbiters->objectAtIndex(i);
        CollisionHandler handler = collisionHandlerForBodies(c->bodyA(), c->bodyB());
        handler.postsolve(c);
    }
    
    
    // == integrate velocities
    for (unsigned int i = 0; i < _indexing->numberOfBodies(); i++) {
        Body *body = (Body *)_indexing->bodies()->objectAtIndex(i);
        
        // if the object is static then there are no forces to resolve.
        if (body->isStatic()) continue;
        
        // intergrate the forces here
        body->integrateVelocities(dt);
    }
    
    // positional correction
    for (unsigned int i = 0; i < arbiters->count(); i++) {
        Arbiter *c = (Arbiter *)arbiters->objectAtIndex(i);
        c->positionalCorrection();
    }
    
    
    // == arbiter end callbacks
    for (auto kv : _postStepCallbacks) {
        void *key = kv.first;
        CollisionPostStepCallBack func = kv.second;
        func(this, key);
    }
    
    
    // == clean up
    _postStepCallbacks.clear();
    
}


//---------------------------------------------------------------------//
#pragma mark - Collision Handlers

#define HASH_COEF (3344921057ul)
#define HASH_PAIR(A, B) (CollisionKey)((A * HASH_COEF) ^ (B * HASH_COEF))

World::CollisionHandler World::collisionHandlerForBodies(Body *a, Body *b)
{
    CollisionKey key = HASH_PAIR(a->collisionLevels(), b->collisionLevels());
    std::unordered_map<CollisionKey, CollisionHandler>::const_iterator got = _collisionHandlers.find(key);
    if (got == _collisionHandlers.end()) {
        return _defaultHandler;
    } else {
        return got->second;
    }
}

bool World::addCollisionHandler(CollisionLevel a, CollisionLevel b, CollisionBeginFunc begin, CollisionPreSolveFunc preSolve, CollisionPostSolveFunc postSolve, CollisionEndFunc seperate)
{
    begin     = begin     ?: AlwaysCollide;
    preSolve  = preSolve  ?: AlwaysCollide;
    postSolve = postSolve ?: Nothing;
    seperate  = seperate  ?: Nothing;
    CollisionHandler handler = (CollisionHandler){ a, b, begin, preSolve, postSolve, seperate };
    
    std::pair<CollisionKey, CollisionHandler> pair (HASH_PAIR(a, b), handler);
    std::pair<std::unordered_map<CollisionKey, CollisionHandler>::const_iterator,bool> result = _collisionHandlers.insert(pair);
    return result.second;
}

void World::setDefaultCollisionHandler(CollisionBeginFunc begin, CollisionPreSolveFunc preSolve, CollisionPostSolveFunc postSolve, CollisionEndFunc seperate)
{
    if (begin     != NULL) _defaultHandler.begin     = begin;
    if (preSolve  != NULL) _defaultHandler.presolve  = preSolve;
    if (postSolve != NULL) _defaultHandler.postsolve = postSolve;
    if (seperate  != NULL) _defaultHandler.end       = seperate;
}


bool World::removeCollisionHandler(CollisionLevel a, CollisionLevel b)
{
    size_t count = _collisionHandlers.erase(HASH_PAIR(a, b));
    return (count > 0);
}

bool World::removeAllCollisionHandlers()
{
    _collisionHandlers.clear();
    return true;
}

bool World::addPostStepCallback(CollisionPostStepCallBack func, void *key)
{
    std::pair<void *, CollisionPostStepCallBack> pair(key, func);
    std::pair<std::unordered_map<void *, CollisionPostStepCallBack>::const_iterator, bool> result = _postStepCallbacks.insert(pair);
    return result.second;
}


void World::addConstraint(Constraint *constraint)
{
    if (!_constraints->containsObject(constraint))
        _constraints->addObject(constraint);
};

void World::removeConstraint(Constraint *constraint)
{
    _constraints->removeObject(constraint);
}

void World::addForceGenerator(ForceGenerator *generator)
{
    if (!_forceGenerators->containsObject(generator))
        _forceGenerators->addObject(generator);
}

void World::removeForceGenerator(ForceGenerator *generator)
{
    _forceGenerators->removeObject(generator);
}


void World::addBody(Body *body)
{
    _indexing->addBody(body);
}

void World::removeBody(Body *body)
{
    _indexing->removeBody(body);
}
