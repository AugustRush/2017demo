//
//  SpatialIndexing.h
//
//  Created by Adrian Russell on 16/12/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
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

#ifndef __ARPhysics__SpatialIndexing__
#define __ARPhysics__SpatialIndexing__

#include "Object.h"
#include "Array.h"
#include "Arbiter.h"

class World;

/*! The spatialIndexing class is an abstract class that all concreate spatial indexing classes must inherit from.
    This class is used for sorting the bodies in a system to allow for efficient collision testing based on needs required for a game.
 */
class SpatialIndexing : public Object {
public:
    
    
    typedef void (*BodyCollisionFunc)(Body *a, Body *b, Arbiter *arbiter);
    
    /*!
     Initialises the spatial indexing system and sets the body collision method.
     @param bodyCollisionFunc
            The method to use as the body collision function.
     */
    SpatialIndexing(BodyCollisionFunc bodyCollisionFunc)
    {
        _bodyCollisionFunc = bodyCollisionFunc;
    }
    
    /*! Spatial indexing destructor. */
    ~SpatialIndexing(){};
    
//---------------------------------------------------------------------------------------------//
#pragma mark Bodies
    
    /*! Sets the bodies in the indexing to those in a specified list.
     @param bodies 
            A list of the bodies to set as those in th system.
     @discussion Depending on the type of spatial indexing used this may not be the way that they are stored. 
     */
    virtual void setBodies(Array *bodies) = 0;
    
    /*! Add a specfied body to the indexing system.
     @param body
            The body to add to the indexing system.
     @discussion If the specified body is already in the indexing system then it will not be added again.
     */
    virtual void addBody(Body *body) = 0;
    
    /*! Remove a specified body from the indexing.
     @param body
            The body to remove.
     @discussion If the body is currently in the indexing system then nothing will happen.
     */
    virtual void removeBody(Body *body) = 0;
    
    /*! Removes all of the bodies in the indexing structure effectively removing them from the world. */
    virtual void removeAllBodies() = 0;
    
    /*! Returns an array of all the bodies currently in the world.
     @return An Array of all the bodies currently in the world.
     @discussion The order of the bodies may change everytime this array is fetched as they may be stored in an entriely different format internally. You should only call this once for every unit it is needed in.
     */
    virtual Array *bodies() = 0;
    
    /*! Returns the number of bodies currently in the world.
     @return The number of bodies currently in the world.
     */
    virtual unsigned int numberOfBodies() = 0;
    
    
//---------------------------------------------------------------------------------------------//
#pragma mark Stuff
    
    
    /*!
     Calculates all of the bodies that are colliding and returns an array of arbiters for each colliding object.
     @param world
            The world in which the spatial indexer belongs to.
     @param dt
            The current time step being simulated.
     @return An Array of Arbiter objects representing each collision in the system at the current time.
     @discussion Calling this method will check the collisions of every single body and so can be resource intensive. It is recommended to call this only once per step.
     */
    virtual Array *calculateCollisions(World *world, float dt) = 0;
    
    /*! Returns an array of all of the arbiters in the system.
     @param includeIgnored 
            Whether, or not, to include all of the arbiters for collisions that are set to be ignored. By default it will include them.
     @return An array of all of the arbiters in the system.
     */
    virtual Array *arbiters(bool includeIngnored = true) = 0;
    
//---------------------------------------------------------------------------------------------//
#pragma mark Stuff
    
    
    /*! Returns an array of all bodies that are in a circular area.
     @param center
            The center of the circular area.
     @param radius
            The radius of the circular area.
     @return An array containing all, if any, bodies that are in the circular area.
     */
    virtual Array *bodiesInCircularArea(Vector2 center, float radius) = 0;
    
    
    /*! Returns an array of all bodies that are in a rectangular area.
     @param rect
            The rectange to check.
     @return An array containing all, if any, bodies that are in the rectangular area.
     @discussion Note that the rectangular area is alway axis aligned. If you need the rectangluar area rotated you will need to create a method to do so yourself.
     */
    virtual Array *bodiesInRectanglarArea(Rect rect) = 0;
    
    /*! Returns an body closest to the specified point in the world.
     @param point
            The point to check.
     @return The body closest to the specified point.
     */
    virtual Body *closestBodyToPoint(Vector2 point) = 0;
    
    
protected:
    BodyCollisionFunc _bodyCollisionFunc;   // the function to use for testing body collisions
};


#endif
