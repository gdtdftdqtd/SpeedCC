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
        inline bool getActive() const {return _bActive;}
        
        virtual void reset(){ _bActive = true; }
    protected:
        SCBinder():
        _bActive(true)
        {}
        
        virtual void onActiveChanged(const bool bNewActive) {}
        
    private:
        bool    _bActive;
    };
    
    
    ///-------------- SCBinderUILabel
    class SCBinderUILabel : public SCBinder
    {
    public:
        SC_AVOID_CLASS_COPY(SCBinderUILabel)
        SC_DEFINE_CLASS_PTR(SCBinderUILabel)
        
        SC_DEFINE_CREATE_FUNC_0(SCBinderUILabel)
        SC_DEFINE_CREATE_FUNC_1(SCBinderUILabel,cocos2d::Label*)
        
        virtual ~SCBinderUILabel();
        
        inline cocos2d::Label* getLabel() const { return _pLabel; }
        void setLabel(cocos2d::Label* pLabel);
        
        template<typename T>
        void setWatch(T num)
        {
            this->removeUpdateFunc();
            
            const int nID = num->addUpdateFunc([this](T ptrNum,typename T::type newNum,typename T::type oldNum)
                                               {
                                                   if(_pLabel!=NULL && this->getActive())
                                                   {
                                                       _pLabel->setString(ptrNum->getString().c_str());
                                                   }
                                                   _strLast = ptrNum->getString();
                                               });
            
            if(_pLabel!=NULL && this->getActive())
            {
                _pLabel->setString(num->getString().c_str());
            }
            else
            {
                _strLast = num->getString();
            }
            
            _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
            {
                SC_RETURN_IF_V(ptr==NULL || nID<=0);
                
                auto p = ptr.cast<T>();
                p->removeUpdateFunc(nID);
            };
            
            _ptrWatchSource = num;
            _nFuncID = nID;
        }
        
        void setWatch(SCWatchString::Ptr watchStr);
        virtual void reset() override;
        
    protected:
        SCBinderUILabel():
        _pLabel(NULL),
        _removeUpdateFunc(NULL)
        {}
        
        SCBinderUILabel(cocos2d::Label* pLabel):
        _pLabel(pLabel),
        _removeUpdateFunc(NULL)
        {}
        
        virtual void onActiveChanged(const bool bNewActive) override;
        void removeUpdateFunc();

    private:
        cocos2d::Label*     _pLabel;
        SCObject::Ptr       _ptrWatchSource;
        SCString            _strLast;
        std::function<void(SCObject::Ptr ptr,const int nID)>   _removeUpdateFunc;
        int                     _nFuncID;
    };
    
    
    ///--------------- SCBinderUIToggle
    class SCBinderUIToggle : public SCBinder
    {
    public:
        SC_AVOID_CLASS_COPY(SCBinderUIToggle)
        SC_DEFINE_CLASS_PTR(SCBinderUIToggle)
        
        SC_DEFINE_CREATE_FUNC_0(SCBinderUIToggle)
        SC_DEFINE_CREATE_FUNC_1(SCBinderUIToggle,SCWatchBool::Ptr)
        SC_DEFINE_CREATE_FUNC_1(SCBinderUIToggle,cocos2d::MenuItemToggle*)
        SC_DEFINE_CREATE_FUNC_2(SCBinderUIToggle,SCWatchBool::Ptr,cocos2d::MenuItemToggle*)
        
        void setWatch(SCWatchBool::Ptr ptrWatch);
        void setCallback(const std::function<void(cocos2d::Ref*)>& func) { _callbackFunc = func;}
        
        inline cocos2d::MenuItemToggle* getToggle() const { return _pToggleMenuItem; }
        void setToggle(cocos2d::MenuItemToggle* pToggle);
        
        inline SCWatchBool::Ptr getWatch() const { return _ptrWatch; }
        virtual void reset() override;
        
    protected:
        SCBinderUIToggle():
        _pToggleMenuItem(NULL),
        _callbackFunc(NULL),
        _removeUpdateFunc(NULL),
        _nFuncID(0)
        {
        }
        
        SCBinderUIToggle(SCWatchBool::Ptr ptrWatch):
        _pToggleMenuItem(NULL),
        _callbackFunc(NULL),
        _removeUpdateFunc(NULL),
        _nFuncID(0)
        {
            this->setWatch(ptrWatch);
        }
        
        SCBinderUIToggle(SCWatchBool::Ptr ptrWatch,cocos2d::MenuItemToggle* pToggle):
        _callbackFunc(NULL),
        _removeUpdateFunc(NULL),
        _nFuncID(0)
        {
            this->setWatch(ptrWatch);
            this->setToggle(pToggle);
        }
        
        SCBinderUIToggle(cocos2d::MenuItemToggle* pToggle):
        _callbackFunc(NULL),
        _removeUpdateFunc(NULL),
        _nFuncID(0)
        {
            this->setToggle(pToggle);
        }
        
        void removeUpdateFunc();
        virtual void onActiveChanged(const bool bNewActive) override;
        
        void updateValue2Toggle();
        void onMenuItemClicked(cocos2d::Ref* pSender);
        
    private:
        SCWatchBool::Ptr                        _ptrWatch;
        cocos2d::MenuItemToggle*                _pToggleMenuItem;
        std::function<void(SCObject::Ptr ptr,
                           const int nID)>      _removeUpdateFunc;
        int                                     _nFuncID;
        std::function<void(cocos2d::Ref*)>      _callbackFunc;
    };
    
    /*
    ///-------------- SCBinderSetting
    class SCSetting;
    class SCBinderSetting : public SCBinder
    {
        friend class SCSetting;
    public:
        SC_AVOID_CLASS_COPY(SCBinderSetting)
        SC_DEFINE_CLASS_PTR(SCBinderSetting)
        
        static Ptr create(const SCString& strSettingKey);
        
        void setWatch(SCWatchFloat::Ptr watchFloat,const float fDefault=0.0f);
        void setWatch(SCWatchDouble::Ptr watchDoube,const double dDefault=0.0);
        void setWatch(SCWatchBool::Ptr watchBool,const bool bDefault=false);
        void setWatch(SCWatchInt::Ptr watchInt,const int nDefault=0);
        void setWatch(SCWatchString::Ptr watchStr);
        
    protected:
        SCBinderSetting()
        {}
        
        SCBinderSetting(const SCString& strSettingKey)
        {}
        
    private:
        SCString        _strSettingKey;
    };
     */
}

#endif //__SPEEDCC__SCBINDER_H__
