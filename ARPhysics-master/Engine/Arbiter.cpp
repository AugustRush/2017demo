//
//  Arbiter.cpp
//  Drawing
//
//  Created by Adrian Russell on 31/12/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Arbiter.h"

Arbiter::Arbiter( Body *a, Body *b ) : _bodyA( a ), _bodyB( b )
{
    // Calculate average restitution
    if (a->isStatic()) {
        _e = b->restitution();
    } else if (b->isStatic()) {
        _e = a->restitution();
    } else {
        _e = (a->restitution() + b->restitution()) / 2.0;
    }
    
    // Calculate average static and dynamic frictions
    _sf = (a->staticFriction()  + b->staticFriction() ) / 2.0;
    _df = (a->dynamicFriction() + b->dynamicFriction()) / 2.0;

    _stepsSinceSeperation = 0;
    state = ArbiterStateNoCollision;
}

void Arbiter::applyImpulse( void )
{
    // Early out and positional correct if both objects have infinite mass
    if (_bodyA->isStatic() && _bodyB->isStatic()) {
        return;
    }
    
    for (unsigned int i = 0; i < contact_count; ++i)
    {
        // Calculate radii from position/centre of mass to contact
        Vector2 ra = contacts[i] - _bodyA->position();
        Vector2 rb = contacts[i] - _bodyB->position();
        
        // Relative velocity
        Vector2 rv = _bodyB->velocity() + (rb.perpendicular() * _bodyB->angularVelocity()) - _bodyA->velocity() - (ra.perpendicular() * _bodyA->angularVelocity());
        
        // Relative velocity along the normal
        float contactVel = Vector2::dotProduct(rv, normal);
        
        // Do not resolve if velocities are separating
        if(contactVel > 0)
            return;
        
        float raCrossN = Vector2::dotProduct(ra.perpendicular(), normal);
        float rbCrossN = Vector2::dotProduct(rb.perpendicular(), normal);
        float invMassSum = _bodyA->invMass() + _bodyB->invMass() + (sqr(raCrossN) * _bodyA->invInertia()) + (sqr(rbCrossN) * _bodyB->invInertia());
        
        // Calculate impulse scalar
        float j = -(1.0f + _e) * contactVel;
        j /= invMassSum;
        j /= (float)contact_count;
        
        // Apply impulse
        Vector2 impulse = normal * j;
        _bodyA->applyImpulse(-impulse, ra);
        _bodyB->applyImpulse( impulse, rb);
        
        //== Friction impulse ==//
        
        // Re-calculate relative velocity after normal impulse is applied
        rv = _bodyB->velocity() + (rb.perpendicular() * _bodyB->angularVelocity()) - _bodyA->velocity() - (ra.perpendicular() * _bodyA->angularVelocity());
        
        // Solve for the tangent vector
        Vector2 t = rv - (normal * Vector2::dotProduct( rv, normal ));
        t = t.normalise();
        
        // j tangent magnitude
        float jt = -Vector2::dotProduct( rv, t );
        jt /= invMassSum;
        jt /= (float)contact_count;
        
        // Don't apply tiny friction impulses
        //if(equal( jt, 0.0f ))
        //    return;
        
        // Clamp magnitude of friction and create impulse vector
        // Coulumb's law
        Vector2 frictionImpulse;
        if(std::abs( jt ) < j * _sf)
            frictionImpulse = jt * t;
        else
            frictionImpulse = -j * t * _df;
        
        // Apply friction impulse
        _bodyA->applyImpulse(-frictionImpulse, ra);
        _bodyB->applyImpulse( frictionImpulse, rb);
    }
}

void Arbiter::positionalCorrection( void )
{
    const float k_slop = 0.05f; // Penetration allowance
    const float percent = 0.4f; // Penetration percentage to correct
    Vector2 correction = (std::max( penetration - k_slop, 0.0f ) / (_bodyA->invMass() + _bodyB->invMass())) * normal * percent;
    Vector2 aPos = _bodyA->position() - (correction * _bodyA->invMass());
    Vector2 bPos = _bodyB->position() + (correction * _bodyB->invMass());
    _bodyA->setPosition(aPos);
    _bodyB->setPosition(bPos);
}


unsigned int Arbiter::increaseStepCount()
{
    if (state == ArbiterStateSeparated) {
        _stepsSinceSeperation++;
    } else {
        _stepsSinceSeperation = 0;
    }
    
    return _stepsSinceSeperation;
}


