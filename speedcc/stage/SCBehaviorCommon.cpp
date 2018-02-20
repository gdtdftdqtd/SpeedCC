//
//  SCBehaviorCommon.cpp
//  libspeedcc
//
//  Created by Kevin on 2/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCBehaviorCommon.h"
#include "../cocos/SCCocosDef.h"
#include "../system/SCSystem.h"

namespace SpeedCC
{
    ///----------- SCBehaviorCallFunc
    
    void SCBehaviorCallFunc::execute(const SCDictionary& par)
    {
        SC_RETURN_V_IF(!this->getActive());
        if(_startFunc!=nullptr)
        {
            _startFunc(par);
        }
        else if(_startFunc2!=nullptr)
        {
            _startFunc2();
        }
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<void(const SCDictionary& par)>& func)
    {
        _startFunc = func;
        _startFunc2 = nullptr;
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<void()>& func)
    {
        _startFunc2 = func;
        _startFunc = nullptr;
    }
    
    
    ///----------- SCBehaviorGroup
    
    SCBehaviorGroup::SCBehaviorGroup(SCBehavior::Ptr ptrBvr)
    {
        SCASSERT(ptrBvr!=nullptr);
        this->addBehavior(ptrBvr);
    }
    
    void SCBehaviorGroup::execute(const SCDictionary& par)
    {
        SC_RETURN_V_IF(!this->getActive());
        for(auto it : _behaviorList)
        {
            it->execute(par);
        }
    }
    
    void SCBehaviorGroup::addBehavior(const SCBehavior::Ptr& ptrBvr)
    {
        SC_RETURN_V_IF(ptrBvr==nullptr);
        _behaviorList.push_back(ptrBvr);
    }
    
    void SCBehaviorGroup::removeBehavior(const int nID)
    {
        SC_RETURN_V_IF(nID==0);
        _behaviorList.remove_if([nID](const SCBehavior::Ptr& ptrBvr)
                                {
                                    return (ptrBvr->getID()==nID);
                                });
    }
    
    ///------------- SCBehaviorDelayExecute
    SCBehaviorDelayExecute::~SCBehaviorDelayExecute()
    {
        SCCCScheduler()->unschedule(SCF(onDelayExecute),static_cast<cocos2d::Ref*>(this));
    }
    
    void SCBehaviorDelayExecute::execute(const SCDictionary& par)
    {
        if(!_bPost && _ptrBvr!=nullptr)
        {
            _bPost = true;
            SCCCScheduler()->schedule(SCF(onDelayExecute),static_cast<cocos2d::Ref*>(this),_fDelay,false);
        }
    }
    
    void SCBehaviorDelayExecute::onDelayExecute(float fDelta)
    {
        SCCCScheduler()->unschedule(SCF(onDelayExecute),static_cast<cocos2d::Ref*>(this));
        _bPost = false;
        if(_ptrBvr!=nullptr)
        {
            _ptrBvr->execute();
        }
    }
    
    bool SCBehaviorDelayExecute::setBehavior(SCBehavior::Ptr ptrBvr)
    {
        SC_RETURN_IF(_bPost, false);
        _ptrBvr = ptrBvr;
        return true;
    }
    
    bool SCBehaviorDelayExecute::setDelayTime(const float fDelay)
    {
        SC_RETURN_IF(_bPost, false);
        _fDelay = fDelay;
        _fDelay = _fDelay<0 ? 0 : _fDelay;
        return true;
    }
    
    ///------------ SCBehaviorBoolInvert
    SCBehaviorBoolInvert::SCBehaviorBoolInvert()
    {
        _ptrWatch = SCWatchBool::create();
    }
    
    SCBehaviorBoolInvert::SCBehaviorBoolInvert(const bool bInit)
    {
        _ptrWatch = SCWatchBool::create();
        (*_ptrWatch) = bInit;
    }
    
    SCBehaviorBoolInvert::SCBehaviorBoolInvert(SCWatchBool::Ptr ptrWatch):
    _ptrWatch(ptrWatch)
    {
    }
    
    void SCBehaviorBoolInvert::execute(const SCDictionary& par)
    {
        if(_ptrWatch!=nullptr)
        {
            (*_ptrWatch) = !(*_ptrWatch);
        }
    }
}


