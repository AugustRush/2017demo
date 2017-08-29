//
//  Matrix22.cpp
//  Drawing
//
//  Created by Adrian Russell on 10/8/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Matrix22.h"
#include "Vector2.h"
#include <math.h>

Matrix22::Matrix22(float m11, float m12, float m21, float m22)
{
    this->m11 = m11;
    this->m12 = m12;
    this->m21 = m21;
    this->m22 = m22;
}

Matrix22& Matrix22::operator+= (const Matrix22 &m)
{
    this->m11 += m.m11;
    this->m12 += m.m12;
    this->m21 += m.m21;
    this->m22 += m.m22;
    return *this;
}


Matrix22& Matrix22::operator-= (const Matrix22 &m)
{
    this->m11 -= m.m11;
    this->m12 -= m.m12;
    this->m21 -= m.m21;
    this->m22 -= m.m22;
    return *this;
}

Matrix22& Matrix22::operator*= (const Matrix22 &m)
{
    this->m11 = ((this->m11 * m.m11) + (this->m12 * m.m21));
    this->m12 = ((this->m11 * m.m12) + (this->m12 * m.m22));
    this->m21 = ((this->m21 * m.m11) + (this->m22 * m.m21));
    this->m22 = ((this->m21 * m.m12) + (this->m22 * m.m22));
    return *this;
}

Matrix22& Matrix22::operator/= (const Matrix22 &m)
{
    Matrix22 im = Matrix22(*this).inverse();
    this->m11 = ((this->m11 * im.m11) + (this->m12 * im.m21));
    this->m12 = ((this->m11 * im.m12) + (this->m12 * im.m22));
    this->m21 = ((this->m21 * im.m11) + (this->m22 * im.m21));
    this->m22 = ((this->m21 * im.m12) + (this->m22 * im.m22));
    return *this;
}

Matrix22& Matrix22::operator*= (const float s)
{
    this->m11 *= s;
    this->m12 *= s;
    this->m21 *= s;
    this->m22 *= s;
    return *this;
}


Matrix22& Matrix22::operator/= (const float s)
{
    this->m11 /= s;
    this->m12 /= s;
    this->m21 /= s;
    this->m22 /= s;
    return *this;
}


const Matrix22 Matrix22::operator+ (const Matrix22 &m)
{
    return Matrix22(*this) += m;
}

const Matrix22 Matrix22::operator- (const Matrix22 &m)
{
    return Matrix22(*this) -= m;
}

const Matrix22 Matrix22::operator* (const Matrix22 &m)
{
    return Matrix22(*this) *= m;
}

const Matrix22 Matrix22::operator/ (const Matrix22 &m)
{
    return Matrix22(*this) /= m;
}

const Matrix22 Matrix22::operator* (const float s)
{
    return Matrix22(*this) *= s;
}

const Matrix22 Matrix22::operator/ (const float s)
{
    return Matrix22(*this) /= s;
}



Vector2 Matrix22::operator* (Vector2 v) const
{
    return Vector2( m11 * v.x + m12 * v.y, m21 * v.x + m22 * v.y );
}




const bool Matrix22::operator== (const Matrix22 &m)
{
    return ((m11 == m.m11) && (m12 == m.m12) && (m21 == m.m21) && (m22 == m.m22));
}

const bool Matrix22::operator!= (const Matrix22 &m)
{
    return ((m11 != m.m11) || (m12 != m.m12) || (m21 != m.m21) || (m22 != m.m22));
}



const Matrix22 Matrix22::inverse()
{
    return Matrix22((1.0 / this->m11), (1.0 / this->m12), (1.0 / this->m21), (1.0 / this->m22));
}

const Matrix22 Matrix22::transpose()
{
    return Matrix22(m11, m21, m12, m22);
}

const Matrix22 Matrix22::scaleMatrix(float sx, float sy)
{
    return Matrix22(sx, 0, 0, sy);
}

const Matrix22 Matrix22::rotationMatrix(float angle)
{
    float c = cos(angle);
    float s = sin(angle);
    return Matrix22(c,-s,s,c);
}

