//
//  SCRole.cpp
//  libspeedcc
//
//  Created by Kevin on 28/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCRole.h"
#include "../cocos/SCSceneNavigator.h"

namespace SpeedCC
{
    SCRole::SCRole(const int nID,SCStage* pStage):
    SCPropertyHolder(nID),
    _pOwnerStage(pStage),
    _nInitStrategyID(0),
    _bFilterMsg(true)
    {
        
    }
    
    bool SCRole::addActor(SCActor::Ptr actorPtr)
    {
        SCASSERT(actorPtr!=NULL);
        SC_RETURN_IF(actorPtr==NULL,false);
        SC_RETURN_IF(this->hasActor(actorPtr->getID()), false);
        actorPtr->setRole(this);
        _actorList.push_back(actorPtr);
        auto strategy = this->getStrategy(_nInitStrategyID);
        actorPtr->applyStrategy(strategy.getRawPointer());
        return true;
    }
    
    void SCRole::removeActor(const int nID)
    {
        SC_RETURN_IF_V(nID<=0);
        _actorList.remove_if([nID](const SCActor::Ptr actorPtr) -> bool
                                 {
                                     return (actorPtr->getID()==nID);
                                 });
    }
    
    bool SCRole::hasActor(const int nID) const
    {
        SC_RETURN_IF(nID<=0, false);
        for(auto it : _actorList)
        {
            if(it->getID()==nID)
            {
                return true;
            }
        }
        
        return false;
    }
    
    SCActor::Ptr SCRole::getActor(const int nID)
    {
        SC_RETURN_IF(nID<=0, NULL);
        for(auto it : _actorList)
        {
            if(it->getID()==nID)
            {
                return it;
            }
        }
        
        return NULL;
    }
    
    void SCRole::addStrategy(SCStrategy::Ptr strategyPtr,const bool bInit)
    {
        SCASSERT(strategyPtr!=NULL);
        SCASSERT(strategyPtr->getID()>0);
        
        _id2StrategyMap[strategyPtr->getID()] = strategyPtr;
        
        if(bInit)
        {
            _nInitStrategyID = strategyPtr->getID();
        }
    }
    
    SCStrategy::Ptr SCRole::getStrategy(const int nID) const
    {
        SC_RETURN_IF(_id2StrategyMap.empty() || nID<=0, NULL);
        
        auto it = _id2StrategyMap.find(nID);
        SC_RETURN_IF(it==_id2StrategyMap.end(), NULL);
        
        return (*it).second;
    }
    
    bool SCRole::hasStrategy(const int nID) const
    {
        SC_RETURN_IF(nID<=0, false);
        
        return (_id2StrategyMap.find(nID)!=_id2StrategyMap.end());
    }
    
    void SCRole::forEach(const std::function<bool(const SCActor::Ptr& actorPtr)>& func) const
    {
        for(const auto& it : _actorList)
        {
            SC_RETURN_IF_V(!func(it));
        }
    }
    
    void SCRole::forEach(const std::function<bool(SCActor::Ptr& actorPtr)>& func)
    {
        for(auto& it : _actorList)
        {
            SC_RETURN_IF_V(!func(it));
        }
    }
    
    void SCRole::increaseMsgFilter(const int nMsgID)
    {
        auto it = _msgID2FilterCounterMap.find(nMsgID);
        if(it!=_msgID2FilterCounterMap.end())
        {
            ++(*it).second;
        }
        else
        {
            SCMapInsert(_msgID2FilterCounterMap, nMsgID, 1);
        }
    }
    
    void SCRole::increaseCmdFilter(const SCString& strCmd)
    {
        this->increaseMsgFilter(SCID::Msg::kSCMsgCommand);
        
        auto it = _cmd2FilterCounterMap.find(strCmd);
        if(it!=_cmd2FilterCounterMap.end())
        {
            ++(*it).second;
        }
        else
        {
            SCMapInsert(_cmd2FilterCounterMap, strCmd, 1);
        }
    }
    
    void SCRole::decreaseMsgFilter(const int nMsgID)
    {
        auto it = _msgID2FilterCounterMap.find(nMsgID);
        if(it!=_msgID2FilterCounterMap.end())
        {
            if(--(*it).second==0)
            {
                _msgID2FilterCounterMap.erase(nMsgID);
            }
        }
    }
    
    void SCRole::decreaseCmdFilter(const SCString& strCmd)
    {
        this->decreaseMsgFilter(SCID::Msg::kSCMsgCommand);
        
        auto it = _cmd2FilterCounterMap.find(strCmd);
        if(it!=_cmd2FilterCounterMap.end())
        {
            if(--(*it).second==0)
            {
                _cmd2FilterCounterMap.erase(strCmd);
            }
        }
    }
    
    bool SCRole::filterMsg(SCMessage::Ptr msgPtr)
    {
        SC_RETURN_IF(!_bFilterMsg, true);
        SC_RETURN_IF(_msgID2FilterCounterMap.empty(), false);
        
        if(msgPtr->nMsgID==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_IF(_cmd2FilterCounterMap.empty(), false);
            bool bResult = false;
            auto strCommand = msgPtr->paramters.getValue(MSG_KEY_COMMAND).getString(&bResult);
            if(bResult && !strCommand.isEmpty())
            {
                return (_cmd2FilterCounterMap.find(strCommand)!=_cmd2FilterCounterMap.end());
            }
        }
        else
        {
            auto it = _msgID2FilterCounterMap.find(msgPtr->nMsgID);
            return (_msgID2FilterCounterMap.end()!=it);
        }
        
        return true;
    }
    
    void SCRole::update(SCMessage::Ptr msgPtr)
    {
        SC_RETURN_IF_V(_actorList.empty());
        SC_RETURN_IF_V(!this->getActive());
        SC_RETURN_IF_V(!_pOwnerStage->getActive());
        SC_RETURN_IF_V(!this->filterMsg(msgPtr));
        
        for(auto it : _actorList)
        {
            SC_RETURN_IF_V(!this->getActive());
            SC_RETURN_IF_V(!_pOwnerStage->getActive());
            it->update(msgPtr);
        }
    }
    
}
