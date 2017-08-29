//
//  PolygonBody_Utilities.cpp
//  Drawing
//
//  Created by Adrian Russell on 31/03/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#include "PolygonBody_Utilities.h"

PolygonBody *randomShapedBody(float minimumRadius, float maximumRadius, Vector2 position, float mass)
{
    unsigned int count = (unsigned int)randomInRange(3, 30);
    Vector2 *vertices = new Vector2[count];
    float e = randomInRange(minimumRadius, maximumRadius);
    for(unsigned int i = 0; i < count; ++i)
        vertices[i] = Vector2( randomInRange(-e, e), randomInRange(-e, e) );
    
    PolygonBody *b = new PolygonBody(position, mass, vertices, count);
    delete[] vertices;
    return b;
}


void giveBodyAttributesFromOther(Body *to, Body *from)
{
    to->setPosition(from->position());
    to->setMass(from->mass());
}