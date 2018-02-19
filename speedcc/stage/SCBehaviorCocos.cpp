//
//  SCBehaviorCocos.cpp
//  libspeedcc
//
//  Created by Kevin on 14/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCBehaviorCocos.h"
#include "../cocos/SCSceneController.h"

namespace SpeedCC
{
    ///--------------- SCBehaviorSceneGoto
    void SCBehaviorSceneGoto::execute(const SCDictionary& par)
    {
        if(_bDirect)
        {
            this->onBvrFunc();
        }
        else if(_ptrDelayBvr==NULL)
        {
            auto ptr = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrFunc, this));
            _ptrDelayBvr = SCBehaviorDelayExecute::create(0, ptr);
            _ptrDelayBvr->addObject(this->makeObjPtr(this));
            _ptrDelayBvr->execute(par);
        }
        
    }
    
    void SCBehaviorSceneGoto::setSceneParameter(const SCDictionary& dic)
    {
        _parameterDic = dic;
    }
    
    void SCBehaviorSceneGoto::onBvrFunc()
    {
        SCSceneNavigator::getInstance()->setSceneParameter(_parameterDic);
        SCSceneNavigator::getInstance()->gotoScene(_switch);
        _ptrDelayBvr = NULL;
    }
    
    ///--------------- SCBehaviorSceneBack
    void SCBehaviorSceneBack::execute(const SCDictionary& par)
    {
        if(_bDirect)
        {
            this->onBvrFunc();
        }
        else if(_ptrDelayBvr==NULL)
        {
            
            auto ptr = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrFunc, this));
            _ptrDelayBvr = SCBehaviorDelayExecute::create(0, ptr);
            _ptrDelayBvr->addObject(this->makeObjPtr(this));
            _ptrDelayBvr->execute(par);
        }
    }
    
    void SCBehaviorSceneBack::onBvrFunc()
    {
        SCSceneNavigator::getInstance()->back(_nSceneNum);
        _ptrDelayBvr = NULL;
    }
    
    ///--------------- SCBehaviorAlertBoxSelected
    SCBehaviorAlertBoxSelected::SCBehaviorAlertBoxSelected():
    _pController(NULL),
    _nSelected(0)
    {
    }
    
    SCBehaviorAlertBoxSelected::SCBehaviorAlertBoxSelected(SCSceneController* pController,const int nSelected):
    _pController(pController),
    _nSelected(nSelected)
    {
    }
    
    void SCBehaviorAlertBoxSelected::setController(SCSceneController* pController)
    {
        _pController = pController;
    }
    
    void SCBehaviorAlertBoxSelected::setSelectedIndex(const int nSelectedIndex)
    {
        _nSelected = nSelectedIndex;
    }
    
    void SCBehaviorAlertBoxSelected::execute(const SCDictionary& par)
    {
        if(_pController!=NULL)
        {
            SCBehaviorSceneBack::create()->execute();
            _pController->finish((void*)(long)_nSelected);
        }
    }
}
