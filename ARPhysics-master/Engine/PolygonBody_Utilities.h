//
//  PolygonBody_Utilities.h
//  Drawing
//
//  Created by Adrian Russell on 31/03/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__PolygonBody_Utilities__
#define __Drawing__PolygonBody_Utilities__

#include "PolygonBody.h"
#include "World.h"


// random shape
PolygonBody *randomShapedBody(float minimumRadius, float maximumRadius, Vector2 position, float mass);

void giveBodyAttributesFromOther(Body *to, Body *from);

// split them
bool splitBodyAtRay(PolygonBody *body, Vector2 rayA, Vector2 rayB, World *world, PolygonBody **newA, PolygonBody **newB);

#endif
