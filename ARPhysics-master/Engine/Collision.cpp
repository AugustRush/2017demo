//
//  Collision.cpp
//
//  Created by Adrian Russell on 10/15/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Collision.h"
#include "Matrix22.h"


bool rectVSbodyIntersection(Rect aRect, Body *body)
{
    if (body->bodyType() == Body::BodyTypeCircle) {
        CircleBody *circle = (CircleBody *)body;
        return rectVScircleIntersection(aRect, circle->position(), circle->radius());
    } else if (body->bodyType() == Body::BodyTypePolygon) {
        PolygonBody *poly = (PolygonBody *)body;
        return rectVSpolygonIntersection(aRect, poly->vertices(), poly->position(), poly->rotation());
    }
    return false;
}

bool circleVSbodyIntersection(Vector2 aPosition, float aRadius, Body *body)
{
    if (body->bodyType() == Body::BodyTypeCircle) {
        CircleBody *circle = (CircleBody *)body;
        return circleVScircleIntersection(aPosition, aRadius, circle->position(), circle->radius());
    } else if (body->bodyType() == Body::BodyTypePolygon) {
        PolygonBody *poly = (PolygonBody *)body;
        return circleVSpolygonIntersection(aPosition, aRadius, poly->vertices(), poly->position(), poly->rotation());
    }
    return false;
}


bool circleVScircleIntersection(Vector2 aPosition, float aRadius, Vector2 bPosition, float bRadius)
{
    Vector2 normal = bPosition - aPosition;
    float distance = normal.length();
    float radius = aRadius + bRadius;
    return (distance < radius);
}


bool rectVScircleIntersection(Rect aRect, Vector2 bPosition, float bRadius)
{
    float closestX = (bPosition.x < aRect.left() ? aRect.left() : (bPosition.x > aRect.right()  ? aRect.right()  : bPosition.x));
    float closestY = (bPosition.y < aRect.top()  ? aRect.top()  : (bPosition.y > aRect.bottom() ? aRect.bottom() : bPosition.y));
    float dx = closestX - bPosition.x;
    float dy = closestY - bPosition.y;
    
    return ( sqr(dx) + sqr(dy) ) <= sqr(bRadius);
}

bool circleVSpolygonIntersection(Vector2 aPosition, float aRadius, const std::vector<Vector2>& bVertices, Vector2 bPosition, float bRotation)
{
    unsigned int size = (unsigned int) bVertices.size();
    for (unsigned int i = 0; i < size; i++) {
        unsigned int j = (i+1) % size;
        
        Vector2 vI = bVertices[i];
        vI = vI.transform(bRotation) + bPosition;
        
        Vector2 vJ = bVertices[j];
        vJ = vJ.transform(bRotation) + bPosition;
     
        unsigned int intersection = intersectionOfLineAndCircle(vI, vJ, aPosition, aRadius, nullptr);
        if (intersection > 0) {
            return true;
        }
    }
    return false;
}

bool rectVSpolygonIntersection(Rect aRect, const std::vector<Vector2>& bVertices, Vector2 bPosition, float bRotation)
{
    Vector2 rectVertices[4] = { aRect.topLeft(), aRect.topRight(), aRect.bottomRight(), aRect.bottomLeft() };
    
    unsigned int size = (unsigned int) bVertices.size();
    for (unsigned int i = 0; i < size; i++) {
        unsigned int j = (i+1) % size;
        
        Vector2 vI = bVertices[i];
        vI = vI.transform(bRotation) + bPosition;
        
        Vector2 vJ = bVertices[j];
        vJ = vJ.transform(bRotation) + bPosition;
        
        for (unsigned int k = 0; k < 4; k++) {
            unsigned int l = (k+1) % 4;
            
            bool intersects = intersectionOfLines(vI, vJ, rectVertices[k], rectVertices[l], nullptr);
            if (intersects) {
                return true;
            }
        }
    }
    return false;
}



//-----------------------------------------------------------------------------------------------------------//

void circleVScircle(CircleBody *a, CircleBody *b, Arbiter *arbiter)
{
    circleVScircle(a->position(), a->radius(), b->position(), b->radius(), arbiter);
}

void circleVScircle(Vector2 aPosition, float aRadius, Vector2 bPosition, float bRadius, Arbiter *arbiter)
{
    // caculate vector between the two bodies
    Vector2 normal = bPosition - aPosition;
    
    float distance = normal.length();
    float radius = aRadius + bRadius;
    
    // check if the distance from body centres is greater than sum of radii.
    if (distance < radius) {
        // calculate contact
        arbiter->contact_count = 1;
        arbiter->penetration = radius - distance;
        arbiter->normal = normal.normalise();
        arbiter->contacts[0] = arbiter->normal * aRadius + aPosition;
    } else {
        // no contact
        arbiter->contact_count = 0;
    }
}





