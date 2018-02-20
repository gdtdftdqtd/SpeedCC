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
        SCASSERT(_pObject!=nullptr);
        _pObject->retain();
    }
    
    SCRef2Ptr::~SCRef2Ptr()
    {
        if(_pObject!=nullptr)
        {
            _pObject->release();
        }
    }
    
    ///------------- SCPtr2Ref
    SCPtr2Ref::SCPtr2Ref()
    {
    }
    
    SCPtr2Ref::~SCPtr2Ref()
    {
    }
    
    SCPtr2Ref::SCPtr2Ref(SCObject::Ptr ptr):
    _ptrObj(ptr)
    {
    }
    
    cocos2d::Ref* SCPtr2Ref::create()
    {
        auto ret = new (std::nothrow) SCPtr2Ref();
        ret->autorelease();
        return ret;
    }
    
    cocos2d::Ref* SCPtr2Ref::create(SCObject::Ptr ptr)
    {
        auto ret = new (std::nothrow) SCPtr2Ref(ptr);
        ret->autorelease();
        return ret;
    }
    
    ///----------- SCRefHolder
    
    SCRefHolder::SCRefHolder()
    {
        
    }
    
    SCRefHolder::~SCRefHolder()
    {
        
    }
    
    SCRefHolder* SCRefHolder::create()
    {
        auto ret = new (std::nothrow) SCRefHolder();
        ret->autorelease();
        return ret;
    }
    
    void SCRefHolder::addObj(cocos2d::Ref* pRef)
    {
        SC_RETURN_V_IF(pRef==nullptr);
        
        _objList.push_back(SCRef2Ptr::create(pRef));
    }
    
    void SCRefHolder::addObj(SCObject::Ptr ptr)
    {
        SC_RETURN_V_IF(ptr==nullptr);
        
        _objList.push_back(ptr);
    }
    
}

