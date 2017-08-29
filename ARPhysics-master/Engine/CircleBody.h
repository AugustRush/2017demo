//
//  CircleBody.h
//  Drawing
//
//  Created by Adrian Russell on 10/9/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __CircleBody_H__
#define __CircleBody_H__

#include "Body.h"

class CircleBody : public Body
{
public:
    
    /*!
     @param radius   ...
     @param position ...
     @param mass     ...
     */
    CircleBody(float radius, Vector2 position, float mass);
    
    //Rect boundingBox();
    
    float area();
    
    float radius() { return this->_radius; };
    
    BodyType bodyType() { return BodyTypeCircle; }
    
    bool intersectsRay(const Vector2& a, const Vector2& b);
    
    bool intersectsRay(const Vector2& ray);
    
    bool containsPoint(const Vector2& point);
    
protected:
    float _radius;
    
    Rect recalculateAABB();
};

#endif