//-----------------------------------------------------------------------------------------------------------//
#pragma mark -


void circleVSpolygon(CircleBody *a, PolygonBody *b, Arbiter *arbiter)
{
    CircleBody *A  = reinterpret_cast<CircleBody *>(a);
    PolygonBody *B = reinterpret_cast<PolygonBody *>(b);
    Arbiter *m = arbiter;
    
    m->contact_count = 0;
    
    // Transform circle center to Polygon model space
    Vector2 center = b->rotationMatrix().transpose() * (a->position() - b->position());
    
    // Find edge with minimum penetration
    // Exact concept as using support points in Polygon vs Polygon
    float separation = -FLT_MAX;
    unsigned int faceNormal = 0;
    for (unsigned int i = 0; i < B->vertexCount(); i++) {
        float s = Vector2::dotProduct( B->normals()[i], center - B->vertices()[i] );
        
        if(s > A->radius()) {
            arbiter->contact_count = 0;
            return;
        }
        
        if(s > separation) {
            separation = s;
            faceNormal = i;
        }
    }
    
    // Grab face's vertices
    Vector2 v1 = B->vertices()[faceNormal];
    unsigned int i2 = faceNormal + 1 < B->vertexCount() ? faceNormal + 1 : 0;
    Vector2 v2 = B->vertices()[i2];
    
    // Check to see if center is within polygon
    if(separation < EPSILON) {
        m->contact_count = 1;
        m->normal = -(B->rotationMatrix() * B->normals()[faceNormal]);
        m->contacts[0] = m->normal * A->radius() + a->position();
        m->penetration = A->radius();
        return;
    }
    
    // Determine which voronoi region of the edge center of circle lies within
    float dot1 = Vector2::dotProduct( center - v1, v2 - v1 );
    float dot2 = Vector2::dotProduct( center - v2, v1 - v2 );
    m->penetration = A->radius() - separation;
    
    
    if(dot1 <= 0.0f) {  // Closest to v1
        
        if(Vector2::squareDistance( center, v1 ) > A->radius() * A->radius())
            return;
        
        m->contact_count = 1;
        Vector2 n = v1 - center;
        n = B->rotationMatrix()* n;
        n = n.normalise( );
        m->normal = n;
        v1 = B->rotationMatrix() * v1 + b->position();
        m->contacts[0] = v1;
    } else if (dot2 <= 0.0f) { // Closest to v2
        
        if(Vector2::squareDistance( center, v2 ) > A->radius() * A->radius())
            return;
        
        m->contact_count = 1;
        Vector2 n = v2 - center;
        v2 = B->rotationMatrix() * v2 + b->position();
        m->contacts[0] = v2;
        n = B->rotationMatrix() * n;
        n = n.normalise( );
        m->normal = n;
    } else {    // Closest to face
        Vector2 n = B->normals()[faceNormal];
        if(Vector2::dotProduct( center - v1, n ) > A->radius())
            return;
        
        n = B->rotationMatrix() * n;
        m->normal = -n;
        m->contacts[0] = m->normal * A->radius() + a->position();
        m->contact_count = 1;
    }
}


//-----------------------------------------------------------------------------------------------------------//
#pragma mark -



Vector2 GetSupport(PolygonBody *body, const Vector2& dir)
{
    float bestProjection = -FLT_MAX;
    Vector2 bestVertex;
    
    for (unsigned int i = 0; i < body->vertexCount(); ++i) {
        Vector2 v = body->vertices()[i];
        float projection = Vector2::dotProduct( v, dir );
        
        if(projection > bestProjection) {
            bestVertex = v;
            bestProjection = projection;
        }
    }
    
    return bestVertex;
}


float FindAxisLeastPenetration( unsigned int *faceIndex, PolygonBody *A, PolygonBody *B )
{
    float bestDistance = -FLT_MAX;
    unsigned int bestIndex;
    
    for(unsigned int i = 0; i < A->vertexCount(); ++i) {
        
        // Retrieve a face normal from A
        Vector2 n = A->normals()[i];
        Vector2 nw = A->rotationMatrix() * n;
        
        // Transform face normal into B's model space
        Matrix22 buT = B->rotationMatrix().transpose( );
        n = buT * nw;
        
        // Retrieve support point from B along -n
        Vector2 s = GetSupport(B, -n );
        
        // Retrieve vertex on face from A, transform into
        // B's model space
        Vector2 v = A->vertices()[i];
        v = A->rotationMatrix() * v + A->position();
        v -= B->position();
        v = buT * v;
        
        // Compute penetration distance (in B's model space)
        float d = Vector2::dotProduct( n, s - v );
        
        // Store greatest distance
        if(d > bestDistance) {
            bestDistance = d;
            bestIndex = i;
        }
    }
    
    *faceIndex = bestIndex;
    return bestDistance;
}

