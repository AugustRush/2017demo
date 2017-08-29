//
//  Spring.h
//
//  Created by Adrian Russell on 25/03/2014.
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

#ifndef __ARPhysics__Spring_H__
#define __ARPhysics__Spring_H__

#include "Constraint.h"

/*! A constraint that acts like a spring allowing a body to be attached to a static point or another body. */
class Spring : public Constraint {
public:
    
    /*! The value to give as fail length if you do not want to spring to ever fail. */
    static const float SpringDoNotFail;
    
    /*!
     Constructs a new spring that attaches two bodies.
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
    Spring(Body *a, Body *b, float stiffness, float restLength, float failLength = SpringDoNotFail);
    
    
    /*! Spring destructor. */
    ~Spring();
    
    /*! Solve the constraint.
     @param dt
            The delta time to solve the constaint for.
     */
    void solve(float dt);
    
    /*! Set the function to be called in the event that the spring extends past the fail length.
     @param failCallBack
            The function to call if/when the spring extends past the fail length.
     */
    void setCallBack(std::function<void(Spring *)> failCallBack);
    
private:
    float    stiffness;
    float    restLength;
    float    failLength;
    
    std::function<void(Spring *)> failCallBack;
};

#endif
