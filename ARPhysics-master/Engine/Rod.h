//
//  Rod.h
//  Drawing
//
//  Created by Adrian Russell on 09/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__Rod__
#define __Drawing__Rod__

#include "Constraint.h"


class Rod : public Constraint
{
public:
    
    /*!
     Constructs a new spring that attaches two bodies.
     @param a
            The first body.
     @param b
            The second body.
     @param length
            The length of the rod.
     */
    Rod(Body *a, Body *b, float length);
    
    
    /*! Rod destructor. */
    ~Rod();
    
    /*! Solve the constraint.
     @param dt
            The delta time to solve the constaint for.
     */
    void solve(float dt);
    
    
    
    
    
private:
    float _length;        //
};

#endif /* defined(__Drawing__Rod__) */