void FindIncidentFace( Vector2 *v, PolygonBody *RefPoly, PolygonBody *IncPoly, unsigned int referenceIndex )
{
    Vector2 referenceNormal = RefPoly->normals()[referenceIndex];
    
    // Calculate normal in incident's frame of reference
    referenceNormal = RefPoly->rotationMatrix() * referenceNormal; // To world space
    referenceNormal = IncPoly->rotationMatrix().transpose() * referenceNormal; // To incident's model space
    
    // Find most anti-normal face on incident polygon
    int incidentFace = 0;
    float minDot = FLT_MAX;
    for (unsigned int i = 0; i < IncPoly->vertexCount(); ++i) {
        
        float dot = Vector2::dotProduct( referenceNormal, IncPoly->normals()[i] );
        if (dot < minDot) {
            minDot = dot;
            incidentFace = i;
        }
    }
    
    // Assign face vertices for incidentFace
    v[0] = IncPoly->rotationMatrix() * IncPoly->vertices()[incidentFace] + IncPoly->position();
    incidentFace = incidentFace + 1 >= (int)IncPoly->vertexCount() ? 0 : incidentFace + 1;
    v[1] = IncPoly->rotationMatrix() * IncPoly->vertices()[incidentFace] + IncPoly->position();
}


void polygonVSpolygon(PolygonBody *a, PolygonBody *b, Arbiter *arbiter)
{
    PolygonBody *A = reinterpret_cast<PolygonBody *>(a);
    PolygonBody *B = reinterpret_cast<PolygonBody *>(b);
    Arbiter *m = arbiter;
    
    
    m->contact_count = 0;
    
    // Check for a separating axis with A's face planes
    unsigned int faceA;
    float penetrationA = FindAxisLeastPenetration( &faceA, A, B );
    if(penetrationA >= 0.0f)
        return;
    
    // Check for a separating axis with B's face planes
    unsigned int faceB;
    float penetrationB = FindAxisLeastPenetration( &faceB, B, A );
    if(penetrationB >= 0.0f)
        return;
    
    unsigned int referenceIndex;
    bool flip; // Always point from a to b
    
    PolygonBody *RefPoly; // Reference
    PolygonBody *IncPoly; // Incident
    
    // Determine which shape contains reference face
    if(penetrationA >= penetrationB) {
        RefPoly = A;
        IncPoly = B;
        referenceIndex = faceA;
        flip = false;
    } else {
        RefPoly = B;
        IncPoly = A;
        referenceIndex = faceB;
        flip = true;
    }
    
    // World space incident face
    Vector2 incidentFace[2];
    FindIncidentFace( incidentFace, RefPoly, IncPoly, referenceIndex );
    
    //        y
    //        ^  ->n       ^
    //      +---c ------posPlane--
    //  x < | i |\
    //      +---+ c-----negPlane--
    //             \       v
    //              r
    //
    //  r : reference face
    //  i : incident poly
    //  c : clipped point
    //  n : incident normal
    
    // Setup reference face vertices
    Vector2 v1 = RefPoly->vertices()[referenceIndex];
    referenceIndex = referenceIndex + 1 == RefPoly->vertexCount() ? 0 : referenceIndex + 1;
    Vector2 v2 = RefPoly->vertices()[referenceIndex];
    
    // Transform vertices to world space
    v1 = RefPoly->rotationMatrix() * v1 + RefPoly->position();
    v2 = RefPoly->rotationMatrix() * v2 + RefPoly->position();
    
    // Calculate reference face side normal in world space
    Vector2 sidePlaneNormal = (v2 - v1);
    sidePlaneNormal =  sidePlaneNormal.normalise();
    
    // Orthogonalize
    Vector2 refFaceNormal( sidePlaneNormal.y, -sidePlaneNormal.x );
    
    // ax + by = c
    // c is distance from origin
    float refC = Vector2::dotProduct( refFaceNormal, v1 );
    
    // Flip
    m->normal = flip ? -refFaceNormal : refFaceNormal;
    
    // Keep points behind reference face
    unsigned int cp = 0; // clipped points behind reference face
    float separation = Vector2::dotProduct( refFaceNormal, incidentFace[0] ) - refC;
    if(separation <= 0.0f) {
        m->contacts[cp] = incidentFace[0];
        m->penetration = -separation;
        cp++;
    } else {
        m->penetration = 0;
    }
        
    separation = Vector2::dotProduct( refFaceNormal, incidentFace[1] ) - refC;
    if(separation <= 0.0f) {
        
        m->contacts[cp] = incidentFace[1];
        
        m->penetration += -separation;
        cp++;
        
        // Average penetration
        m->penetration /= (float)cp;
    }
    
    m->contact_count = cp;
}

