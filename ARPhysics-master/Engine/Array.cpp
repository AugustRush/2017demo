//
//  Array.cpp
//
//  Created by Adrian Russell on 10/10/13.
//  Copyright (c) 2013 Adrian Russell. All rights reserved.
//

#include "Array.h"


Array::Array(unsigned int size)
{
    assert(size > 0);
    this->_newObjs = std::vector<Object *>(0);
}

Array::~Array()
{
    empty();
}

void Array::resize(unsigned long size)
{
    _newObjs.resize(size);
}

Object *Array::firstObject()
{
    return _newObjs.front();
}

Object *Array::lastObject()
{
    return _newObjs.back();
}

Object *Array::objectAtIndex(unsigned long index)
{
    return (index < _newObjs.size()) ? _newObjs[index] : NULL;
}


void Array::addObject(Object *obj)
{
    obj->retain();
    _newObjs.push_back(obj);
};


void Array::removeObject(Object *obj)
{
    unsigned long index = this->indexOfObject(obj);
    if (index != this->ObjectNotFound) {
        removeObjectAtIndex(index);
    }
}


void Array::removeObjectAtIndex(unsigned long index)
{
    _newObjs.erase(_newObjs.begin() + index);
}


void Array::empty()
{
    for (unsigned long i = 0; i < _newObjs.size(); i++) {
        Object *obj = _newObjs[i];
        obj->release();
    }
    _newObjs.clear();
}

unsigned long Array::indexOfObject(Object *obj)
{
    auto it = std::find(_newObjs.begin(), _newObjs.end(), obj);
    if (it == _newObjs.end())
    {
        return this->ObjectNotFound;
    } else
    {
        auto index = std::distance(_newObjs.begin(), it);
        return index;
    }
}

bool Array::containsObject(Object *obj)
{
    auto it = std::find(_newObjs.begin(), _newObjs.end(), obj);
    return (it != _newObjs.end());
}

Array *Array::objectsNotInArray(Array *arr)
{
    Array *array = new Array();
    for (unsigned int i = 0; i < count(); i++) {
        Object *obj = objectAtIndex(i);
        if (!arr->containsObject(obj)) {
            array->addObject(obj);
        }
    }
    return array;
}

