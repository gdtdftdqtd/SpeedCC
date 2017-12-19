//
//  SCBinder.hpp
//  libspeedcc
//
//  Created by Kevin on 17/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCBINDER_H__
#define __SPEEDCC__SCBINDER_H__

#include "cocos2d.h"

#include "../base/SCObject.h"
#include "../base/SCString.h"
#include "../base/SCMacroDef.h"
#include "../base/SCWatchString.h"
#include "../base/SCWatchNumberT.h"

namespace SpeedCC
{
    ///------------- SCBinder
    class SCBinder : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCBinder)
        SC_DEFINE_CLASS_PTR(SCBinder)
        
        void setActive(const bool bActive);
        inline bool isActive() const {return _bActive;}
        
    protected:
        SCBinder():
        _bActive(true)
        {}
        
        virtual void onActiveChanged(const bool bNewActive) {}
        
    protected:
        bool    _bActive;
    };
    
    
    ///-------------- SCBinderLabel
    class SCBinderLabel : public SCBinder
    {
    public:
        SC_AVOID_CLASS_COPY(SCBinderLabel)
        SC_DEFINE_CLASS_PTR(SCBinderLabel)
        
        static Ptr create();
        static Ptr create(cocos2d::Label* pLabel);
        
        inline cocos2d::Label* getLabel() const { return _pLabel; }
        void setLabel(cocos2d::Label* pLabel);
        
        template<typename T>
        void setWatchSource(T num)
        {
            num->addUpdateFun([this](T numPtr,typename T::type newNum,typename T::type oldNum)
                                {
                                    if(_pLabel!=NULL && _bActive)
                                    {
                                        _pLabel->setString(numPtr->getString().c_str());
                                    }
                                    _strLast = numPtr->getString();
                                });
            
            if(_pLabel!=NULL && _bActive)
            {
                _pLabel->setString(num->getString().c_str());
            }
            else
            {
                _strLast = num->getString();
            }
        }
        
        void setWatchSource(SCWatchString::Ptr watchStr);
        
    protected:
        SCBinderLabel():
        _pLabel(NULL)
        {}
        
        SCBinderLabel(cocos2d::Label* pLabel):
        _pLabel(pLabel)
        {}
        
        virtual void onActiveChanged(const bool bNewActive);
        
    private:
        cocos2d::Label*     _pLabel;
        SCString            _strLast;
    };
    
    
    ///-------------- SCBinderSetting
    class SCBinderSetting : public SCBinder
    {
    public:
        SC_AVOID_CLASS_COPY(SCBinderSetting)
        SC_DEFINE_CLASS_PTR(SCBinderSetting)
        
        static Ptr create(const SCString& strSettingKey);
        
        void setWatchSource(SCWatchFloat::Ptr watchFloat,const float fDefault=0.0f);
        void setWatchSource(SCWatchDouble::Ptr watchDoube,const double dDefault=0.0);
        void setWatchSource(SCWatchBool::Ptr watchBool,const bool bDefault=false);
        void setWatchSource(SCWatchInt::Ptr watchInt,const int nDefault=0);
        void setWatchSource(SCWatchString::Ptr watchStr);
        
    protected:
        SCBinderSetting()
        {}
        
        SCBinderSetting(const SCString& strSettingKey)
        {}
        
    private:
        SCString        _strSettingKey;
    };
}

#endif //__SPEEDCC__SCBINDER_H__
