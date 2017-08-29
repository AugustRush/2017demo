//
//  ForceGenerator.h
//
//  Created by Adrian Russell on 10/9/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __ForceGenerator_H__
#define __ForceGenerator_H__

#include "Object.h"
#include "Body.h"
#include "Array.h"


/*! The force generator class is an abstract class that all concreate force generator classes must inherit from.
 Force generators are used for apply an impulse to all or a set of bodies during each step. 
 These forces are useful for creating gravity, explosions or anything else you can thins of.
 */
class ForceGenerator : public Object {
public:
    
    /*! The constructor for ForceGenerators. All subclass constructors should call this one. */
    ForceGenerator() : Object() {};
    
    /*!
     Checks and returns whether, or not, the force generator should be applied to the specified body. 
     If true then applyToBody(Body*, float) is called with the specified object.
     @param b
            The body to check.
     @return A bool indicating if the force generator should be applied to the body.
     */
    virtual bool shouldApplyToBody(Body *b) = 0;
    
    
    /*!
     Applies an impulse from the force generator to the specified body for the specified time period.
     @param b
            The body to apply the impulse to.
     @param d
            The timestep to use.
     */
    virtual void applyToBody(Body *b, float dt) = 0;
};

#endif
