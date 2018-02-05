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
        SC_RETURN_V_IF(!this->getActive());
        SC_RETURN_V_IF(_nStragtegyID==0);
        auto actorValue = par.getValue(SC_KEY_ACTOR);
        SC_RETURN_V_IF(!actorValue.isValidObject<SCActor::Ptr>());
        
        auto ptrActor = actorValue.getObject<SCActor::Ptr>();
        
        auto stragtegy = ptrActor->getRole()->getStrategy(_nStragtegyID);
        SC_RETURN_V_IF(stragtegy==NULL);
        
        ptrActor->applyStrategy(stragtegy.getRawPointer());
    }
    
    ///--------------- SCBehaviorRemoveActor
    
    void SCBehaviorRemoveActor::execute(const SCDictionary& par)
    {
        SC_RETURN_V_IF(!this->getActive());
        auto actorValue = par.getValue(SC_KEY_ACTOR);
        SC_RETURN_V_IF(!actorValue.isValidObject<SCActor::Ptr>());
        
        auto ptrActor = actorValue.getObject<SCActor::Ptr>();
        if(_nActorID==0)
        {// remove all actors
            ptrActor->removeFromRole();
        }
        else if(_nActorID==ptrActor->getID())
        {
            ptrActor->removeFromRole();
        }
    }
    
    ///--------------- SCBehaviorRoleActive
    void SCBehaviorRoleActive::execute(const SCDictionary& par)
    {
        auto actorValue = par.getValue(SC_KEY_ACTOR);
        SC_RETURN_V_IF(!actorValue.isValidObject<SCActor::Ptr>());
        auto ptrActor = actorValue.getObject<SCActor::Ptr>();
        
        if(_nRoleID==0 || _nRoleID==ptrActor->getRole()->getID())
        {
            ptrActor->getRole()->setActive(_bActive);
        }
        else
        {
            ptrActor->getRole()->getStage()->getRole(_nRoleID)->setActive(_bActive);
        }
    }
}
