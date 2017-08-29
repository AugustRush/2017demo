//
//  Drawing.h
//
//  Created by Adrian Russell on 17/02/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//
//  THIS DRAWING IS BASED ON THE DRAWING FROM THE CHIPMUNK PHYSICS ENGINE BY SCOTT LEMBCKE (his copyright below)

/* Copyright (c) 2007 Scott Lembcke
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef binary_tests_Drawing_h
#define binary_tests_Drawing_h

#include "Types.h"
#include "Vector2.h"
#include "Rect.h"


class PolygonBody;
class CircleBody;

typedef struct Color {
	float r, g, b, a;
} Color;

static const Color kNoColor     = (Color){ 0.0, 0.0, 0.0, 0.0 };
static const Color kGrayColor   = (Color){ 0.5, 0.5, 0.5, 1.0 };
static const Color kBlackColor  = (Color){ 0.0, 0.0, 0.0, 1.0 };
static const Color kWhiteColor  = (Color){ 1.0, 1.0, 1.0, 1.0 };
static const Color kGreenColor  = (Color){ 0.0, 1.0, 0.0, 1.0 };
static const Color kRedColor    = (Color){ 1.0, 0.0, 0.0, 1.0 };
static const Color kBlueColor   = (Color){ 0.0, 0.0, 1.0, 1.0 };
static const Color kYellowColor = (Color){ 1.0, 1.0, 0.0, 1.0 };

Color randomColor();


void drawString(int x, int y, const char *str);

void drawCircle(Vector2 center, float radius, float rotation, Color fillColor, Color strokeColor);

void drawPolygon(const Vector2* points, unsigned int pointCount, Vector2 center, float rotation, Color fillColor, Color strokeColor);

void drawLine(Vector2 a, Vector2 b, Color color);

void drawRect(Rect rect, float rotation, Color fillColor, Color strokeColor);


void drawPolygonBody(PolygonBody *polygon, Color fillColor, Color strokeColor, bool drawAABB = false, Color aabbColor = kBlueColor);
void drawCircleBody(CircleBody *circle, Color fillColor, Color strokeColor, bool drawAABB = true, Color aabbColor = kBlueColor);

#endif
