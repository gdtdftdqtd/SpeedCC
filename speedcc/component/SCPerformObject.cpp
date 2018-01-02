//
//  SCPerformObject.cpp
//  libspeedcc
//
//  Created by Kevin on 31/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCPerformObject.h"

namespace SpeedCC
{
    SCPerformObject::SCPerformObject():
    _nID(0),
    _bActive(true)
    {
    }
    
    SCPerformObject::SCPerformObject(const int nID):
    _nID(nID),
    _bActive(true)
    {}
    
    SCPerformObject::~SCPerformObject()
    {
    }
    
    void SCPerformObject::setActive(const bool bActive)
    {
        if(bActive!=_bActive)
        {
            _bActive = bActive;
            this->onActiveChanged(_bActive);
        }
    }
    
    ///----------- SCComponentHolder
    bool SCComponentHolder::hasComponent(const int nID) const
    {
        return (_id2ComponentMap.find(nID)!=_id2ComponentMap.end());
    }
    
    void SCComponentHolder::removeComponent(const int nID)
    {
        _id2ComponentMap.erase(nID);
    }
}
