//
//  Constraint.h
//
//  Created by Adrian Russell on 10/17/13.
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

#ifndef __ARPhysics__Constraint_H__
#define __ARPhysics__Constraint_H__

#include "Body.h"

/*! The constraint class is an abstract class that all constaint objects must subclass. */
class Constraint : public Object {
public:
    
    /*!
     Initialises a Cnostriant with two specified bodies.
     @param a
            The first body.
     @param b
            The second body.
     */
    Constraint(Body *a, Body *b)
    {
        a->retain();
        this->a = a;
        b->retain();
        this->b = b;
    };
    
    /*! constraint destructor. */
    ~Constraint()
    {
        a->release();
        b->release();
    }
    
    /*! Solve the constraint.
     @param dt
     The delta time to solve the constaint for.
     */
    virtual void solve(float dt) = 0;
    
    /*!
     Returns the first body.
     @return The first body.
     */
    Body *getA() { return a; }
    
    /*!
     Returns the second body.
     @return The second body.
     */
    Body *getB() { return b; }
    
protected:
    Body *a;
    Body *b;
};



#endif
