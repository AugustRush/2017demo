//
//  types.h
//
//  Created by Adrian Russell on 9/18/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __types_h__
#define __types_h__

#include <tgmath.h>
#include <float.h>
#include <stdbool.h>


#define EPSILON 0.0001f

#ifndef INFINITY
#define INFINITY (1e1000)
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

#ifndef M_E
#define M_E 2.71828182845904523536028747135266250
#endif


#ifndef MIN
#define MIN(a, b) ((a < b) ? a : b)
#endif

#ifndef MAX
#define MAX(a, b) ((a > b) ? a : b)
#endif

template <class T>
inline T clamp(T min, T max, T a)
{
    return MIN(MAX(a, min), max);
}


/// Clamp f to be between 0 and 1.
inline float clamp01(float f)
{
	return MAX(0.0f, MIN(f, 1.0f));
}

inline float deg2rad(float d)
{
    return (d * (M_PI / 180.0));
}

inline float rad2deg(float r)
{
    return (r * (180.0 / M_PI));
}

// Comparison with tolerance of EPSILON
inline bool equal(float a, float b)
{
    // <= instead of < for NaN comparison safety
    return std::abs( a - b ) <= EPSILON;
}

/*! Squares an input value */
template <class T>
inline T sqr(T value) {
    return (value * value);
}

inline int round(float a)
{
    return (int)(a + 0.5f);
}

inline const float randomInRange(float l, float h)
{
    float a = ((float)rand()) / RAND_MAX;
    a = (h - l) * a + l;
    return a;
}

#endif
