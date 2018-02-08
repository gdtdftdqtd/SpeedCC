//
//  SCRefHolder.hpp
//  libspeedcc
//
//  Created by Kevin on 18/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCREF2PTR_H__
#define __SPEEDCC__SCREF2PTR_H__

#include "cocos2d.h"
#include "../base/SCObject.h"

namespace SpeedCC
{
    ///---------- SCRef2Ptr
    class SCRef2Ptr : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCRef2Ptr)
        SC_DEFINE_CLASS_PTR(SCRef2Ptr)
        
        SC_DEFINE_CREATE_FUNC_1(SCRef2Ptr,cocos2d::Ref*)
        
        virtual ~SCRef2Ptr();
        
        inline cocos2d::Ref* getRef() const {return _pObject;}
    protected:
        SCRef2Ptr():
        _pObject(NULL)
        {}
        
        SCRef2Ptr(cocos2d::Ref* pObject);
        
    private:
        cocos2d::Ref*   _pObject;
    };
    
    ///------------- SCPtr2Ref
    class SCPtr2Ref : public cocos2d::Ref
    {
    public:
        static cocos2d::Ref* create();
        static cocos2d::Ref* create(SCObject::Ptr ptr);
        
        inine void setPtr(SCObject::Ptr ptr) { _ptrObj = ptr; }
        inline SCObject::Ptr getPtr() const { return _ptrObj;}
        
    protected:
        SCPtr2Ref();
        SCPtr2Ref(SCObject::Ptr ptr);
        
    private:
        SCObject::Ptr       _ptrObj;
    };
}

#endif // __SPEEDCC__SCREF2PTR_H__
