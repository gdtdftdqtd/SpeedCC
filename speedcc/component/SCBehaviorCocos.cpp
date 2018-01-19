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
    ///--------------- SCBehaviorSceneNavigate
    void SCBehaviorSceneNavigate::execute(const SCDictionary& par)
    {
        if(_ptrDelayBvr==NULL)
        {
            auto ptr = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrFunc, this));
            _ptrDelayBvr = SCBehaviorDelayExecute::create(0, ptr);
            _ptrDelayBvr->execute(par);
        }
    }
    
    void SCBehaviorSceneNavigate::setSceneParameter(const SCDictionary& dic)
    {
        _parameterDic = dic;
    }
    
    void SCBehaviorSceneNavigate::onBvrFunc()
    {
        SCSceneNavigator::getInstance()->setSceneParameter(_parameterDic);
        SCSceneNavigator::getInstance()->switchScene(_switch);
        _ptrDelayBvr = NULL;
    }
    
    ///--------------- SCBehaviorSceneBack
    void SCBehaviorSceneBack::execute(const SCDictionary& par)
    {
        if(_ptrDelayBvr==NULL)
        {
            auto ptr = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrFunc, this));
            _ptrDelayBvr = SCBehaviorDelayExecute::create(0, ptr);
            _ptrDelayBvr->execute(par);
        }
    }
    
    void SCBehaviorSceneBack::onBvrFunc()
    {
        SCSceneNavigator::getInstance()->back(_nSceneNum);
        _ptrDelayBvr = NULL;
    }
}
