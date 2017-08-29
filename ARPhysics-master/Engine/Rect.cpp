//
//  Rect.cpp
//
//  Created by Adrian Russell on 9/18/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Rect.h"


Rect::Rect(float x, float y, float w, float h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}


Rect::Rect(Vector2 origin, float w, float h)
{
    this->x = origin.x;
    this->y = origin.y;
    this->w = w;
    this->h = h;
}


bool Rect::contains(Vector2 v)
{
    return this->contains(v.x, v.y);
}


bool Rect::contains(float x, float y)
{
    return ((this->x <= x && this->right() >= x) && (this->y <= y && this->top() >= y));
}

Vector2 Rect::center()
{
    return Vector2(this->x + (this->w / 2.0), this->y + (this->h / 2.0));
}


float Rect::area()
{
    return (this->w * this->h);
}

const Rect Rect::standardise()
{
    double width  = this->w;
    double height = this->h;
    
    Rect standardized = Rect(*this);
    
    if (width < 0.0) {
        standardized.x += width;
        standardized.w = -width;
    }
    
    if (height < 0.0) {
        standardized.y += height;
        standardized.h = -height;
    }
    
    return standardized;
}

Rect Rect::intersectionRect(Rect r1, Rect r2)
{
    Rect rect = Rect();
    
    /* If both of them are empty we can return r2 as an empty rect,
     so this covers all cases: */
    if (r1.isEmpty())
        return r2;
    else if (r2.isEmpty())
        return r1;
    
    r1 = r1.standardise();
    r2 = r2.standardise();
    
    if (r1.x + r1.w <= r2.x ||
        r2.x + r2.w <= r1.x ||
        r1.y + r1.h <= r2.y ||
        r2.y + r2.h <= r1.y)
        return Rect();
    
    rect.x = (r1.x > r2.x ? r1.x : r2.x);
    rect.y = (r1.y > r2.y ? r1.y : r2.y);
    
    if (r1.x + r1.w < r2.x + r2.w)
        rect.w = r1.x + r1.w - rect.x;
    else
        rect.w = r2.x + r2.w - rect.x;
    
    if (r1.y + r1.h < r2.y + r2.h)
        rect.h = r1.y + r1.h - rect.y;
    else
        rect.h = r2.y + r2.h - rect.y;
    
    return rect;
}

bool Rect::intersect(Rect r1, Rect r2)
{
    r1 = r1.standardise();
    r2 = r2.standardise();
    return (r1.left() < r2.right() && r1.right() > r2.left() && r1.bottom() < r2.top() && r1.top() > r2.bottom());
}


//static float intersectionDepth(const Rect &r1, const Rect &r2)
//{
//    
//}
//
//static float distance(const Rect &r1, const Rect &r2)
//{
//    
//}

bool Rect::isEmpty()
{
    return (this->w == 0 || this->h == 0);
}

bool Rect::operator== (const Rect r2)
{
    return (this->x == r2.x && this->y == r2.y && this->w == r2.w && this->h == r2.h);
}

bool Rect::operator!= (const Rect r2)
{
    return !(this->x == r2.x && this->y == r2.y && this->w == r2.w && this->h == r2.h);
}

