//
//  CollisionTests.cpp
//  Drawing
//
//  Created by Adrian Russell on 31/12/2013.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Collision.h"
#include "catch.hpp"

TEST_CASE("Circle Vs Circle", "Collision")
{
    //Contact contact[2];
    //unsigned int i = circleVScircle(Vector2(10, 10), 10, Vector2(25, 10), 10, contact);
    
    //unsigned int j = circleVScircle(Vector2(25, 10), 12, Vector2(10, 10), 10, contact);
    
}


TEST_CASE("Lines Intersect", "Collision")
{
    Vector2 a;
    bool intersection = intersectionOfLines(Vector2(10, 0), Vector2(20, 0), Vector2(15, -10), Vector2(15, 20), &a);
    REQUIRE(intersection);
    REQUIRE(a.x == 15.0);
    REQUIRE(a.y == 0.0);
    
    Vector2 b;
    intersection = intersectionOfLines(Vector2(2, 2), Vector2(4, 4), Vector2(2, 4), Vector2(4, 2), &b);
    REQUIRE(intersection);
    REQUIRE(b.x == 3.0);
    REQUIRE(b.y == 3.0);
}