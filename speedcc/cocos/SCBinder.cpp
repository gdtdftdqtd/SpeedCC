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
    
///------------- SCBinderLabel

    void SCBinderLabel::setLabel(cocos2d::Label* pLabel)
    {
        _pLabel = pLabel;
        if(_bActive)
        {
            _pLabel->setString(_strLast.c_str());
        }
    }
    
    void SCBinderLabel::onActiveChanged(const bool bNewActive)
    {
        if(bNewActive && _pLabel!=NULL)
        {
            _pLabel->setString(_strLast.c_str());
        }
    }
    
    void SCBinderLabel::setWatchSource(SCWatchString::Ptr watchStr)
    {
        SCASSERT(watchStr!=NULL);
        watchStr->addUpdateFun([this](SCWatchString::Ptr watchPtr,const SCString& strNew,const SCString& strOld)
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
        
        _ptrWatchSource = watchStr;
    }
    
    void SCBinderLabel::reset()
    {
        _bActive = true;
        _pLabel = NULL;
        _ptrWatchSource = NULL;
    }
    
    /*
    ///-------------- SCBinderSetting
    void SCBinderSetting::setWatchSource(SCWatchString::Ptr watchStr)
    {
        SCASSERT(watchStr!=NULL);
        watchStr->addUpdateFun([this](SCWatchString::Ptr watchPtr,const SCString& strNew,const SCString& strOld)
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
        watchInt->addUpdateFun([this](SCWatchInt::Ptr watchPtr,const int nNew,const int nOld)
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
        watchFloat->addUpdateFun([this](SCWatchFloat::Ptr watchPtr,const float fNew,const float fOld)
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
        watchDoube->addUpdateFun([this](SCWatchDouble::Ptr watchPtr,const double dNew,const double dOld)
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
        watchBool->addUpdateFun([this](SCWatchDouble::Ptr watchPtr,const bool bNew,const bool bOld)
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
