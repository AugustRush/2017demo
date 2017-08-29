//
//  World.h
//
//  Created by Adrian Russell on 10/9/13.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//
//  This software is provided 'as-is', without any express or implied
//  warranty. In no event will the authors be held liable for any damages
//  arising from the use of this software. Permission is granted to anyone to
//  use this software for any purpose, including commercial applications, and to
//  alter it and redistribute it freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source
//     distribution.
//

#ifndef __ARPhysics__World_H__
#define __ARPhysics__World_H__

#include "types.h"
#include "Body.h"
#include "Array.h"
#include "Constraint.h"
#include "SpatialIndexing.h"
#include "ForceGenerator.h"
#include <unordered_map>

/*!
 The World class is the base class representing an area where simulation can take place.
 */
class World : public Object {
    
public:
    
    /*!
     Constructor for World object.
     @param width
            The width of the world.
     @param height   
            The height of the world.
     @param indexing 
            The spatial indexing system to use for the world.
     @param numberOfIterations
            The number of times to solve the collisions and constraints each step. 
            The larger this number the more accurate the simulation will be but the slower it will run.
            The default is 5.
     @discussion Note that bodies can go beyond the bounds of the world making the world size arbitrary.
     */
    World(float width, float height, SpatialIndexing *indexing, unsigned int numberOfIterations = 5);

    /*! World destructor. */
    ~World();
    
    /*! Advances the physics simulation by a specified time.
     @param dt (Delta Time) The time to advance the simulation by in seconds. I.e. if 0.0166 is specfied then all bodies and forces will be advanced in their states by 0.0166 seconds.
     */
    virtual void step(float dt);
    
    /*! 
     Returns the width of the world.
     @return The width of the world.
     */
    float getWidth() { return _width; };
    
    /*! 
     Returns the height of the world.
     @return The height of the world.
     */
    float getHeight() { return _height; };
    
    
//---------------------------------------------------------------------------------------//
#pragma mark Indexing
    
    /*!
     Returns the spatial indexing system used by the world.
     @return The spatial indexing system used by the world.
     */
    SpatialIndexing *indexing() { return this->_indexing; };
    
    
//---------------------------------------------------------------------------------------//
#pragma mark Bodies
    
    /*!
     Adds a body to the world that allows it to be simulated.
     @param body 
            The body to add to the world.
     @discussion If the body has already been added to the world then it will not be added again.
     */
    virtual void addBody(Body *body);
    
    /*!
     Returns an array of all of the bodies in the world.
     @return An array of Body* objects representing all bodies.
     */
    virtual Array* getBodies() { return this->_indexing->bodies(); };
    
    
    virtual void removeBody(Body *body);
    
//---------------------------------------------------------------------------------------//
#pragma mark Constraints
    
    /*!
     Returns an array of all of the contraints registered in the world.
     @return An Array of all of the contraints registered in the world.
     */
    virtual Array *getConstraints() { return this->_constraints; };
    
    
    /*!
     Adds a constraint to the world, if it hasn't alreadt been added.
     @param constraint
            The constraint to add to the world
     */
    virtual void addConstraint(Constraint *constraint);
    
    /*!
     Removes a specified constraint from the world.
     @param constraint
            The constraint to remove.
     */
    virtual void removeConstraint(Constraint *constraint);
    
//---------------------------------------------------------------------------------------//
#pragma mark Force Generators
    
    
    /*!
     Returns an array of all of the contraints registered in the world.
     @return An Array of all of the contraints registered in the world.
     */
    virtual Array *getForceGenerators() { return this->_forceGenerators; };
    
    /*!
     Adds a force generator to the world, if it hasn't already been added.
     @param generator
            The force generator to add to the world
     */
    virtual void addForceGenerator(ForceGenerator *generator);
    
    
    /*!
     Removes a specified force generator from the world.
     @param generator
     The force generator to remove.
     */
    virtual void removeForceGenerator(ForceGenerator *generator);
    
    
//---------------------------------------------------------------------------------------//
#pragma mark Collision Handlers
    
    // collision handling
    typedef uintptr_t CollisionKey;
    
