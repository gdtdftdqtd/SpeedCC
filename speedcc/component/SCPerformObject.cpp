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
    
}
