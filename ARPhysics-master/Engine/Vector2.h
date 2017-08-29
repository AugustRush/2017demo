//
//  Vector2.h
//
//  Created by Adrian Russell on 9/18/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __Vector2_H__
#define __Vector2_H__

#include "types.h"
#include "Matrix22.h"

/** A vector in 2 dimensions. {x, y} */
struct Vector2 final {
    //
    
public:

    Vector2(float x = 0, float y = 0);
    
    
    static const Vector2 Vector2Zero;
    
    
    
    
    Vector2 operator+= (Vector2 v);
    Vector2 operator-= (Vector2 v);
    Vector2 operator*= (float s);
    Vector2 operator/= (float s);
    
    
    const Vector2 operator+ (Vector2 v) const;
    const Vector2 operator- (Vector2 v) const;
    const Vector2 operator* (float s) const;
    const Vector2 operator/ (float s) const;
    
    const Vector2 operator* (Matrix22 m) const;
    
    const Vector2 operator- () const;
    
    const bool operator== (Vector2 &v) const;
    const bool operator!= (Vector2 &v) const;
    
    const Vector2 transform(float angle) const;
    
    const Vector2 normalise() const;
    
    const Vector2 inverse() const;
    
    const float squareMagnitude() const;
    const float magnitude() const;
    
    const float length() const;
    
    // perpenduclar (90deg rotation)
    const Vector2 perpendicular() const;
    
    // perpendcular (-90 deg rotation)
    const Vector2 reversePerpendicular() const;
    
    const Vector2 relativeDirection() const;
    
    
    //-----------------
    
    inline static const Vector2 vectorWithMagnitudeRotation(float magnitude, float angle)
    {
        float x = cos(angle) * magnitude;
        float y = sin(angle) * magnitude;
        return Vector2(x, y);
    }
    
    inline static const float distance(const Vector2 &v1, const Vector2 &v2)
    {
        float distx = (v2.x - v1.x);
        float disty = (v2.y - v1.y);
        return std::sqrt( (distx * distx) + (disty * disty) );
    }
    
    inline static const bool parallel(Vector2 &v1, Vector2 &v2)
    {
        return (dotProduct(v1.perpendicular(), v2) == 0.0);
    }
    
    
    
    inline static const float dotProduct(const Vector2 &v1, const Vector2 &v2)
    {
        return (v1.x * v2.x) + (v1.y * v2.y);
    }
    
    
    inline static const float squareDistance( const Vector2& a, const Vector2& b )
    {
        Vector2 c = a - b;
        return dotProduct( c, c );
    }
    
    inline float const squareLength() const
    {
        return sqr(x) + sqr(y);
    }
    
    
    float x, y;
    
};

inline Vector2 operator*( float s, const Vector2& v )
{
    return Vector2( s * v.x, s * v.y );
}


#endif /* defined(__Vector2_H__) */
