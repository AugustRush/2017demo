//
//  Vector2Tests.h
//
//  Created by Adrian Russell on 9/25/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Vector2.h"
#include "catch.hpp"

TEST_CASE("Vector2 / Creation", "Vector2")
{
    Vector2 a = Vector2();
    REQUIRE(a.x == 0.0);
    REQUIRE(a.y == 0.0);
    
    Vector2 b = Vector2(2.0, 3.0);
    REQUIRE(b.x == 2.0);
    REQUIRE(b.y == 3.0);
}

TEST_CASE("Vector2 / Addition (operator+)", "Vector2")
{
    Vector2 a = Vector2(2,  3);
    Vector2 b = Vector2(10, 11);
    Vector2 c = a + b;
    REQUIRE(c.x == 12);
    REQUIRE(c.y == 14);
    
    Vector2 d = Vector2(2,  10);
    Vector2 e = Vector2(-3, -12);
    Vector2 f = d + e;
    REQUIRE(f.x == -1);
    REQUIRE(f.y == -2);
    
    Vector2 g = Vector2(0,  0);
    Vector2 h = Vector2(-3, 12);
    Vector2 i = g + h;
    REQUIRE(i.x == -3);
    REQUIRE(i.y == 12);
    
    Vector2 j = e + g;
    REQUIRE(j.x == -3);
    REQUIRE(j.y == -12);
}

TEST_CASE("Vector2 / Addition (operator+=)", "Vector2")
{
    Vector2 a = Vector2(2,  3);
    Vector2 b = Vector2(10, 11);
    a += b;
    REQUIRE(a.x == 12);
    REQUIRE(a.y == 14);
    
    Vector2 d = Vector2(2,  10);
    Vector2 e = Vector2(-3, -12);
    d += e;
    REQUIRE(d.x == -1);
    REQUIRE(d.y == -2);
    
    Vector2 g = Vector2(0,  0);
    Vector2 h = Vector2(-3, 12);
    g += h;
    REQUIRE(g.x == -3);
    REQUIRE(g.y == 12);
}


TEST_CASE("Vector2 / Subtraction (operator-)", "Vector2")
{
    Vector2 a = Vector2(10, 11);
    Vector2 b = Vector2(2,  8);
    Vector2 c = a - b;
    REQUIRE(c.x == 8);
    REQUIRE(c.y == 3);
}

TEST_CASE("Vector2 / Multiplication", "Vector2")
{
    Vector2 a = Vector2(10, 11);
    float  b = 3;
    Vector2 c = a * b;
    REQUIRE(c.x == 30);
    REQUIRE(c.y == 33);
}

TEST_CASE("Vector2 / Equality", "Vector2")
{
    Vector2 a = Vector2(10, 11);
    Vector2 b = Vector2(10, 11);
    REQUIRE(a == b);
}

TEST_CASE("Vector2 / Not Equality", "Vector2")
{
    Vector2 a = Vector2(10, 11);
    Vector2 b = Vector2(10, 12);
    REQUIRE(a != b);
}
