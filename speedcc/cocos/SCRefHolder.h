//
//  SCRefHolder.hpp
//  libspeedcc
//
//  Created by Kevin on 18/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCREFHOLDER_H__
#define __SPEEDCC__SCREFHOLDER_H__

#include "cocos2d.h"
#include "../base/SCObject.h"

namespace SpeedCC
{
    class SCRefHolder : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCRefHolder)
        SC_DEFINE_CLASS_PTR(SCRefHolder)
        
        SC_DEFINE_CREATE_FUNC_1(SCRefHolder,cocos2d::Ref*)
        
        virtual ~SCRefHolder();
        
        inline cocos2d::Ref* getRef() const {return _pObject;}
    protected:
        SCRefHolder():
        _pObject(NULL)
        {}
        
        SCRefHolder(cocos2d::Ref* pObject);
        
    private:
        cocos2d::Ref*   _pObject;
    };
}

#endif // __SPEEDCC__SCREFHOLDER_H__
