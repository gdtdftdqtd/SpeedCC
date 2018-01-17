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
    void SCBinder::setActive(const bool bActive)
    {
        _bActive = bActive;
        this->onActiveChanged(_bActive);
    }
    
///------------- SCBinderUILabel

    SCBinderUILabel::~SCBinderUILabel()
    {
        this->removeUpdateFunc();
    }
    
    void SCBinderUILabel::removeUpdateFunc()
    {
        if(_removeUpdateFunc!=NULL && _nFuncID>0)
        {
            _removeUpdateFunc(_ptrWatchSource,_nFuncID);
        }
        
        _removeUpdateFunc = NULL;
        _nFuncID = 0;
    }
    
    void SCBinderUILabel::setLabel(cocos2d::Label* pLabel)
    {
        _pLabel = pLabel;
        if(_bActive)
        {
            _pLabel->setString(_strLast.c_str());
        }
    }
    
    void SCBinderUILabel::onActiveChanged(const bool bNewActive)
    {
        if(bNewActive && _pLabel!=NULL)
        {
            _pLabel->setString(_strLast.c_str());
        }
    }
    
    void SCBinderUILabel::setWatchSource(SCWatchString::Ptr watchStr)
    {
        SCASSERT(watchStr!=NULL);
        
        this->removeUpdateFunc();
        
        const int nID = watchStr->addUpdateFunc([this](SCWatchString::Ptr watchPtr,const SCString& strNew,const SCString& strOld)
                                                {
                                                    if(_pLabel!=NULL && _bActive)
                                                    {
                                                        _pLabel->setString(strNew.c_str());
                                                    }
                                                    _strLast = strNew;
                                                });
        
        if(_pLabel!=NULL && _bActive)
        {
            _pLabel->setString(watchStr->getValue().c_str());
        }
        else
        {
            _strLast = watchStr->getValue();
        }
        
        _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
        {
            SC_RETURN_IF_V(ptr==NULL || nID<=0);
            
            auto p = ptr.cast<SCWatchString::Ptr>();
            p->removeUpdateFunc(nID);
        };
        
        _ptrWatchSource = watchStr;
        _nFuncID = nID;
    }
    
    void SCBinderUILabel::reset()
    {
        this->removeUpdateFunc();
        
        _bActive = true;
        _pLabel = NULL;
        _ptrWatchSource = NULL;
    }
    
    ///-----------------
    void SCBinderUIToggle::setWatchSource(SCWatchBool::Ptr ptrWatch)
    {
        
    }
    
    void SCBinderUIToggle::setToggle(cocos2d::MenuItemToggle* pToggle)
    {
        SC_RETURN_IF_V(pToggle==NULL);
        
        _pToggleMenuItem = pToggle;
    }
    
    void SCBinderUIToggle::reset()
    {
        if(_removeUpdateFunc!=NULL && _nFuncID>0)
        {
            _removeUpdateFunc(_ptrWatch,_nFuncID);
        }
        
        _ptrWatch = NULL;
        _pToggleMenuItem = NULL;
        _nFuncID = NULL;
        _removeUpdateFunc = NULL;
    }
    
    /*
    ///-------------- SCBinderSetting
    void SCBinderSetting::setWatchSource(SCWatchString::Ptr watchStr)
    {
        SCASSERT(watchStr!=NULL);
        watchStr->addUpdateFunc([this](SCWatchString::Ptr watchPtr,const SCString& strNew,const SCString& strOld)
                               {
                                   if(_bActive)
                                   {
                                       cocos2d::UserDefault::getInstance()->setStringForKey(_strSettingKey, strNew.c_str());
                                   }
                               });
        
        *watchStr = cocos2d::UserDefault::getInstance()->getStringForKey(_strSettingKey);
    }
    
    void SCBinderSetting::setWatchSource(SCWatchInt::Ptr watchInt,const int nDefault)
    {
        SCASSERT(watchInt!=NULL);
        watchInt->addUpdateFunc([this](SCWatchInt::Ptr watchPtr,const int nNew,const int nOld)
                               {
                                   if(_bActive)
                                   {
                                       cocos2d::UserDefault::getInstance()->setIntegerForKey(_strSettingKey, nNew);
                                   }
                               });
        
        *watchInt = cocos2d::UserDefault::getInstance()->getIntegerForKey(_strSettingKey,nDefault);
    }
    
    void SCBinderSetting::setWatchSource(SCWatchFloat::Ptr watchFloat,const float fDefault)
    {
        SCASSERT(watchFloat!=NULL);
        watchFloat->addUpdateFunc([this](SCWatchFloat::Ptr watchPtr,const float fNew,const float fOld)
                               {
                                   if(_bActive)
                                   {
                                       cocos2d::UserDefault::getInstance()->setFloatForKey(_strSettingKey, fNew);
                                   }
                               });
        
        *watchFloat = cocos2d::UserDefault::getInstance()->getFloatForKey(_strSettingKey,fDefault);
    }
    
    void SCBinderSetting::setWatchSource(SCWatchDouble::Ptr watchDoube,const double dDefault)
    {
        SCASSERT(watchDoube!=NULL);
        watchDoube->addUpdateFunc([this](SCWatchDouble::Ptr watchPtr,const double dNew,const double dOld)
                                 {
                                     if(_bActive)
                                     {
                                         cocos2d::UserDefault::getInstance()->setDoubleForKey(_strSettingKey, dNew);
                                     }
                                 });
        
        *watchDoube = cocos2d::UserDefault::getInstance()->getDoubleForKey(_strSettingKey,dDefault);
    }
    
    void SCBinderSetting::setWatchSource(SCWatchBool::Ptr watchBool,const bool bDefault)
    {
        SCASSERT(watchBool!=NULL);
        watchBool->addUpdateFunc([this](SCWatchDouble::Ptr watchPtr,const bool bNew,const bool bOld)
                                 {
                                     if(_bActive)
                                     {
                                         cocos2d::UserDefault::getInstance()->setBoolForKey(_strSettingKey, bNew);
                                     }
                                 });
        
        *watchBool = cocos2d::UserDefault::getInstance()->getBoolForKey(_strSettingKey,bDefault);
    }
     */
}
