//
//  Array.h
//
//  Created by Adrian Russell on 10/10/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//


#ifndef __ARPhysics__Array_H__
#define __ARPhysics__Array_H__

#include "Object.h"
#include <vector>

/*! An array structure for Objects that will retain them when added and release when removed. */
class Array : public Object {
    
public:
    
    /*! The value retuend when an object is not found. */
    static const long ObjectNotFound = INT_MAX;
    
    /*! Initialises an array with the specified length
     @param size
            The size to make the array.
     */
    Array(unsigned int size = 10);
    
    /*! Array destructor. Releases all contents. */
    ~Array();
    
    /*!
     Resizes the array to the specified size.
     @param size
            The new length of the array.
     */
    void resize(unsigned long size);
    
    /*!
     Add a specfied object to the end of the array.
     @param obj
            The object to add to the array.
     */
    void addObject(Object *obj);
    
    /*!
     Removes the specified object from the array.
     @param obj
            The object to remove from the array.
     */
    void removeObject(Object *obj);
    
    /*!
     Removes the object at the specified index. If the index is invalid nothing is performed.
     @param index
            The index of the object to remove.
     */
    void removeObjectAtIndex(unsigned long index);
    
    /*! returns the first object in the array.
     @return The first object in the array. If the array is empty then NULL is returned.
     */
    Object *firstObject();
    
    /*! returns the last object in the array.
     @return The last object in the array. If the array is empty then NULL is returned.
     */
    Object *lastObject();
    
    /*!
     Returns the object at the specified index.
     @param index The index.
     @return The object at the specified index. If the index is invalid then NULL is returned.
     */
    Object *objectAtIndex(unsigned long index);
    
    /*!
     Empties the array of all contents.
     */
    void empty();
    
    /*!
     Returns whether, or not, the array contains the specified object.
     @param obj
            The object to check the existance of.
     @return A bool indicating if the array contain the object.
     */
    bool containsObject(Object *obj);
    
    /*! Returns the index of the specified object in the index.
     @param obj
            The object to get the index for.
     @return The index of the specified object. If the array doesn't contain the object then ObjectNotFound is returned.
     */
    unsigned long indexOfObject(Object *obj);
    
    /*! Returns the number of objects in the array.
     @return The number of objects in the array.
     */
    unsigned long count() { return _newObjs.size(); };
    
    /*! Creates an array containing all the objects in the array that are not also in the specified array/
     @param arr
            The array to test against.
     */
    Array *objectsNotInArray(Array *arr);
    
    
private:
    std::vector<Object *> _newObjs;
};

#endif
