//
//  SCBehaviorCommon.cpp
//  libspeedcc
//
//  Created by Kevin on 2/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCBehaviorCommon.h"

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
    
    void SCBehaviorGroup::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        for(auto& it : _behaviorList)
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
    
    ///--------------- SCBehaviorStrategySwitch
    
    void SCBehaviorStrategySwitch::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        SC_RETURN_IF_V(_actorPtr==NULL || _nStragtegyID==0);
        
        auto stragtegy = _actorPtr->getRole()->getStrategy(_nStragtegyID);
        SC_RETURN_IF_V(stragtegy==NULL);
        _actorPtr->applyStrategy(stragtegy.getRawPointer());
    }
    
    ///--------------- SCBehaviorRemoveActor
    
    void SCBehaviorRemoveActor::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        auto roleValue = par.getValue(SC_BVR_ARG_ROLE);
        SC_RETURN_IF_V(!roleValue.isValidObject<SCRole::Ptr>());
        auto actorValue = par.getValue(SC_BVR_ARG_ACTOR);
        SC_RETURN_IF_V(!actorValue.isValidObject<SCActor::Ptr>());
        
        auto rolePtr = roleValue.getObject<SCRole::Ptr>();
        auto actorPtr = actorValue.getObject<SCActor::Ptr>();
        rolePtr->removeActor(actorPtr->getID());
    }
    
    ///--------------- SCBehaviorRoleActive
    void SCBehaviorRoleActive::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        auto actorValue = par.getValue(SC_BVR_ARG_ACTOR);
        SC_RETURN_IF_V(!actorValue.isValidObject<SCActor::Ptr>());
        auto actorPtr = actorValue.getObject<SCActor::Ptr>();
        actorPtr->getRole()->setActive(_bActive);
    }
}


