//
//  Collision.h
//
//  Created by Adrian Russell on 10/15/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __ARPhysics__Collision_H__
#define __ARPhysics__Collision_H__

#include "CircleBody.h"
#include "PolygonBody.h"
#include "PolygonPath.h"
#include "Arbiter.h"







bool circleVSbodyIntersection(Vector2 aPosition, float aRadius, Body *body);
bool circleVScircleIntersection(Vector2 aPosition, float aRadius, Vector2 bPosition, float bRadius);
bool circleVSpolygonIntersection(Vector2 aPosition, float aRadius, const std::vector<Vector2>& bVertices, Vector2 bPosition, float bRotation);

bool rectVSbodyIntersection(Rect aRect, Body *body);
bool rectVScircleIntersection(Rect aRect, Vector2 bPosition, float bRadius);
bool rectVSpolygonIntersection(Rect aRect, const std::vector<Vector2>& bVertices, Vector2 bPosition, float bRotation);

/*!
 Tests for collision between two specified bodies & applies the information about the collision to a supplied Arbiter object.
 @param a
 The first body to check.
 @param b
 The second body to check.
 @param arbiter
 The arbiter to use for the collision.
 */
void collideBodies(Body *a, Body *b, Arbiter *arbiter);

/*!
 Tests for collision between two circles & applies the information about the collision to a supplied Arbiter object.
 @param aPosition
        ...
 @param aRadius
        ...
 @param bPosition
        ...
 @param bRadius
        ...
 @param arbiter
        ...
 @return
 */
void circleVScircle(Vector2 aPosition, float aRadius, Vector2 bPosition, float bRadius, Arbiter *arbiter);


/*!
 Tests for collision between two specified circular bodies & applies the information about the collision to a supplied Arbiter object.
 @param a
        The first circular body to check.
 @param b
        The second circular body to check.
 @param arbiter
        The arbiter to use for the collision.
 */
void circleVScircle(CircleBody *a, CircleBody *b, Arbiter *arbiter);

/*!
 Tests for collision between a circular body and a polygon body & applies the information about the collision to a supplied Arbiter object.
 @param a
 The circular body to check.
 @param b
 The polygon body to check.
 @param arbiter
 The arbiter to use for the collision.
 */
void circleVSpolygon(CircleBody *a, PolygonBody *b, Arbiter *arbiter);


/*!
 Tests for collision between two specified polygon bodies & applies the information about the collision to a supplied Arbiter object.
 @param a
 The first polygon body to check.
 @param b
 The second polygon body to check.
 @param arbiter
 The arbiter to use for the collision.
 */
void polygonVSpolygon(PolygonBody *a, PolygonBody *b, Arbiter *arbiter);

//------------------------------------------//

/*! 
 Calculates the gradient of the line made by two specified points.
 @param a1
        The first point of the line.
 @param a2
        A second point on the line.
 @return The gradient of the line formed.
 @discussion **warning** This function is not safe to use with vertical lines.
 */
float gradient(Vector2 a1, Vector2 a2);

/*!
 Checks whether two lines intersects and if so supplies the point of intersection.
 @param a1
        The first point on the first line.
 @param a2
        The second point on the first line.
 @param b1
        The first point on the second line.
 @param b2
        The second point on the second line.
 @param intersection
        A pointer to a Vector2 to add the place at which the lines intersected if they do.
 @param limitBetweenLineEnds
        Whether to limit the lines to to between the specified points to to extend to infinity. Deault is to limit them.
 @return A bool indicating whether, or not, the lines intersect.
 */
bool intersectionOfLines(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2, Vector2 *intersection, bool limitBetweenLineEnds = true);

/*!
 Checks whether a line & a circle intersects and returns the number of points of intersection. The points of intersection are also returned.
 @param a1
        The first point on the line.
 @param a2
        The second point on the line.
 @param bCenter
        The center point of the circle.
 @param bRadius
        The radius of the circle.
 @param intersections
        A pointer to a 2 length array of Vector2 objects as a place to add the points of intersection.
 @return The number of points at which the line intersects the circle. This value wsill be between 0 and 2.
 */
unsigned int intersectionOfLineAndCircle(Vector2 a1, Vector2 a2, Vector2 bCenter, float bRadius, Vector2 intersections[2]);

#endif
