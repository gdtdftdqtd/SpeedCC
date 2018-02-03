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
        
        virtual void reset();
        
        void removeUpdateFunc();
    protected:
        SCBinder():
        _bActive(true),
        _nFuncID(0)
        {}
        
        virtual void onActiveChanged(const bool bNewActive) {}
        
    protected:
        SCObject::Ptr       _ptrWatch;
        std::function<void(SCObject::Ptr ptr,const int nID)>   _removeUpdateFunc;
        int                     _nFuncID;
        
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
        
        template<typename T,
        typename = typename std::enable_if<SCIsWatchNumberable<typename T::type>::value==1,T>::type >
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
                SC_RETURN_V_IF(ptr==NULL || nID<=0);
                
                auto p = ptr.cast<T>();
                p->removeUpdateFunc(nID);
            };
            
            _ptrWatch = num;
            _nFuncID = nID;
        }
        
        void setWatch(SCWatchString::Ptr watchStr);
        virtual void reset() override;
        
    protected:
        SCBinderUILabel():
        _pLabel(NULL)
        {}
        
        SCBinderUILabel(cocos2d::Label* pLabel):
        _pLabel(pLabel)
        {}
        
        virtual void onActiveChanged(const bool bNewActive) override;

    private:
        cocos2d::Label*     _pLabel;
        SCString            _strLast;
    };
    
    
    ///--------------- SCBinderUIToggle
    class SCBinderUISwitch : public SCBinder
    {
    public:
        virtual ~SCBinderUISwitch();
        
        SC_AVOID_CLASS_COPY(SCBinderUISwitch)
        SC_DEFINE_CLASS_PTR(SCBinderUISwitch)
        
        SC_DEFINE_CREATE_FUNC_0(SCBinderUISwitch)
        SC_DEFINE_CREATE_FUNC_1(SCBinderUISwitch,SCWatchBool::Ptr)
        SC_DEFINE_CREATE_FUNC_1(SCBinderUISwitch,cocos2d::MenuItemToggle*)
        SC_DEFINE_CREATE_FUNC_2(SCBinderUISwitch,SCWatchBool::Ptr,cocos2d::MenuItemToggle*)
        
        void setWatch(SCWatchBool::Ptr ptrWatch);
        void setCallback(const std::function<void(cocos2d::Ref*)>& func) { _callbackFunc = func;}
        
        inline cocos2d::MenuItemToggle* getToggle() const { return _pToggleMenuItem; }
        void setToggle(cocos2d::MenuItemToggle* pToggle);
        
        inline SCWatchBool::Ptr getWatch() const { return _ptrWatch.cast<SCWatchBool::Ptr>(); }
        virtual void reset() override;
        
    protected:
        SCBinderUISwitch():
        _pToggleMenuItem(NULL),
        _callbackFunc(NULL)
        {
        }
        
        SCBinderUISwitch(SCWatchBool::Ptr ptrWatch):
        _pToggleMenuItem(NULL),
        _callbackFunc(NULL)
        {
            this->setWatch(ptrWatch);
        }
        
        SCBinderUISwitch(SCWatchBool::Ptr ptrWatch,cocos2d::MenuItemToggle* pToggle):
        _callbackFunc(NULL)
        {
            this->setWatch(ptrWatch);
            this->setToggle(pToggle);
        }
        
        SCBinderUISwitch(cocos2d::MenuItemToggle* pToggle):
        _callbackFunc(NULL)
        {
            this->setToggle(pToggle);
        }
        
        virtual void onActiveChanged(const bool bNewActive) override;
        
        void updateValue2Toggle();
        void onMenuItemClicked(cocos2d::Ref* pSender);
        
    private:
        cocos2d::MenuItemToggle*                _pToggleMenuItem;
        std::function<void(cocos2d::Ref*)>      _callbackFunc;
    };
    
    ///--------------- SCBinderUIProgress
    class SCBinderUIProgress : public SCBinder
    {
    public:
        virtual ~SCBinderUIProgress();
        
        SC_AVOID_CLASS_COPY(SCBinderUIProgress)
        SC_DEFINE_CLASS_PTR(SCBinderUIProgress)
        
        SC_DEFINE_CREATE_FUNC_0(SCBinderUIProgress)
        
        template<typename T,
        typename = typename std::enable_if<SCIsWatchNumberable<typename T::type>::value==1,T>::type >
        void setWatch(T num)
        {
            this->removeUpdateFunc();
            const int nID = num->addUpdateFunc([this](T ptrNum,typename T::type newNum,typename T::type oldNum)
                                               {
                                                   if(_pProgressTimer!=NULL && this->getActive())
                                                   {
                                                       _pProgressTimer->setPercentage(newNum);
                                                   }
                                               });
            
            if(_pProgressTimer!=NULL && this->getActive())
            {
                _pProgressTimer->setPercentage((*num));
            }
            
            _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
            {
                SC_RETURN_V_IF(ptr==NULL || nID<=0);
                
                auto p = ptr.cast<T>();
                p->removeUpdateFunc(nID);
            };
            
            _ptrWatch = num;
            _nFuncID = nID;
        }
        
        inline void setProgressTimer(cocos2d::ProgressTimer* pProgress)
        { _pProgressTimer = pProgress; }
        
        virtual void reset() override;
        
    protected:
        SCBinderUIProgress():
        _pProgressTimer(NULL)
        {}
        
        virtual void onActiveChanged(const bool bNewActive) override;
        
    private:
        SCObject::Ptr               _ptrWatchSource;
        cocos2d::ProgressTimer*     _pProgressTimer;
    };
    
}

#endif //__SPEEDCC__SCBINDER_H__