//-----------------------------------------------------------------------------------------------------------------------//
#pragma mark -

void collideBodies(Body *a, Body *b, Arbiter *arbiter)
{
    // if either body is NULL then return as not two things to collide
    if (!a || !b) return;
    
    
    switch (a->bodyType() + b->bodyType()) {
        case 0:
            return circleVScircle((CircleBody *)a, (CircleBody *)b, arbiter);
        case 1:
            return circleVSpolygon((CircleBody *)a, (PolygonBody *)b, arbiter);
        case 2:
            return polygonVSpolygon((PolygonBody *)a, (PolygonBody *)b, arbiter);
        default:
            return;
    }
}


//-----------------------------------------------------------------------------------------------------------------------//


float gradient(Vector2 a1, Vector2 a2)
{
    return (a2.y - a1.y) / (a2.x - a1.x);
}

bool intersectionOfLines(Vector2 a1, Vector2 a2, Vector2 b1, Vector2 b2, Vector2 *intersection, bool limitBetweenLineEnds)
{
    float xA = a1.y - a2.y;
    float yA = a2.x - a1.x;
    
    float xB = b1.y - b2.y;
    float yB = b2.x - b1.x;
    
    float cA = (a1.x * a2.y) - (a2.x * a1.y);
    float cB = (b1.x * b2.y) - (b2.x * b1.y);
    
    float determinant = (xA * yB) - (yA * xB);
    
    if (determinant == 0.0) {
        // the lines are parallel so no intersection is possible
        return false;
    }
    
    float x = -((cA * yB) - (yA * cB)) / determinant;
    float y = -((xA * cB) - (cA * xB)) / determinant;
    
    float largerX = MAX(MAX(a1.x, a2.x), MAX(b1.x, b2.x));
    float largerY = MAX(MAX(a1.y, a2.y), MAX(b1.y, b2.y));
    
    float smallerX = MIN(MIN(a1.x, a2.x), MIN(b1.x, b2.x));
    float smallerY = MIN(MIN(a1.y, a2.y), MIN(b1.y, b2.y));
    
    if (limitBetweenLineEnds && (largerX < x || largerY < y || smallerX > x || smallerY > y)) {
        // the point of intersection is not on either of the lines
        return false;
    }
    
    *intersection = Vector2(x, y);
    return true;
}


unsigned int intersectionOfLineAndCircle(Vector2 a1, Vector2 a2, Vector2 bCenter, float radius, Vector2 intersections[2])
{
    float A, B, C, det, t;
    
    Vector2 aD = a2 - a1;
    
    A = aD.squareLength();
    B = 2 * (aD.x * (a1.x - bCenter.x) + aD.y * (a1.y - bCenter.y));
    C = (a1.x - bCenter.x) * (a1.x - bCenter.y) + (a1.y - bCenter.y) * (a1.y - bCenter.y) - sqr(radius);
    
    det = B * B - 4 * A * C;
    if ((A <= EPSILON) || (det < 0)) {
        // No real solutions.
        if (intersections) {
            intersections[0] = NULL;
            intersections[1] = NULL;
        }
        return 0;
    } else if (det == 0) {
        // One solution.
        t = -B / (2 * A);
        if (intersections) {
            intersections[0] = Vector2(a1.x + t * aD.x, a1.y + t * aD.y);
            intersections[1] = NULL;
        }
        return 1;
    } else {
        // Two solutions.
        if (intersections) {
            t = (float)((-B + std::sqrt(det)) / (2 * A));
            intersections[0] = Vector2(a1.x + t * aD.x, a1.y + t * aD.y);
        
            t = (float)((-B - std::sqrt(det)) / (2 * A));
            intersections[1] = Vector2(a1.x + t * aD.x, a1.y + t * aD.y);
        }
        return 2;
    }
}


