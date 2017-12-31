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
        SC_RETURN_IF_V(this->getState()!=SCBehavior::RUNNING);
        
        if(_enterBehaviorPtr!=NULL)
        {
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_PERFORMER, SCValue::create(pPerformer->makeObjPtr<SCPerformer>()));
            _enterBehaviorPtr->start(dic);
        }
    }
    
    void SCStrategy::exit(SCPerformer* pPerformer)
    {
        SCASSERT(pPerformer!=NULL);
        SC_RETURN_IF_V(this->getState()!=SCBehavior::RUNNING);
        
        if(_exitBehaviorPtr!=NULL)
        {
            SCDictionary dic;
            dic.setValue(SC_BVR_ARG_PERFORMER, SCValue::create(pPerformer->makeObjPtr<SCPerformer>()));
            _exitBehaviorPtr->start(dic);
        }
    }
    
//    bool SCStrategy::addStrategy(SCStrategy::Ptr strategyPtr)
//    {
//        SCASSERT(strategyPtr!=NULL);
//        SC_RETURN_IF(strategyPtr==NULL || strategyPtr->getID()<=0,false);
//
//        _name2ChildStrategyMap[strategyPtr->getID()] = strategyPtr;
//        return true;
//    }
//
//    SCStrategy::Ptr SCStrategy::getStrategy(const int nID) const
//    {
//        SC_RETURN_IF(_name2ChildStrategyMap.empty() || nID<=0, NULL);
//
//        auto it = _name2ChildStrategyMap.find(nID);
//        SC_RETURN_IF(it==_name2ChildStrategyMap.end(), NULL);
//
//        return (*it).second;
//    }
    
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
    
    bool SCStrategy::addBehaviorWithCommand(const int nCommand,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr)
    {
        SCASSERT(nCommand>0);
        SCASSERT(bvrPtr!=NULL);
        
        SC_RETURN_IF(nCommand<=0 || bvrPtr==NULL,false);
        
        SBehaviorInfo bi;
        bi.behaviorPtr = bvrPtr;
        bi.matcherPtr = matcherPtr;
        
        _userCommand2BehaviorMap[nCommand] = bi;
        
        return true;
    }
    
    bool SCStrategy::addBehavior(SCMessageMatcher::Ptr matcherPtr,SCBehavior::Ptr bvrPtr)
    {
        SCASSERT(bvrPtr!=NULL);
        SCASSERT(matcherPtr!=NULL);
        
        bool bRet = false;
        if(matcherPtr->getMessageID()==kSCMsgUserCommand)
        {
            SC_RETURN_IF(matcherPtr->getCommand()<=0,false);
            bRet = this->addBehaviorWithCommand(matcherPtr->getCommand(),bvrPtr,matcherPtr);
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
        SC_RETURN_IF_V(this->getState()!=SCBehavior::RUNNING);
        SBehaviorInfo* pBehaviorInfo = NULL;
        
        if(mi.nMsgID==kSCMsgUserCommand)
        {
            SC_RETURN_IF_V(_userCommand2BehaviorMap.empty());
            
            bool bResult = false;
            auto nCommand = mi.paramters.getValue(MSG_KEY_COMMAND).getInt(&bResult);
            if(bResult && nCommand>0)
            {
                auto it = _userCommand2BehaviorMap.find(nCommand);
                if(it!=_userCommand2BehaviorMap.end())
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
            pBehaviorInfo->behaviorPtr->start(dic);
        }
    }
    
}
