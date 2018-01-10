//
//  SCStrategy.cpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCStrategy.h"
#include "SCActor.h"

namespace SpeedCC
{
    void SCStrategy::enter(SCActor* pActor)
    {
        SCASSERT(pActor!=NULL);
        SC_RETURN_IF_V(!this->getActive());
        
        if(_enterBehaviorPtr!=NULL)
        {
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_ACTOR, SCValue::create(pActor->makeObjPtr<SCActor>()));
            _enterBehaviorPtr->execute(dic);
        }
    }
    
    void SCStrategy::exit(SCActor* pActor)
    {
        SCASSERT(pActor!=NULL);
        SC_RETURN_IF_V(!this->getActive());
        
        if(_exitBehaviorPtr!=NULL)
        {
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_ACTOR, SCValue::create(pActor->makeObjPtr<SCActor>()));
            _exitBehaviorPtr->execute(dic);
        }
    }
    
    // bvrPtr can be NULL
    bool SCStrategy::addBehavior(const int nMsgID,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr)
    {
        SCASSERT(nMsgID>0);
        SC_RETURN_IF(nMsgID<=0 || bvrPtr==NULL,false);
        
        SBehaviorInfo bi;
        bi.behaviorPtr = bvrPtr;
        bi.matcherPtr = matcherPtr;
        
        _msgID2BehaviorMap[nMsgID] = bi;
        
        return true;
    }
    
    // bvrPtr can be NULL
    bool SCStrategy::addBehavior(const SCString& strCommand,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr)
    {
        SCASSERT(!strCommand.isEmpty());
        SC_RETURN_IF(strCommand.isEmpty(),false);
        
        SBehaviorInfo bi;
        bi.behaviorPtr = bvrPtr;
        bi.matcherPtr = matcherPtr;
        
        _command2BehaviorMap[strCommand] = bi;
        
        return true;
    }
    
    // bvrPtr can be NULL
    bool SCStrategy::addBehavior(SCMessageMatcher::Ptr matcherPtr,SCBehavior::Ptr bvrPtr)
    {
        SCASSERT(matcherPtr!=NULL);
        
        bool bRet = false;
        if(matcherPtr->getMessageID()==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_IF(matcherPtr->getCommand()<=0,false);
            bRet = this->addBehavior(matcherPtr->getCommand(),bvrPtr,matcherPtr);
        }
        else
        {
            bRet = this->addBehavior(matcherPtr->getMessageID(),bvrPtr,matcherPtr);
        }
        
        return bRet;
    }
    
    void SCStrategy::setEnterBehavior(SCBehavior::Ptr bvrPtr)
    {
        _enterBehaviorPtr = bvrPtr;
    }
    
    void SCStrategy::setExitBehavior(SCBehavior::Ptr bvrPtr)
    {
        _exitBehaviorPtr = bvrPtr;
    }
    
    void SCStrategy::update(SCActor* pActor,SCMessage::Ptr mi)
    {
        SC_RETURN_IF_V(!this->getActive());
        SBehaviorInfo* pBehaviorInfo = NULL;
        
        if(mi->nMsgID==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_IF_V(_command2BehaviorMap.empty());
            
            bool bResult = false;
            auto strCommand = mi->paramters.getValue(MSG_KEY_COMMAND).getString(&bResult);
            if(bResult && !strCommand.isEmpty())
            {
                auto it = _command2BehaviorMap.find(strCommand);
                if(it!=_command2BehaviorMap.end())
                {
                    pBehaviorInfo = &(*it).second;
                }
            }
        }
        else
        {
            auto it = _msgID2BehaviorMap.find(mi->nMsgID);
            if(it!=_msgID2BehaviorMap.end())
            {
                pBehaviorInfo = &(*it).second;
            }
        }
        
        if(pBehaviorInfo!=NULL)
        {
            if(pBehaviorInfo->matcherPtr!=NULL)
            {
                SC_RETURN_IF_V(!pBehaviorInfo->matcherPtr->isMatch(mi));
            }
            SCASSERT(pBehaviorInfo->behaviorPtr!=NULL);
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_ACTOR, SCValue::create(pActor->makeObjPtr<SCActor>()));
            dic.setValue(SC_BVR_ARG_STRATEGY, SCValue::create(this->makeObjPtr<SCStrategy>()));
            dic.setValue(SC_BVR_ARG_MESSAGE,SCValue::create(mi));
            pBehaviorInfo->behaviorPtr->execute(dic);
        }
    }
    
    
    ///------------------ SCStrategyFunc
    
    void SCStrategyFunc::update(SCActor* pActor,SCMessage::Ptr msgPtr)
    {
        if(_func!=NULL)
        {
            _func(pActor,msgPtr);
        }
        
        SCStrategy::update(pActor,msgPtr);
    }
    
}
