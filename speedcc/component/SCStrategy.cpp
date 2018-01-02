//
//  SCStrategy.cpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCStrategy.h"
#include "SCPerformer.h"

namespace SpeedCC
{
    void SCStrategy::enter(SCPerformer* pPerformer)
    {
        SCASSERT(pPerformer!=NULL);
        SC_RETURN_IF_V(!this->getActive());
        
        if(_enterBehaviorPtr!=NULL)
        {
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_PERFORMER, SCValue::create(pPerformer->makeObjPtr<SCPerformer>()));
            _enterBehaviorPtr->execute(dic);
        }
    }
    
    void SCStrategy::exit(SCPerformer* pPerformer)
    {
        SCASSERT(pPerformer!=NULL);
        SC_RETURN_IF_V(!this->getActive());
        
        if(_exitBehaviorPtr!=NULL)
        {
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_PERFORMER, SCValue::create(pPerformer->makeObjPtr<SCPerformer>()));
            _exitBehaviorPtr->execute(dic);
        }
    }
    
    bool SCStrategy::addBehavior(const int nMsgID,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr)
    {
        SCASSERT(nMsgID>0);
        SCASSERT(bvrPtr!=NULL);
        
        SC_RETURN_IF(nMsgID<=0 || bvrPtr==NULL,false);
        
        SBehaviorInfo bi;
        bi.behaviorPtr = bvrPtr;
        bi.matcherPtr = matcherPtr;
        
        _msgID2BehaviorMap[nMsgID] = bi;
        
        return true;
    }
    
    bool SCStrategy::addBehavior(const SCString& strCommand,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr)
    {
        SCASSERT(!strCommand.isEmpty());
        SCASSERT(bvrPtr!=NULL);
        
        SC_RETURN_IF(strCommand.isEmpty() || bvrPtr==NULL,false);
        
        SBehaviorInfo bi;
        bi.behaviorPtr = bvrPtr;
        bi.matcherPtr = matcherPtr;
        
        _command2BehaviorMap[strCommand] = bi;
        
        return true;
    }
    
    bool SCStrategy::addBehavior(SCMessageMatcher::Ptr matcherPtr,SCBehavior::Ptr bvrPtr)
    {
        SCASSERT(bvrPtr!=NULL);
        SCASSERT(matcherPtr!=NULL);
        
        bool bRet = false;
        if(matcherPtr->getMessageID()==kSCMsgCommand)
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
    
    void SCStrategy::update(SCPerformer* pPerformer,SCMessageInfo& mi)
    {
        SC_RETURN_IF_V(!this->getActive());
        SBehaviorInfo* pBehaviorInfo = NULL;
        
        if(mi.nMsgID==kSCMsgCommand)
        {
            SC_RETURN_IF_V(_command2BehaviorMap.empty());
            
            bool bResult = false;
            auto nCommand = mi.paramters.getValue(MSG_KEY_COMMAND).getInt(&bResult);
            if(bResult && nCommand>0)
            {
                auto it = _command2BehaviorMap.find(nCommand);
                if(it!=_command2BehaviorMap.end())
                {
                    pBehaviorInfo = &(*it).second;
                }
            }
        }
        else
        {
            auto it = _msgID2BehaviorMap.find(mi.nMsgID);
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
            dic.setValue(SC_BVR_ARG_PERFORMER, SCValue::create(pPerformer->makeObjPtr<SCPerformer>()));
            dic.setValue(SC_BVR_ARG_STRATEGY, SCValue::create(this->makeObjPtr<SCStrategy>()));
            pBehaviorInfo->behaviorPtr->execute(dic);
        }
    }
    
}