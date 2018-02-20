//
//  SCBinder.cpp
//  libspeedcc
//
//  Created by Kevin on 17/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCBinder.h"


namespace SpeedCC
{
    
///------------- SCBinder
    SCBinder::~SCBinder()
    {
        this->reset();
    }
    
    void SCBinder::setActive(const bool bActive)
    {
        _bActive = bActive;
        this->onActiveChanged(_bActive);
    }
    
    void SCBinder::removeUpdateFunc()
    {
        if(_removeUpdateFunc!=nullptr && _nFuncID>0)
        {
            _removeUpdateFunc(_ptrWatch,_nFuncID);
        }
        
        _removeUpdateFunc = nullptr;
        _nFuncID = 0;
    }
    
    void SCBinder::reset()
    {
        _bActive = true;
        this->removeUpdateFunc();
        _ptrWatch = nullptr;
    }
    
    
}
