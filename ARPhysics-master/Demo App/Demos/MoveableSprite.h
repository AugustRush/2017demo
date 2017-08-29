//
//  MoveableSprite.h
//  Drawing
//
//  Created by Adrian Russell on 09/04/2014.
//  Copyright (c) 2014 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__MoveableSprite__
#define __Drawing__MoveableSprite__

#include "PhysicsDemo.h"

class MoveableSprite : public PhysicsDemo
{
public:
    MoveableSprite();
    ~MoveableSprite();
    
    void keyPressed(unsigned char key, int x, int y);
    
    std::string name() { return "Movable Sprite"; };
    
private:
    Body *_sprite;
    Body *_tokenA;
    Body *_tokenB;
    Body *_tokenC;
    bool tokenCollisionBegin(Arbiter *arbiter);
    bool finalCollisionBegin(Arbiter *arbiter);
    void removeBodyCallback(World *world, void *key);
    void removeFinalBodyCallback(World *world, void *key);
};

#endif
