//
//  SCArgTraits.cpp
//  libspeedcc
//
//  Created by Kevin on 21/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCUIArg.h"
#include "SCSceneController.h"

namespace SpeedCC
{
//    void SCUIMethod::bindLabel(cocos2d::Label* pLabel,SCBinderUILabel::Ptr ptrBinder,SCSceneController* pController)
//    {
//        if(ptrBinder!=NULL && pLabel!=NULL)
//        {
//            ptrBinder->setLabel(pLabel);
//            pController->storeBinder(pLabel,ptrBinder);
//        }
//    }
    
    void SCUIMethod::bindToggle(cocos2d::MenuItemToggle* pToggle,
                    SCBinderUISwitch::Ptr ptrBinder,
                    SCSceneController* pController,
                    const std::function<void(cocos2d::Ref*)>& func)
    {
        if(ptrBinder!=NULL && pToggle!=NULL)
        {
            ptrBinder->setToggle(pToggle);
            pController->storeBinder(pToggle,ptrBinder);
            ptrBinder->setCallback(func);
        }
    }
}


