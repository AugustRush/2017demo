//
//  PhysicsEngine.h
//
//  Created by Adrian Russell on 10/11/13.
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

#ifndef _ARPhysics_PhysicsEngine_H_
#define _ARPhysics_PhysicsEngine_H_

// spatial indexing
#include "SpatialIndexing.h"
#include "BruteForceIndexing.h"

// bodies
#include "Body.h"
#include "CircleBody.h"
#include "PolygonBody.h"

// world
#include "World.h"

// collisions
#include "Arbiter.h"
#include "Collision.h"

// force generators
#include "ForceGenerator.h"
#include "LinearForceGenerator.h"
#include "GravityForceGenerator.h"
#include "GravityToPointForceGenerator.h"


// constraints
#include "Constraint.h"
#include "Spring.h"
#include "DampedSpring.h"
#include "Rod.h"

// types
#include "types.h"
#include "Vector2.h"
#include "Matrix22.h"
#include "Rect.h"
#include "Object.h"
#include "Array.h"
#include "PolygonPath.h"

// utilities
#include "Physics_Utilities.h"
#include "Shape_Utilities.h"
#include "PolygonBody_Utilities.h"
#include "World_Utilities.h"

#endif
