//
//  SCStrategyCommon.cpp
//  libspeedcc
//
//  Created by Kevin on 2/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCStrategyCommon.h"

namespace SpeedCC
{
    ///----------- SCBehaviorCallFunc
    
    void SCBehaviorCallFunc::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        SC_RETURN_IF_V(_startFunc==NULL);
        _startFunc(par);
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<void(const SCDictionary& par)>& func)
    {
        _startFunc = func;
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
        SC_RETURN_IF_V(_performerPtr==NULL || _nStragtegyID==0);
        
        auto stragtegy = _performerPtr->getRole()->getStrategy(_nStragtegyID);
        SC_RETURN_IF_V(stragtegy==NULL);
        _performerPtr->applyStrategy(stragtegy.getRawPointer());
    }
    
    ///--------------- SCBehaviorRemovePerformer
    
    void SCBehaviorRemovePerformer::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        auto roleValue = par.getValue(SC_BVR_ARG_ROLE);
        SC_RETURN_IF_V(!roleValue.isValidObject<SCRole::Ptr>());
        auto performerValue = par.getValue(SC_BVR_ARG_PERFORMER);
        SC_RETURN_IF_V(!performerValue.isValidObject<SCPerformer::Ptr>());
        
        auto rolePtr = roleValue.getObject<SCRole::Ptr>();
        auto performerPtr = performerValue.getObject<SCPerformer::Ptr>();
        rolePtr->removePerformer(performerPtr->getID());
    }
}


