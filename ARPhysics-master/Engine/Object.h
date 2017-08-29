//
//  Object.h
//
//  Created by Adrian Russell on 10/10/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//


#ifndef __ARPhysics__Object_H__
#define __ARPhysics__Object_H__

#include <cassert>

#define SAFE_RELEASE(p) (if (p != NULL) { if(p->getReferenceCount() == 1) {p->release(); p = NULL;} else { p->release(); }})
#define SAFE_DELETE(p)  (if (p != NULL) { delete p; p = NULL; })

/*! This class gives a basic reference counting functionality for objects that inherit. */
class Object {
public:
    
    /*! inititlises and retains an object. */
    Object() { this->_retainCount = 1; };
    
    /*! Object destructor. */
    virtual ~Object() {};
    
    /*! retain the object. */
    void retain() { _retainCount++; };
    
    /*! Release the object. if the retain count reaches 0 then the object will be deleted. */
    void release() {
        assert(_retainCount > 0);
        _retainCount--;
        
        if (_retainCount == 0) {
            delete this;
        }
        
    };
    
    /*! Returns the current retain count of the object.
     @return the current retain count of the object.
     */
    int getRetainCount() { return _retainCount; };
    
    
private:
    int _retainCount;
};


#endif
