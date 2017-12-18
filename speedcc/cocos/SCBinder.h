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
        void setStringSource(T num)
        {
            num->addPosUpdateFun([this](T* pNum,typename T::NumberType newNum,typename T::NumberType oldNum)
                                {
                                    if(_pLabel!=NULL && _bActive)
                                    {
                                        _pLabel->setString(pNum->getString().c_str());
                                    }
                                    _strLast = pNum->getString();
                                });
            
            if(_pLabel!=NULL && _bActive)
            {
                _pLabel->setString(num.getString().c_str());
            }
            else
            {
                _strLast = num.getString();
            }
        }
        
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
