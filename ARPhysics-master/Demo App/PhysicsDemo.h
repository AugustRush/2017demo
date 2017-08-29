//
//  PhysicsDemo.h
//
//  Created by Adrian Russell on 10/11/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#ifndef __Drawing__PhysicsDemo__
#define __Drawing__PhysicsDemo__

#include "PhysicsEngine.h"

#include "Drawing.h"
#include <typeinfo>
#include <GLUT/glut.h>

class PhysicsDemo {
    
public:
    
    virtual ~PhysicsDemo() {}
    
    virtual void draw()
    {
        unsigned long numberOfBodies = world->getBodies()->count();
        for (unsigned long i = 0; i < numberOfBodies; i++) {
            
            Object *body = world->getBodies()->objectAtIndex(i);
            
            CircleBody *circle = dynamic_cast<CircleBody *>(body);
            if (circle != NULL) {
                drawCircleBody(circle, kRedColor, kWhiteColor, false);
            }
            
            PolygonBody *polygon = dynamic_cast<PolygonBody *>(body);
            if (polygon != NULL) {
                drawPolygonBody(polygon, kNoColor, kWhiteColor);
            }
        }
        
        Array *arbiters = world->indexing()->arbiters();
        for (unsigned int i = 0; i < arbiters->count(); i++) {
            Arbiter *arbiter = (Arbiter *)arbiters->objectAtIndex(i);
            for (unsigned int j = 0; j < arbiter->contact_count; j ++) {
                Vector2 position = arbiter->contacts[j];
                drawRect(Rect(position.x, position.y, 1.0, 1.0), 0.0, kGreenColor, kGreenColor);
            }
        
        }
        
        Array *constraints = world->getConstraints();
        for (unsigned int i = 0; i < constraints->count(); i++) {
            DampedSpring *spring = (DampedSpring *)constraints->objectAtIndex(i);
            drawLine(spring->getA()->position(), spring->getB()->position(), kGreenColor);
        }
    };
    
    
    virtual void update(float dt) { world->step(dt); }
    
    virtual void mouseMoved(int x, int y) {};
    
    virtual void mouseEvent(int button, int state, int x, int y) {};
    
    virtual void keyPressed(unsigned char key, int x, int y) {};
    
    virtual void keyUnpressed(int key, int x, int y) {};
    
    virtual std::string name() = 0;
    
public:
    World *world;
};



#endif /* defined(__Drawing__PhysicsDemo__) */
