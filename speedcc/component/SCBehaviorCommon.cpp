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
        SC_RETURN_IF_V(!this->getActive());
        if(_startFunc!=NULL)
        {
            _startFunc(par);
        }
        else if(_startFunc2!=NULL)
        {
            _startFunc2();
        }
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<void(const SCDictionary& par)>& func)
    {
        _startFunc = func;
        _startFunc2 = NULL;
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<void()>& func)
    {
        _startFunc2 = func;
        _startFunc = NULL;
    }
    
    
    ///----------- SCBehaviorGroup
    
    SCBehaviorGroup::SCBehaviorGroup(SCBehavior::Ptr ptrBvr)
    {
        SCASSERT(ptrBvr!=NULL);
        this->addBehavior(ptrBvr);
    }
    
    void SCBehaviorGroup::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        for(auto it : _behaviorList)
        {
            it->execute(par);
        }
    }
    
    void SCBehaviorGroup::addBehavior(const SCBehavior::Ptr& ptrBvr)
    {
        SC_RETURN_IF_V(ptrBvr==NULL);
        _behaviorList.push_back(ptrBvr);
    }
    
    void SCBehaviorGroup::removeBehavior(const int nID)
    {
        SC_RETURN_IF_V(nID==0);
        _behaviorList.remove_if([nID](const SCBehavior::Ptr& ptrBvr)
                                {
                                    return (ptrBvr->getID()==nID);
                                });
    }
    
    ///------------- SCBehaviorDelayExecute
    SCBehaviorDelayExecute::~SCBehaviorDelayExecute()
    {
        SCCCScheduler()->unschedule(SCF(onDelayExecute),this);
    }
    
    void SCBehaviorDelayExecute::execute(const SCDictionary& par)
    {
        if(!_bPost && _ptrBvr!=NULL)
        {
            _bPost = true;
            
            SCCCScheduler()->schedule(SCF(onDelayExecute),this,_fDelay,false);
        }
    }
    
    void SCBehaviorDelayExecute::onDelayExecute(float fDelta)
    {
        SCCCScheduler()->unschedule(SCF(onDelayExecute),this);
        _bPost = false;
        if(_ptrBvr!=NULL)
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
}


