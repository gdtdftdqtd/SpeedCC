//
//  SCRef2Ptr.cpp
//  libspeedcc
//
//  Created by Kevin on 18/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCRefHolder.h"
#include "../base/SCMacroDef.h"

namespace SpeedCC
{
    ///------------- SCRef2Ptr
    SCRef2Ptr::SCRef2Ptr(cocos2d::Ref* pObject):
    _pObject(pObject)
    {
        SCASSERT(_pObject!=NULL);
        _pObject->retain();
    }
    
    SCRef2Ptr::~SCRef2Ptr()
    {
        if(_pObject!=NULL)
        {
            _pObject->release();
        }
    }
    
    ///------------- SCPtr2Ref
    SCPtr2Ref::SCPtr2Ref()
    {
    }
    
    SCPtr2Ref::SCPtr2Ref(SCObject::Ptr ptr):
    _ptrObj(ptr)
    {
    }
    
    cocos2d::Ref* SCPtr2Ref::create()
    {
        SCPtr2Ref * ret = new (std::nothrow) SCPtr2Ref();
        ret->autorelease();
        return ret;
    }
    
    cocos2d::Ref* SCPtr2Ref::create(SCObject::Ptr ptr)
    {
        SCPtr2Ref * ret = new (std::nothrow) SCPtr2Ref(ptr);
        ret->autorelease();
        return ret;
    }
    
    void SCPtr2Ref::setPtrObj(SCObject::Ptr ptr)
    {
        _ptrObj = ptr;
    }
}

