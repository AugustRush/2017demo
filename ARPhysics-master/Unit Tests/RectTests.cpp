//
//  RectTests.cpp
//
//  Created by Adrian Russell on 9/25/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Rect.h"
#include "catch.hpp"

TEST_CASE("Rect / Creation", "Rect")
{
    Rect a = Rect();
    REQUIRE(a.origin().x == 0.0);
    REQUIRE(a.origin().y == 0.0);
    REQUIRE(a.width()    == 0.0);
    REQUIRE(a.height()   == 0.0);
    
    Rect b = Rect(2.0, 3.0, 4.0, 5.0);
    REQUIRE(b.origin().x == 2.0);
    REQUIRE(b.origin().y == 3.0);
    REQUIRE(b.width()    == 4.0);
    REQUIRE(b.height()   == 5.0);
    
    
    Vector2 v = Vector2(10.0, 11.0);
    Rect c = Rect(v, 12.0, 13.0);
    REQUIRE(c.origin().x == 10.0);
    REQUIRE(c.origin().y == 11.0);
    REQUIRE(c.width()    == 12.0);
    REQUIRE(c.height()   == 13.0);

}