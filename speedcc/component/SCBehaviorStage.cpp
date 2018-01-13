//
//  SCBehaviorStage.cpp
//  libspeedcc
//
//  Created by Kevin on 13/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCBehaviorStage.h"
#include "SCStage.h"

namespace SpeedCC
{
    ///--------------- SCBehaviorStrategySwitch
    
    void SCBehaviorStrategySwitch::execute(const SCDictionary& par)
    {
        SC_RETURN_IF_V(!this->getActive());
        SC_RETURN_IF_V(_ptrActor==NULL || _nStragtegyID==0);
        
        auto stragtegy = _ptrActor->getRole()->getStrategy(_nStragtegyID);
        SC_RETURN_IF_V(stragtegy==NULL);
        _ptrActor->applyStrategy(stragtegy.getRawPointer());
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
        if(_nActorID==0)
        {// remove all actors
            actorPtr->removeFromRole();
        }
        else if(_nActorID==actorPtr->getID())
        {
            actorPtr->removeFromRole();
        }
    }
    
    ///--------------- SCBehaviorRoleActive
    void SCBehaviorRoleActive::execute(const SCDictionary& par)
    {
        auto actorValue = par.getValue(SC_BVR_ARG_ACTOR);
        SC_RETURN_IF_V(!actorValue.isValidObject<SCActor::Ptr>());
        auto actorPtr = actorValue.getObject<SCActor::Ptr>();
        
        if(_nRoleID==0 || _nRoleID==actorPtr->getRole()->getID())
        {
            actorPtr->getRole()->setActive(_bActive);
        }
        else
        {
            actorPtr->getRole()->getStage()->getRole(_nRoleID)->setActive(_bActive);
        }
    }
}
