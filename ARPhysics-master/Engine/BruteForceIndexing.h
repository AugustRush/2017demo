//
//  BruteForceIndexing.h
//
//  Created by Adrian Russell on 10/10/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
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

#ifndef __ARPhysics__BruteForceIndexing_H__
#define __ARPhysics__BruteForceIndexing_H__

#include "SpatialIndexing.h"
#include <unordered_map>
#include "Collision.h"

/*! The brute force indexing system is the simplest indexing system supplied. It will check every body against everyother body for collisions each step.
 */
class BruteForceIndexing : public SpatialIndexing
{    
public:
    
    /*! Constructs a new brute force spatial indexing system ready for use with a world Object. */
    BruteForceIndexing(BodyCollisionFunc bodyCollisionFunc = collideBodies);
    
    /*! Brute force indexing destructor. */
    ~BruteForceIndexing();
    
    
    
    void setBodies(Array *bodies);
    
    Array *calculateCollisions(World *world, float dt);
    
    
    void addBody(Body *body);
    
    void removeBody(Body *body);
    
    void removeAllBodies();
    
    
    Array *bodies();
    
    unsigned int numberOfBodies();
    
    Arbiter *collisionForBodies(Body *a, Body *b);
    
    Array *arbiters(bool includeIngnored = true);
    
    
    Array *bodiesInCircularArea(Vector2 center, float radius);
    
    Array *bodiesInRectanglarArea(Rect rect);
    
    Body *closestBodyToPoint(Vector2 point);
    
private:
    Array *_bodies;
    
    typedef uintptr_t ArbiterKey;
    std::unordered_map<ArbiterKey, Arbiter *> _arbiters;
    
    Array *_collisions;
};



#endif
