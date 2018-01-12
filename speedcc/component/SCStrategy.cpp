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
        
        if(!_enterBehaviorPtrList.empty())
        {
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_ACTOR, SCValue::create(pActor->makeObjPtr<SCActor>()));
            dic.setValue(SC_BVR_ARG_STRATEGY, SCValue::create(this->makeObjPtr<SCStrategy>()));

            for(auto it : _enterBehaviorPtrList)
            {
                it->execute(dic);
            }
        }
    }
    
    void SCStrategy::exit(SCActor* pActor)
    {
        SCASSERT(pActor!=NULL);
        SC_RETURN_IF_V(!this->getActive());
        
        if(!_exitBehaviorPtrList.empty())
        {
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_ACTOR, SCValue::create(pActor->makeObjPtr<SCActor>()));
            dic.setValue(SC_BVR_ARG_STRATEGY, SCValue::create(this->makeObjPtr<SCStrategy>()));
            
            for(auto it : _exitBehaviorPtrList)
            {
                it->execute(dic);
            }
        }
    }
    
    // bvrPtr can be NULL
    bool SCStrategy::addBehavior(const int nMsgID,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr)
    {
        SCASSERT(nMsgID>0);
        SC_RETURN_IF(nMsgID<=0 || bvrPtr==NULL,false);
        
        SBehaviorInfo bi;
        bi.ptrBehavior = bvrPtr;
        bi.ptrMatcher = matcherPtr;
        
        _msgID2BehaviorMap[nMsgID] = bi;
        
        return true;
    }
    
    // bvrPtr can be NULL
    bool SCStrategy::addBehavior(const SCString& strCommand,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr)
    {
        SCASSERT(!strCommand.isEmpty());
        SC_RETURN_IF(strCommand.isEmpty(),false);
        
        SBehaviorInfo bi;
        bi.ptrBehavior = bvrPtr;
        bi.ptrMatcher = matcherPtr;
        
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
    
    void SCStrategy::addEnterBehavior(SCBehavior::Ptr bvrPtr)
    {
        SC_RETURN_IF_V(bvrPtr==NULL);
        _enterBehaviorPtrList.push_back(bvrPtr);
    }
    
    void SCStrategy::addExitBehavior(SCBehavior::Ptr bvrPtr)
    {
        SC_RETURN_IF_V(bvrPtr==NULL);
        _exitBehaviorPtrList.push_back(bvrPtr);
    }
    
    void SCStrategy::update(SCActor* pActor,SCMessage::Ptr ptrMsg)
    {
        SC_RETURN_IF_V(!this->getActive());
        SBehaviorInfo* pBehaviorInfo = NULL;
        
        if(ptrMsg->nMsgID==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_IF_V(_command2BehaviorMap.empty());
            
            bool bResult = false;
            auto strCommand = ptrMsg->paramters.getValue(MSG_KEY_COMMAND).getString(&bResult);
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
            auto it = _msgID2BehaviorMap.find(ptrMsg->nMsgID);
            if(it!=_msgID2BehaviorMap.end())
            {
                pBehaviorInfo = &(*it).second;
            }
        }
        
        if(pBehaviorInfo!=NULL)
        {
            if(pBehaviorInfo->ptrMatcher!=NULL)
            {
                SC_RETURN_IF_V(!pBehaviorInfo->ptrMatcher->isMatch(ptrMsg));
            }
            SCASSERT(pBehaviorInfo->ptrBehavior!=NULL);
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_ACTOR, SCValue::create(pActor->makeObjPtr<SCActor>()));
            dic.setValue(SC_BVR_ARG_STRATEGY, SCValue::create(this->makeObjPtr<SCStrategy>()));
            dic.setValue(SC_BVR_ARG_MESSAGE,SCValue::create(ptrMsg));
            pBehaviorInfo->ptrBehavior->execute(dic);
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
