//
//  GroupForceGenerator.h
//
//  Created by Adrian Russell on 09/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __ARPhysics__GroupForceGenerator_H_
#define __ARPhysics__GroupForceGenerator_H_

#include "ForceGenerator.h"

/*! The GroupForceGenerator will be applied to all bodies in the collision groups that the force generator is set to be applied to. */
class GroupForceGenerator : public ForceGenerator
{
public:
    
    GroupForceGenerator(CollisionLevel groups = CollisionLevelAllLevels) : ForceGenerator()
    {
        _groups = groups;
    }
    
    
    virtual bool shouldApplyToBody(Body *b)
    {
        return (_groups == CollisionGroupAllGroups || b->collisionLevels() & _groups);
    }
    
    CollisionLevel groups()               { return _groups; }
    void setGroups(CollisionLevel groups) { _groups = groups; }
    
protected:
    CollisionLevel _groups;
};


#endif
