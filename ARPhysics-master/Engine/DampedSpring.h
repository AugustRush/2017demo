//
//  DampedSpring.h
//
//  Created by Adrian Russell on 10/18/13.
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

#ifndef __ARPhysics__DampedSpring_H__
#define __ARPhysics__DampedSpring_H__

#include "Constraint.h"


/*! A constraint that acts like a damped spring allowing a body to be attached to a static point or another body. */
class DampedSpring : public Constraint {
public:
    
    /*! The value to give as fail length if you do not want the damped spring to ever fail. */
    static const float DampedSpringDoNotFail;
    
    /*!
     Constructs a new damped spring that attaches two bodies.
     @param a
     The first body.
     @param b
     The second body.
     @param stiffness
     The stiffness of the spring.
     @param restLength
     The length at which the spring is at rest.
     @param failLength
     The length at which the spring should fail and call the fail callback.
     @discussion The spring can not remove itself when it fails; the specfied failCallBack must remove it.
     */
    DampedSpring(Body *a, Body *b, float stiffness, float restLength, float failLength = DampedSpringDoNotFail);
    
    /*! Damped Spring Desctructor. */
    ~DampedSpring();
    
    void solve(float dt);
    
    void setCallBack(std::function<void(DampedSpring *)> failCallBack);
    
private:
    float stiffness;
    float restLength;
    float failLength;
    
    std::function<void(DampedSpring *)> failCallBack;
};

#endif
