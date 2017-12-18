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
    SCBinderLabel::Ptr SCBinderLabel::create()
    {
        SCBinderLabel::Ptr retPtr;
        
        retPtr.createInstanceWithCon([](void* pData)
                                     {
                                         new(pData)SCBinderLabel();
                                     });
        
        return retPtr;
    }
    
    SCBinderLabel::Ptr SCBinderLabel::create(cocos2d::Label* pLabel)
    {
        SCBinderLabel::Ptr retPtr;
        
        retPtr.createInstanceWithCon([pLabel](void* pData)
                                     {
                                         new(pData)SCBinderLabel(pLabel);
                                     });
        
        return retPtr;
    }
    
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
    
    void SCBinderLabel::setStringSource(SCWatchString::Ptr watchStr)
    {
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
            _pLabel->setString(watchStr->getString().c_str());
        }
        else
        {
            _strLast = watchStr->getString();
        }
    }
}
