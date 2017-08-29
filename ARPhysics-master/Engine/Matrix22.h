//
//  Matrix22.h
//
//  Created by Adrian Russell on 10/8/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __ARPhysics_Matrix22_H__
#define __ARPhysics_Matrix22_H__

#include "types.h"


struct Vector2;

struct Matrix22 final {
    
public:
    
    Matrix22(float m11 = 0, float m12 = 0, float m21 = 0, float m22 = 0);
    
    
    static const Matrix22 indentityMatrix();
 
    Matrix22& operator+= (const Matrix22 &m);
    Matrix22& operator-= (const Matrix22 &m);
    Matrix22& operator*= (const Matrix22 &m);
    Matrix22& operator/= (const Matrix22 &m);
    Matrix22& operator*= (const float s);
    Matrix22& operator/= (const float s);
    
    
    
    const Matrix22 operator+ (const Matrix22 &m);
    const Matrix22 operator- (const Matrix22 &m);
    const Matrix22 operator* (const Matrix22 &m);
    const Matrix22 operator/ (const Matrix22 &m);
    const Matrix22 operator* (const float s);
    const Matrix22 operator/ (const float s);
    
    const bool operator== (const Matrix22 &m);
    
    const bool operator!= (const Matrix22 &m);
    
    const Matrix22 transpose();
    
    const Matrix22 inverse();
    
    
    
    /*!
     @param sx
            ...
     @param sy
            ...
     @return ...
     */
    static const Matrix22 scaleMatrix(float sx, float sy);
    
    /*!
     @param angle
            ...
     @return ...
     */
    static const Matrix22 rotationMatrix(float angle);
    
    Vector2 operator* (Vector2 v) const;
    
    
    
   
    
    
    
public:
    float m11, m12, m21, m22;
};

#endif