    typedef std::function<bool(Arbiter *)> CollisionBeginFunc;
    typedef std::function<bool(Arbiter *)> CollisionPreSolveFunc;
    typedef std::function<void(Arbiter *)> CollisionPostSolveFunc;
    typedef std::function<void(Arbiter *)> CollisionEndFunc;
    
    typedef std::function<void(World *, void *)> CollisionPostStepCallBack;
    
    struct CollisionHandler
    {
        CollisionLevel          a;            // the type of the first collision body
        CollisionLevel          b;            // the type of the second collision body
        CollisionBeginFunc     begin;        // called when start touching
        CollisionPreSolveFunc  presolve;     // called before solving
        CollisionPostSolveFunc postsolve;    // collision been processed
        CollisionEndFunc       end;          // stopped touching
    };
    typedef struct CollisionHandler CollisionHandler;
    
    /*!
     Returns the default collision handler.
     @return The default collision handler.
     */
    CollisionHandler defaultCollisionHander() { return _defaultHandler; }
    
    /*!
     Set the collision handler methods that will be used by default.
     @param begin
            The method to call when bodies collide.
     @param preSolve
            The method to call before the collision is resolved.
     @param postSolve
            The method to call after the collision is resolved.
     @param seperate
            The method to call when the bodies separate.
     @discussion If any value is set to NULL then the current value will be retained.
     */
    void setDefaultCollisionHandler(CollisionBeginFunc begin, CollisionPreSolveFunc preSolve, CollisionPostSolveFunc postSolve, CollisionEndFunc seperate);
    
    /*!
     Adds new collisions handler methods for two specified collision levels.
     @param a
            The collision level for one body that will use the specified collision callbacks.
     @param b
            The collision level for the other body that will use the specified collision callbacks.
     @param begin
            The method to call when bodies collide.
     @param preSolve
            The method to call before the collision is resolved.
     @param postSolve
            The method to call after the collision is resolved.
     @param seperate
            The method to call when the bodies separate.
     @return A bool indicating if the if the new collision handler has been added.
     */
    bool addCollisionHandler(CollisionLevel a, CollisionLevel b, CollisionBeginFunc begin, CollisionPreSolveFunc preSolve, CollisionPostSolveFunc postSolve, CollisionEndFunc seperate);
    
    /*!
     Remove the collision handler.
     @param a
            The collision level for one body.
     @param b
            The collision level for the other body.
     @return A bool inducating if the removal was successful. If no collision handler existed then it will return false.
     @discussion *Note:* You can not remove the default handler.
     */
    bool removeCollisionHandler(CollisionLevel a, CollisionLevel b);
    
    /*!
     Removes all collision handlers, except the default handler.
     @return A bool inducating whether or not all collision handelrs were removed.
     */
    bool removeAllCollisionHandlers();
    
    /*!
     Adds a method that will be called at the end of the current step with a specified key that will be passed back.
     @param func
            The method to call and the end of the current step.
     @param key
            The key to be used that will be passed back when the callback is called.
     @return A bool indicating whether or not the poststep callback was added.
     */
    bool addPostStepCallback(CollisionPostStepCallBack func, void *key);
    
    
    
    /*!
     Returns the collision handler for the two speicfied bodies. 
     @param a
            The first body.
     @param b
            The second body.
     @return The collision handler that will be used for the two bodies.
     @discussion If a specific collision handler has not been specified for the two bodies the defauly collision handler will be returned.
     */
    CollisionHandler collisionHandlerForBodies(Body *a, Body *b);
    
private:
    
    float            _damping;              // the damping applied to forces in each step. (default 1.0).
    unsigned int     _numberOfIterations;   // the number of times to apply impulses & solve constraints in each step.
    SpatialIndexing *_indexing;             // the spatial indexing system to use.
    float            _width;                // the width of the world
    float            _height;               // the height of the world
    Array           *_forceGenerators;      // array of force generators
    Array           *_constraints;          // array of constraints
    CollisionHandler _defaultHandler;       // the defuault collision handler
    
    std::unordered_map<CollisionKey, CollisionHandler> _collisionHandlers;
    
    std::unordered_map<void *, CollisionPostStepCallBack> _postStepCallbacks;
    
};

#endif
