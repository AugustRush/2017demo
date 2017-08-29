//
//  Arbiter.h
//
//  Created by Adrian Russell on 31/12/2013.
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

#ifndef __ARPhysics__Arbiter_H_
#define __ARPhysics__Arbiter_H_

#include "Vector2.h"
#include "Object.h"
#include "Body.h"

#define MAX_CONTACT_COUNT 2

/*! An Arbiter represents the state of a collision between two bodies. */
class Arbiter : public Object {
public:
    
    /*! The maximum number of contact points that an arbiter can support at a time. */
    inline static const unsigned int maxContactCount() { return MAX_CONTACT_COUNT; }
    
    typedef enum {
        ArbiterStateNoCollision,
        ArbiterStateFirstContact,
        ArbiterStateIgnoring,
        ArbiterStateContact,
        ArbiterStateSeparated,
    } ArbiterState;
    
    ArbiterState state;
    
    /*! Constructs a new arbiter using the two specified bodies.
     @param a
            The first body.
     @param b
            The second body.
     */
    Arbiter(Body *a, Body *b);
    
    
    /*! Returns the first body.
     @return The first body.
     */
    Body *bodyA() { return _bodyA; }
    
    /*! Returns the second body.
     @return The second body.
     */
    Body *bodyB() { return _bodyB; }
    
    
    /*! Calulates and applies the relative impulses to both objects to push them apart. */
    void applyImpulse(void);
    
    /*! Apply a naive form of position correction to the bodies to move them apart and stop them penerating each other. */
    void positionalCorrection(void);
    
    
    
    
    float penetration;                      // Depth of penetration from collision
    Vector2 normal;                         // From A to B
    Vector2 contacts[MAX_CONTACT_COUNT];    // Points of contact during collision
    unsigned int contact_count;             // Number of contacts that occured during collision
    
    unsigned int increaseStepCount();

protected:
    float _e;       // mixed restitution
    float _df;      // mixed dynamic friction
    float _sf;      // mixed static friction
    Body *_bodyA;   // The first body
    Body *_bodyB;   // The second body
    
    unsigned int _stepsSinceSeperation;
};

#endif
