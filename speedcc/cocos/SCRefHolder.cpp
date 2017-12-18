//
//  SCRefHolder.cpp
//  libspeedcc
//
//  Created by Kevin on 18/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCRefHolder.h"
#include "../base/SCMacroDef.h"

namespace SpeedCC
{
    SCRefHolder::SCRefHolder(cocos2d::Ref* pObject):
    _pObject(pObject)
    {
        SCASSERT(_pObject!=NULL);
        _pObject->retain();
    }
    
    SCRefHolder::~SCRefHolder()
    {
        if(_pObject!=NULL)
        {
            _pObject->release();
        }
    }
    
    SCRefHolder::Ptr SCRefHolder::create(cocos2d::Ref* pObject)
    {
        SCASSERT(pObject!=NULL);
        Ptr ret;
        ret.createInstanceWithCon([pObject](void* pData)
                                  {
                                      new(pData)SCRefHolder(pObject);
                                  });
        
        return ret;
    }
}

