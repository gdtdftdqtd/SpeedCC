//
//  SCStrategy.cpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCStrategy.h"
#include "SCActor.h"
#include "SCRole.h"

namespace SpeedCC
{
    void SCStrategy::enter(SCActor* pActor)
    {
        SCASSERT(pActor!=NULL);
        SC_RETURN_V_IF(!this->getActive());
        
        auto ptrSI = pActor->getRole()->getStrategyInfo(this->getID());
        SCASSERT(ptrSI!=NULL);
        
        if(ptrSI->ptrEnterBehavior!=NULL)
        {
            SCDictionary dic;
            dic.setValue(SC_KEY_ACTOR, SCValue::create(pActor->makeObjPtr<SCActor::Ptr>()));
            dic.setValue(SC_KEY_STRATEGY, SCValue::create(this->makeObjPtr<SCStrategy::Ptr>()));
            
            ptrSI->ptrEnterBehavior->execute(dic);
        }
    }
    
    void SCStrategy::exit(SCActor* pActor)
    {
        SCASSERT(pActor!=NULL);
        SC_RETURN_V_IF(!this->getActive());
        
        auto ptrSI = pActor->getRole()->getStrategyInfo(this->getID());
        SCASSERT(ptrSI!=NULL);
        
        if(ptrSI->ptrExitBehavior!=NULL)
        {
            SCDictionary dic;
            dic.setValue(SC_KEY_ACTOR, SCValue::create(pActor->makeObjPtr<SCActor::Ptr>()));
            dic.setValue(SC_KEY_STRATEGY, SCValue::create(this->makeObjPtr<SCStrategy::Ptr>()));
            
            ptrSI->ptrExitBehavior->execute(dic);
        }
    }
    
    void SCStrategy::update(SCActor* pActor,SCMessage::Ptr ptrMsg)
    {
        SCASSERT(pActor!=NULL);
        SCASSERT(ptrMsg!=NULL);
        
        SC_RETURN_V_IF(!this->getActive());
        SC_RETURN_V_IF(ptrMsg==NULL);
        SC_RETURN_V_IF(pActor==NULL);
        SC_RETURN_V_IF(pActor->getRole()==NULL);
        
        auto ptrSI = pActor->getRole()->getStrategyInfo(this->getID());
        SCASSERT(ptrSI!=NULL);
        
        SCStrategyInfo::SBehaviorInfo* pBehaviorInfo = NULL;
        
        if(ptrMsg->nMsgID==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_V_IF(ptrSI->command2BehaviorMap.empty());
            
            bool bResult = false;
            auto strCommand = ptrMsg->parameters.getValue(SC_KEY_COMMAND).getString(&bResult);
            if(bResult && !strCommand.isEmpty())
            {
                auto it = ptrSI->command2BehaviorMap.find(strCommand);
                if(it!=ptrSI->command2BehaviorMap.end())
                {
                    pBehaviorInfo = &(*it).second;
                }
            }
        }
        else
        {
            auto it = ptrSI->msgID2BehaviorMap.find(ptrMsg->nMsgID);
            if(it!=ptrSI->msgID2BehaviorMap.end())
            {
                pBehaviorInfo = &(*it).second;
            }
        }
        
        if(pBehaviorInfo!=NULL)
        {
            if(pBehaviorInfo->ptrMatcher!=NULL)
            {
                SC_RETURN_V_IF(!pBehaviorInfo->ptrMatcher->isMatch(ptrMsg));
            }
            SCASSERT(pBehaviorInfo->ptrBehaviorGroup!=NULL);
            SCDictionary dic;
            dic.setValue(SC_KEY_ACTOR, SCValue::create(pActor->makeObjPtr<SCActor::Ptr>()));
            dic.setValue(SC_KEY_STRATEGY, SCValue::create(this->makeObjPtr<SCStrategy::Ptr>()));
            dic.setValue(SC_KEY_MESSAGE,SCValue::create(ptrMsg));
            pBehaviorInfo->ptrBehaviorGroup->execute(dic);
        }
    }
    
    
    ///------------------ SCStrategyFunc
    
    void SCStrategyFunc::update(SCActor* pActor,SCMessage::Ptr ptrMsg)
    {
        if(_func!=NULL)
        {
            _func(pActor,ptrMsg);
        }
        
        SCStrategy::update(pActor,ptrMsg);
    }
    
}
