//
//  SCBehaviorCocos.cpp
//  libspeedcc
//
//  Created by Kevin on 14/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCBehaviorCocos.h"

namespace SpeedCC
{
    ///--------------- SCBehaviorSceneSwitch
    void SCBehaviorSceneSwitch::execute(const SCDictionary& par)
    {
        SCSceneNavigator::getInstance()->setSceneParameter(_parameterDic);
        SCSceneNavigator::getInstance()->switchScene(_switch);
    }
    
    void SCBehaviorSceneSwitch::setSceneParameter(const SCDictionary& dic)
    {
        _parameterDic = dic;
    }
    
    ///--------------- SCBehaviorSceneBack
    void SCBehaviorSceneBack::execute(const SCDictionary& par)
    {
        SCSceneNavigator::getInstance()->back(_nSceneNum);
    }
}
