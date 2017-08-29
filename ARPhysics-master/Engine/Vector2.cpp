//
//  Vector2.cpp
//
//  Created by Adrian Russell on 9/18/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Vector2.h"
#include <math.h>

const Vector2 Vector2::Vector2Zero = Vector2(0.0, 0.0);

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2 Vector2::operator+= (Vector2 v)
{
    this->x += v.x;
    this->y += v.y;
    return *this;
}


Vector2 Vector2::operator-= (Vector2 v)
{
    this->x -= v.x;
    this->y -= v.y;
    return *this;
}


Vector2 Vector2::operator*= (float s)
{
    this->x *= s;
    this->y *= s;
    return *this;
}

Vector2 Vector2::operator/= (float s)
{
    this->x /= s;
    this->y /= s;
    return *this;
}


const Vector2 Vector2::operator+ (Vector2 v) const
{
    return Vector2(this->x + v.x, this->y + v.y);
}

const Vector2 Vector2::operator- (Vector2 v) const
{
    return Vector2(this->x - v.x, this->y - v.y);
}

const Vector2 Vector2::operator* (float s) const
{
    return Vector2(*this) *= s;
}


const Vector2 Vector2::operator* (Matrix22 m) const
{
    return Vector2(x * m.m11 + y * m.m12, x * m.m21 + y * m.m22);
}



const Vector2 Vector2::operator/ (float s) const
{
    return Vector2(*this) /= s;
}

const Vector2 Vector2::operator- () const
{
    return Vector2(*this) * -1.0;
}

const bool Vector2::operator== (Vector2 &v) const
{
    return ((x == v.x) && (y == v.y));
}

const bool Vector2::operator!= (Vector2 &v) const
{
    return !((x == v.x) && (y == v.y));
}

const Vector2 Vector2::transform(float angle) const
{
    double cs = cos(angle);
    double sn = sin(angle);
    //cs = rounddp(cs, 5);
    //sn = rounddp(sn, 5);
    double px = x * cs - y * sn;
    double py = x * sn + y * cs;
    
    return Vector2(px, py);
}

const Vector2 Vector2::normalise() const
{
    return (this->x == 0.0f && this->y == 0.0f) ? Vector2() : (*this * (1.0 / this->length()));
}

const Vector2 Vector2::inverse() const
{
    return Vector2(-this->x, -this->y);
}

const float Vector2::squareMagnitude() const
{
    return (this->x * this->x) + (this->y * this->y);
}

const float Vector2::magnitude() const
{
    return sqrt(this->squareMagnitude());
}

const float Vector2::length() const
{
    return this->magnitude();
}


const Vector2 Vector2::perpendicular() const
{
    return Vector2(-y, x);
}

const Vector2 Vector2::reversePerpendicular() const
{
    return Vector2(y, -x);
}

// normalise!!
const Vector2 Vector2::relativeDirection() const
{
    return normalise();
};




