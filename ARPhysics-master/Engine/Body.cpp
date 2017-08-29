//
//  Body.cpp
//  Drawing
//
//  Created by Adrian Russell on 10/9/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Body.h"

Body::Body(Vector2 position, float mass, float staticFriction, float dynamicFriction, float restitution, float rotation)
{
    _position        = position;
    _staticFriction  = staticFriction;
    _dynamicFriction = dynamicFriction;
    _rotation        = rotation;
    _restitution     = restitution;
    
    _levels = CollisionLevelAllLevels;
    _groups = CollisionGroupAllGroups;
    resetAllEnergy();
    
    setMass(mass);
}

void Body::setMass(float mass)
{
    _mass    = mass;
    _invMass = (mass) ? (1.0/mass) : 0.0;
}

void Body::setInertia(float i)
{
    _inertia    = i;
    _invInertia = (_inertia) ? 1.0f / _inertia : 0.0f;
}

void Body::setPosition(Vector2 p)
{
    _position = p;
    _AABB = recalculateAABB();
}

void Body::setRotation(float radians)
{
    _rotation = radians;
    _AABB = recalculateAABB();
}

void Body::applyForce(const Vector2& f)
{
    _force += f;
}

void Body::applyImpulse(const Vector2& impulse, const Vector2& contactVector)
{
    _velocity        += _invMass * impulse;
    _angularVelocity += _invInertia * Vector2::dotProduct(contactVector.perpendicular(), impulse);
}

void Body::setStatic()
{
    _inertia    = 0.0f;
    _invInertia = 0.0f;
    _mass       = 0.0f;
    _invMass    = 0.0f;
    
    // stop all forces & velocities
    resetAllEnergy();
}

void Body::resetAllEnergy()
{
    resetForces();
    _velocity        = Vector2(0.0, 0.0);
    _angularVelocity = 0.0;
}


void Body::resetForces()
{
    _torque = 0.0;
    _force  = Vector2(0.0, 0.0);
}

bool Body::isStatic()
{
    return (_invMass == 0.0);
}

void Body::integrateForces(float dt, float damping)
{
    if(isStatic()) return;
    
    _velocity        += (_force * _invMass) * (dt) * damping;
    _angularVelocity += _torque * _invInertia * (dt) * damping;
}

void Body::integrateVelocities(float dt)
{
    if(isStatic()) return;
    
    _position += _velocity * dt;
    _rotation += _angularVelocity * dt;
    _AABB = recalculateAABB();
}
