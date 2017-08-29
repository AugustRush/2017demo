//
//  World_Utilities.cpp
//  Drawing
//
//  Created by Adrian Russell on 09/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "World_Utilities.h"
#include "Rect.h"
#include "PolygonBody.h"
#include "PolygonPath.h"

void addBorderWallsToWorld(World *world, float wallThickness, float friction)
{
    float worldWidth    = world->getWidth();
    float worldHeight   = world->getHeight();
    float halfThickness = wallThickness / 2.0;
    
    PolygonBody *leftWall = new PolygonBody(Rect(halfThickness, 0, halfThickness, worldHeight), 0.0);
    leftWall->setStaticFriction(friction);
    world->addBody(leftWall);
    leftWall->release();
    
    PolygonBody *rightWall = new PolygonBody(Rect(worldWidth - halfThickness, 0, halfThickness, worldHeight), 0.0);
    rightWall->setStaticFriction(friction);
    world->addBody(rightWall);
    rightWall->release();
    
    PolygonBody *bottomWall = new PolygonBody(Rect(0.0, halfThickness, worldWidth, halfThickness), 0.0);
    bottomWall->setStaticFriction(friction);
    world->addBody(bottomWall);
    bottomWall->release();
    
    PolygonBody *topWall = new PolygonBody(Rect(0.0, worldHeight - halfThickness, worldWidth, halfThickness), 0.0);
    topWall->setStaticFriction(friction);
    world->addBody(topWall);
    topWall->release();
    
    
}