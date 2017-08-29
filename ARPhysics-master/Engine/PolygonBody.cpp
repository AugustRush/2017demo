//
//  PolygonBody.cpp
//  Drawing
//
//  Created by Adrian Russell on 31/12/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "PolygonBody.h"


PolygonBody::PolygonBody(Vector2 position, float mass, Vector2 vertices[], unsigned int vertexCount) : Body(position, mass)
{
    _polygonPath      = new PolygonPath(vertices, vertexCount);
    float density     = _mass / _polygonPath->area();
    this->_inertia    = _polygonPath->momentOfIntertia() * density;
    this->_invInertia = this->_inertia ? 1.0f / this->_inertia : 0.0f;
    _AABB             = recalculateAABB();
}


PolygonBody::PolygonBody(Vector2 position, float mass, std::vector<Vector2> vertices) : Body(position, mass)
{
    _polygonPath      = new PolygonPath(vertices);
    float density     = _mass / _polygonPath->area();
    this->_inertia    = _polygonPath->momentOfIntertia() * density;
    this->_invInertia = this->_inertia ? 1.0f / this->_inertia : 0.0f;
    _AABB             = recalculateAABB();
}

PolygonBody::PolygonBody(Vector2 position, float mass, PolygonPath *path) : Body(position, mass)
{
    _polygonPath = path;
    path->retain();
    float density     = _mass / path->area();
    this->_inertia    = path->momentOfIntertia() * density;
    this->_invInertia = this->_inertia ? 1.0f / this->_inertia : 0.0f;
    _AABB             = recalculateAABB();
}


PolygonBody::PolygonBody(Rect rect, float mass) : Body(rect.center(), mass)
{
    _polygonPath      = new PolygonPath(rect);
    float density     = _mass / _polygonPath->area();
    this->_inertia    = _polygonPath->momentOfIntertia() * density;
    this->_invInertia = this->_inertia ? 1.0f / this->_inertia : 0.0f;
    _AABB             = recalculateAABB();
}


PolygonBody::~PolygonBody()
{
    _polygonPath->release();
}

Rect PolygonBody::recalculateAABB()
{
    float minX = FLT_MAX;
    float minY = FLT_MAX;
    float maxX = -FLT_MAX;
    float maxY = -FLT_MAX;
    for (Vector2 v : _polygonPath->vertices()) {
        v = v.transform(_rotation) + _position;
        if (v.x < minX) minX = v.x;
        if (v.y < minY) minY = v.y;
        if (v.x > maxX) maxX = v.x;
        if (v.y > maxY) maxY = v.y;
    }
    return Rect(minX, minY, maxX - minX, maxY - minY);
}

//-----

unsigned int PolygonBody::vertexCount()
{
    return (unsigned int)_polygonPath->vertices().size();
}

const std::vector<Vector2> &PolygonBody::vertices() const
{
    return _polygonPath->vertices();
}

const std::vector<Vector2> &PolygonBody::normals() const
{
    return _polygonPath->faceNormals();
}


bool PolygonBody::intersectsRay(const Vector2& a, const Vector2& b)
{
    return false;
}

bool PolygonBody::intersectsRay(const Vector2& ray)
{
    return false;
}

bool PolygonBody::containsPoint(const Vector2& point)
{
    return false;
}




