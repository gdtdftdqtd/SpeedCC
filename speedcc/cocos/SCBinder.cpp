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
        if(_pLabel!=NULL && this->getActive())
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
    
    void SCBinderUILabel::setWatch(SCWatchString::Ptr watchStr)
    {
        SCASSERT(watchStr!=NULL);
        
        this->removeUpdateFunc();
        
        const int nID = watchStr->addUpdateFunc([this](SCWatchString::Ptr watchPtr,const SCString& strNew,const SCString& strOld)
                                                {
                                                    if(_pLabel!=NULL && this->getActive())
                                                    {
                                                        _pLabel->setString(strNew.c_str());
                                                    }
                                                    _strLast = strNew;
                                                });
        
        if(_pLabel!=NULL && this->getActive())
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
        SCBinder::reset();
        this->removeUpdateFunc();
        
        _pLabel = NULL;
        _ptrWatchSource = NULL;
    }
    
    ///-----------------
    void SCBinderUIToggle::setWatch(SCWatchBool::Ptr ptrWatch)
    {
        SCASSERT(ptrWatch!=NULL);
        
        this->removeUpdateFunc();
        
        const int nID = ptrWatch->addUpdateFunc([this](SCWatchBool::Ptr ptrWatch, const bool bNew)
                                                {
                                                    this->updateValue2Toggle();
                                                });
        
        if(_pToggleMenuItem!=NULL && this->getActive())
        {
            _pToggleMenuItem->setSelectedIndex(*(ptrWatch) ? 0 : 1);
        }
        
        _removeUpdateFunc = [](SCObject::Ptr ptr,const int nID)
        {
            SC_RETURN_IF_V(ptr==NULL || nID<=0);
            
            auto p = ptr.cast<SCWatchBool::Ptr>();
            p->removeUpdateFunc(nID);
        };
        
        _ptrWatch = ptrWatch;
        _nFuncID = nID;
    }
    
    void SCBinderUIToggle::setToggle(cocos2d::MenuItemToggle* pToggle)
    {
        SC_RETURN_IF_V(pToggle==NULL);
        
        _pToggleMenuItem = pToggle;
        if(_pToggleMenuItem!=NULL)
        {
            _pToggleMenuItem->setCallback(SC_MAKE_FUNC(onMenuItemClicked, this));
        }
        
        this->updateValue2Toggle();
    }
    
    void SCBinderUIToggle::reset()
    {
        SCBinder::reset();
        
        this->removeUpdateFunc();
        
        _ptrWatch = NULL;
        _pToggleMenuItem = NULL;
        _callbackFunc = NULL;
    }
    
    void SCBinderUIToggle::removeUpdateFunc()
    {
        if(_removeUpdateFunc!=NULL && _nFuncID>0)
        {
            _removeUpdateFunc(_ptrWatch,_nFuncID);
        }
        
        _removeUpdateFunc = NULL;
        _nFuncID = 0;
    }
    
    
    void SCBinderUIToggle::onActiveChanged(const bool bNewActive)
    {
        this->updateValue2Toggle();
    }
    
    void SCBinderUIToggle::updateValue2Toggle()
    {
        if(_ptrWatch!=NULL && _pToggleMenuItem!=NULL && this->getActive())
        {
            const int nIndex = (*(_ptrWatch) ? 0 : 1);
            
            if(_pToggleMenuItem->getSelectedIndex()!=nIndex)
            {
                _pToggleMenuItem->setSelectedIndex(nIndex);
            }
        }
    }
    
    void SCBinderUIToggle::onMenuItemClicked(cocos2d::Ref* pSender)
    {
        SC_RETURN_IF_V(_ptrWatch==NULL);
        auto pToggle = dynamic_cast<cocos2d::MenuItemToggle*>(pSender);
        SCASSERT(pToggle!=NULL);
        SC_RETURN_IF_V(pToggle==NULL);
        
        (*_ptrWatch) = (pToggle->getSelectedIndex()==0);
        
        if(_callbackFunc!=NULL)
        {
            _callbackFunc(pSender);
        }
    }
    
    /*
    ///-------------- SCBinderSetting
    void SCBinderSetting::setWatch(SCWatchString::Ptr watchStr)
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
    
    void SCBinderSetting::setWatch(SCWatchInt::Ptr watchInt,const int nDefault)
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
    
    void SCBinderSetting::setWatch(SCWatchFloat::Ptr watchFloat,const float fDefault)
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
    
    void SCBinderSetting::setWatch(SCWatchDouble::Ptr watchDoube,const double dDefault)
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
    
    void SCBinderSetting::setWatch(SCWatchBool::Ptr watchBool,const bool bDefault)
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
