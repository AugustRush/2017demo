//
//  Rect.h
//
//  Created by Adrian Russell on 9/18/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __Rect_H__
#define __Rect_H__

#include "Vector2.h"

struct Rect {
    //
    
public:
    
    Rect(float x = 0, float y = 0, float w = 0, float h = 0);
    Rect(Vector2 origin, float w = 0, float h = 0);
    ~Rect() {};
    
    inline float left()   const { return x; }
    inline float right()  const { return x + w; }
    inline float top()    const { return y + h; }
    inline float bottom() const { return y; }
    
    inline Vector2 topLeft()     const { return Vector2(left(),  top()); }
    inline Vector2 topRight()    const { return Vector2(right(), top()); }
    inline Vector2 bottomLeft()  const { return Vector2(left(),  bottom()); }
    inline Vector2 bottomRight() const { return Vector2(right(), bottom()); }
    
    inline float width() const  { return w; }
    inline float height() const { return h; }
    
    bool contains(Vector2 v);
    bool contains(float x, float y);
    
    Vector2 center();
    
    inline Vector2 origin() { return Vector2(x, y); }
    inline float width()  { return w; }
    inline float height() { return h; }
    
    float area();
    
    const Rect standardise();
    
    static Rect intersectionRect(Rect r1, Rect r2);
    
    static bool intersect(Rect r1, Rect r2);
    
    bool isEmpty();
    
    bool operator== (const Rect r2);
    bool operator!= (const Rect r2);
    
protected:
    float x, y, w, h;
};

#endif /* defined(__Drawing__Rect__) */
