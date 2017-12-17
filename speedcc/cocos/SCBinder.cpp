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
        _pLabel->setString(_strLast.c_str());
    }
}
