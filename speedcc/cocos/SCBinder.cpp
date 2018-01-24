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
            SC_RETURN_V_IF(ptr==NULL || nID<=0);
            
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
    SCBinderUISwitch::~SCBinderUISwitch()
    {
        this->removeUpdateFunc();
    }
    
    void SCBinderUISwitch::setWatch(SCWatchBool::Ptr ptrWatch)
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
            SC_RETURN_V_IF(ptr==NULL || nID<=0);
            
            auto p = ptr.cast<SCWatchBool::Ptr>();
            SCASSERT(p!=NULL);
            p->removeUpdateFunc(nID);
        };
        
        _ptrWatch = ptrWatch;
        _nFuncID = nID;
    }
    
    void SCBinderUISwitch::setToggle(cocos2d::MenuItemToggle* pToggle)
    {
        SC_RETURN_V_IF(pToggle==NULL);
        
        _pToggleMenuItem = pToggle;
        if(_pToggleMenuItem!=NULL)
        {
            _pToggleMenuItem->setCallback(SC_MAKE_FUNC(onMenuItemClicked, this));
        }
        
        this->updateValue2Toggle();
    }
    
    void SCBinderUISwitch::reset()
    {
        SCBinder::reset();
        
        this->removeUpdateFunc();
        
        _ptrWatch = NULL;
        _pToggleMenuItem = NULL;
        _callbackFunc = NULL;
    }
    
    void SCBinderUISwitch::removeUpdateFunc()
    {
        if(_removeUpdateFunc!=NULL && _nFuncID>0)
        {
            _removeUpdateFunc(_ptrWatch,_nFuncID);
        }
        
        _removeUpdateFunc = NULL;
        _nFuncID = 0;
    }
    
    
    void SCBinderUISwitch::onActiveChanged(const bool bNewActive)
    {
        this->updateValue2Toggle();
    }
    
    void SCBinderUISwitch::updateValue2Toggle()
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
    
    void SCBinderUISwitch::onMenuItemClicked(cocos2d::Ref* pSender)
    {
        SC_RETURN_V_IF(_ptrWatch==NULL);
        auto pToggle = dynamic_cast<cocos2d::MenuItemToggle*>(pSender);
        SCASSERT(pToggle!=NULL);
        SC_RETURN_V_IF(pToggle==NULL);
        
        (*_ptrWatch) = (pToggle->getSelectedIndex()==0);
        
        if(_callbackFunc!=NULL)
        {
            _callbackFunc(pSender);
        }
    }
    
}
