//
//  Body.h
//  Drawing
//
//  Created by Adrian Russell on 10/9/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __Body_H__
#define __Body_H__

#include "types.h"
#include "Vector2.h"
#include "Rect.h"
#include "Object.h"
#include "Matrix22.h"

typedef u_int64_t CollisionLevel;
typedef u_int64_t CollisionGroup;
static const CollisionGroup CollisionGroupAllGroups = 0;
static const CollisionLevel CollisionLevelAllLevels = 0;

struct Body : public Object
{
    /*! The posible body types available */
    enum BodyType
    {
        BodyTypeCircle,
        BodyTypePolygon,
    };
    
    /*! Creates a new body
     @param position        The position to set the center of mass.
     @param mass            The mass of the body.
     @param staticFriction  The coefficient of friction.
     @param dynamicFriction The coefficient of dynamic friction.
     @param restitution     The coefficient of restitution.
     @param rotation        The angle of the body.
     */
    Body(Vector2 position, float mass, float staticFriction = 0.5f, float dynamicFriction = 0.3f, float restitution = 0.2f, float rotation = 0.0f);
    
    /*!
     Apply a constant force to the body. The force is applied to the centre of mass.
     @param f
            The value of the force to apply.
     */
    void applyForce(const Vector2& f);
    
    /*!
     Apply a one time impulse to the body.
     @param impulse
            The force of the impulse.
     @param contactVector
            The position to apply the force offset from the centre of mass.
     */
    void applyImpulse(const Vector2& impulse, const Vector2& contactVector);
    
    
    /*! Returns whether or not the body is intersected by the specified ray
     @param a
            The first point of the ray
     @param b
            The second point of the ray
     @return a bool indicating if the ray intersects the body.
     */
    virtual bool intersectsRay(const Vector2& a, const Vector2& b) = 0;
    
    
    virtual bool intersectsRay(const Vector2& ray) = 0;
    
    /*! Returns whether or not the body contains the specified point
     @param point
            The point to test.
     @return a bool indicating if the point is contained by the body.
     */
    virtual bool containsPoint(const Vector2& point) = 0;
    
    //-- Static
    
    /*! Returns whether, or not, the body is static and not affected by forces.
     @return A bool indicating whether, or not, the body is static and not affected by forces
     */
    bool isStatic();
    
    /*! Set the body to be static. */
    void setStatic();
    
    
    //-- Forces
    
    void resetAllEnergy();
    void resetForces();
    void integrateForces(float dt, float damping);
    void integrateVelocities(float dt);
    
    
    //-- Position
    
    Vector2 position() { return _position; }
    void setPosition(Vector2 p);
    
    
    
    
    virtual BodyType bodyType() = 0;
    
    virtual Matrix22 rotationMatrix()  { return Matrix22::rotationMatrix(_rotation); };
    float rotation() { return _rotation; }
    void setRotation(float radians);
    
    
    Vector2 velocity()        { return _velocity;        }
    float   angularVelocity() { return _angularVelocity; }
    
    
    float mass()    { return _mass;    }
    float invMass() { return _invMass; }
    
    void setMass(float mass);
    
    float inertia()    { return _inertia;    }
    float invInertia() { return _invInertia; }
    void setInertia(float i);
    
    float staticFriction()  { return _staticFriction;  }
    float dynamicFriction() { return _dynamicFriction; }
    
    void setStaticFriction(float sf) { _staticFriction = sf; }
    void setDynamicFriction(float df) { _dynamicFriction = df; }
    
    float restitution() { return _restitution; }
    void setRestitution(float e) { _restitution = e; }
    
    
    CollisionLevel collisionLevels() { return _levels; }
    void setLevels(CollisionLevel levels) { _levels = levels; }
    
    
    CollisionGroup collisionGroups()      { return _groups; }
    void setGroups(CollisionGroup groups) { _groups = groups; }
    
    /*! Returns the axis-aligned bounding box that fits the body.
     @return The axis-aligned bounding box that fits the body.
     */
    Rect &AABB() { return _AABB; }
    
    
protected:
    
    virtual Rect recalculateAABB() = 0;
    
    
    Vector2 _position;
    
    float   _angularVelocity;
    Vector2 _velocity;
    
    Rect _AABB;
    
    Vector2 _force;
    float   _torque;
    
    float _inertia;     // moment of inertia
    float _invInertia;  // inverse moment of inertia
    float _mass;        // mass
    float _invMass;     // inverse mass
    
    float _staticFriction;
    float _dynamicFriction;
    float _restitution;
    
    float _rotation; // radians
    
    CollisionLevel _levels;
    CollisionGroup _groups;
};

#endif
