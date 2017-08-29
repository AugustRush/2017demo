//
//  CircleBody.cpp
//  Drawing
//
//  Created by Adrian Russell on 10/9/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "CircleBody.h"
#include "Shape_Utilities.h"
#include "Collision.h"

CircleBody::CircleBody(float radius, Vector2 position, float mass) : Body(position, mass)
{
    _radius     = radius;
    _inertia    = _mass * radius * radius;
    _invInertia = (_inertia) ? 1.0f / _inertia : 0.0f;
    _AABB       = recalculateAABB();
}

bool CircleBody::intersectsRay(const Vector2& a, const Vector2& b)
{
    return (intersectionOfLineAndCircle(a, b, _position, _radius, NULL) > 0);
}

bool CircleBody::intersectsRay(const Vector2& ray)
{
    return false;
}

bool CircleBody::containsPoint(const Vector2& point)
{
    return pointInCircle(_position, _radius, point);
}

Rect CircleBody::recalculateAABB()
{
    return Rect(_position.x - _radius, _position.y - _radius, _radius * 2, _radius * 2);
}