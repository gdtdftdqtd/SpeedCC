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
    _bFilterMsg(true),
    _bUpdating(false)
    {
    }
    
    bool SCRole::addActor(SCActor::Ptr ptrActor)
    {
        SCASSERT(ptrActor!=nullptr);
        SC_RETURN_IF(ptrActor==nullptr,false);
        const int nID = ptrActor->getID();
        
        if(this->isActorInRemovedList(nID))
        {
            _removeActorList.remove_if([nID](const int id)
                                       {
                                           return (nID==id);
                                       });
            
            _actorList.remove_if([nID](SCActor::Ptr ptrActor)
                                 {
                                     return (ptrActor->getID()==nID);
                                 });
        }
        else
        {
            SC_RETURN_IF(this->hasActor(nID), false);
        }
        
        ptrActor->setRole(this);
        auto strategy = this->getStrategy(_nInitStrategyID);
        ptrActor->applyStrategy(strategy.getRawPointer());
        
        if(_bUpdating)
        {
            _addActorList.push_back(ptrActor);
        }
        else
        {
            _actorList.push_back(ptrActor);
        }
        
        return true;
    }
    
    void SCRole::removeActor(const int nID)
    {
        SC_RETURN_V_IF(nID<=0);
        
        auto ptrActor = this->getActor(nID);
        if(ptrActor!=nullptr)
        {
            if(_bUpdating)
            {
                ptrActor->setActive(false);
                _removeActorList.push_back(nID);
            }
            else
            {
                _actorList.remove_if([nID](SCActor::Ptr ptrActor)
                                     {
                                         return (ptrActor->getID()==nID);
                                     });
            }
        }
    }
    
    bool SCRole::hasActor(const int nID) const
    {
        SC_RETURN_IF(nID<=0, false);
        
        SC_RETURN_IF(this->isActorInRemovedList(nID),false);
        
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
        SC_RETURN_IF(nID<=0, nullptr);
        SC_RETURN_IF(this->isActorInRemovedList(nID),nullptr);
        
        for(auto it : _actorList)
        {
            if(it->getID()==nID)
            {
                return it;
            }
        }
        
        return nullptr;
    }
    
    bool SCRole::isActorInRemovedList(const int nID) const
    {
        SC_RETURN_IF(_removeActorList.empty(), false);
        
        for(const auto& it : _removeActorList)
        {
            SC_RETURN_IF(it==nID, true);
        }
        
        return false;
    }
    
    bool SCRole::setInitStrategyID(const int nID)
    {
        auto it = _id2StrategyInfoMap.find(nID);
        SC_RETURN_IF(it==_id2StrategyInfoMap.end(), false);
        SC_RETURN_IF((*it).second->nParentStrategyID>0, false);
        _nInitStrategyID = nID;
        return true;
    }
    
    void SCRole::addStrategy(SCStrategy::Ptr ptrStrategy,const int nParentID)
    {
        SCASSERT(ptrStrategy!=nullptr);
        SCASSERT(ptrStrategy->getID()>0);
        
        SCStrategyInfo::Ptr ptrSI = SCStrategyInfo::create();
        ptrSI->ptrStrategy = ptrStrategy;
        ptrSI->nParentStrategyID = nParentID;
        _id2StrategyInfoMap[ptrStrategy->getID()] = ptrSI;
    }
    
    SCStrategy::Ptr SCRole::getStrategy(const int nID) const
    {
        SC_RETURN_IF(_id2StrategyInfoMap.empty() || nID<=0, nullptr);
        
        auto it = _id2StrategyInfoMap.find(nID);
        SC_RETURN_IF(it==_id2StrategyInfoMap.end(), nullptr);

        
        return (*it).second->ptrStrategy;
    }
    
    SCStrategyInfo::Ptr SCRole::getStrategyInfo(const int nID) const
    {
        SC_RETURN_IF(_id2StrategyInfoMap.empty() || nID<=0, nullptr);
        
        auto it = _id2StrategyInfoMap.find(nID);
        SC_RETURN_IF(it==_id2StrategyInfoMap.end(), nullptr);
        
        
        return (*it).second;
    }
    
    bool SCRole::hasStrategy(const int nID) const
    {
        SC_RETURN_IF(nID<=0, false);

        return (_id2StrategyInfoMap.find(nID)!=_id2StrategyInfoMap.end());
    }
    
    void SCRole::forEach(const std::function<bool(const SCActor::Ptr& ptrActor)>& func) const
    {
        for(const auto& it : _actorList)
        {
            SC_RETURN_V_IF(!func(it));
        }
    }
    
    void SCRole::forEach(const std::function<bool(SCActor::Ptr& ptrActor)>& func)
    {
        for(auto& it : _actorList)
        {
            SC_RETURN_V_IF(!func(it));
        }
    }
    
    void SCRole::markMsgUnfilter(const int nMsgID)
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
    
    void SCRole::markCmdUnfilter(const SCString& strCmd)
    {
        this->markMsgUnfilter(SCID::Msg::kSCMsgCommand);
        
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
    
    void SCRole::unmarkMsgUnfilter(const int nMsgID)
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
    
    void SCRole::unmarkCmdUnfilter(const SCString& strCmd)
    {
        this->unmarkMsgUnfilter(SCID::Msg::kSCMsgCommand);
        
        auto it = _cmd2FilterCounterMap.find(strCmd);
        if(it!=_cmd2FilterCounterMap.end())
        {
            if(--(*it).second==0)
            {
                _cmd2FilterCounterMap.erase(strCmd);
            }
        }
    }
    
    bool SCRole::isFilterMsg(SCMessage::Ptr ptrMsg)
    {
        SC_RETURN_IF(!_bFilterMsg, true);
        SC_RETURN_IF(_msgID2FilterCounterMap.empty(), false);
        
        if(ptrMsg->nMsgID==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_IF(_cmd2FilterCounterMap.empty(), false);
            bool bResult = false;
            auto strCommand = ptrMsg->parameters.getValue(SC_KEY_COMMAND).getString(&bResult);
            if(bResult && !strCommand.isEmpty())
            {
                return (_cmd2FilterCounterMap.find(strCommand)!=_cmd2FilterCounterMap.end());
            }
        }
        else
        {
            auto it = _msgID2FilterCounterMap.find(ptrMsg->nMsgID);
            return (_msgID2FilterCounterMap.end()!=it);
        }
        
        return true;
    }
    
    bool SCRole::addBehavior2Strategy(const int nStrategyID,
                              const int nMsgID,
                              SCBehavior::Ptr bvrPtr,
                              SCMessageMatcher::Ptr ptrMatcher)
    {
        SCASSERT(nMsgID>0);
        
        auto ptrSI =  this->getStrategyInfo(nStrategyID);
        SC_RETURN_IF(ptrSI==nullptr, false);
        
        auto it = ptrSI->msgID2BehaviorMap.find(nMsgID);
        
        if(it==ptrSI->msgID2BehaviorMap.end())
        {
            SCStrategyInfo::SBehaviorInfo bi;
            bi.ptrBehaviorGroup = SCBehaviorGroup::create();
            bi.ptrBehaviorGroup->addBehavior(bvrPtr);
            bi.ptrMatcher = ptrMatcher;
            
            ptrSI->msgID2BehaviorMap[nMsgID] = bi;
        }
        else
        {
            (*it).second.ptrBehaviorGroup->addBehavior(bvrPtr);
        }
        
        this->markMsgUnfilter(nMsgID);
        
        return true;
    }
    
    bool SCRole::addBehavior2Strategy(const int nStrategyID,
                              const SCString& strCommand,
                              SCBehavior::Ptr bvrPtr,
                              SCMessageMatcher::Ptr ptrMatcher)
    {
        SCASSERT(!strCommand.isEmpty());
        
        auto ptrSI =  this->getStrategyInfo(nStrategyID);
        SC_RETURN_IF(ptrSI==nullptr, false);
        
        auto it = ptrSI->command2BehaviorMap.find(strCommand);
        if(it==ptrSI->command2BehaviorMap.end())
        {
            SCStrategyInfo::SBehaviorInfo bi;
            bi.ptrBehaviorGroup = SCBehaviorGroup::create();
            bi.ptrBehaviorGroup->addBehavior(bvrPtr);
            bi.ptrMatcher = ptrMatcher;
            
            ptrSI->command2BehaviorMap[strCommand] = bi;
        }
        else
        {
            (*it).second.ptrBehaviorGroup->addBehavior(bvrPtr);
        }
        
        this->markCmdUnfilter(strCommand);
        
        return true;
    }
    
    bool SCRole::addBehavior2Strategy(const int nStrategyID,
                              SCMessageMatcher::Ptr ptrMatcher,
                              SCBehavior::Ptr bvrPtr)
    {
        SCASSERT(nStrategyID>0);
        
        bool bRet = false;
        if(ptrMatcher->getMessageID()==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_IF(ptrMatcher->getCommand()<=0,false);
            bRet = this->addBehavior2Strategy(nStrategyID,ptrMatcher->getCommand(),bvrPtr,ptrMatcher);
        }
        else
        {
            bRet = this->addBehavior2Strategy(nStrategyID,ptrMatcher->getMessageID(),bvrPtr,ptrMatcher);
        }
        
        return bRet;
    }
    
    bool SCRole::addEnterBehavior2Strategy(const int nStrategyID,SCBehavior::Ptr bvrPtr)
    {
        auto ptrSI = this->getStrategyInfo(nStrategyID);
        SC_RETURN_IF(ptrSI==nullptr, false);
        
        if(ptrSI->ptrEnterBehavior==nullptr)
        {
            ptrSI->ptrEnterBehavior = SCBehaviorGroup::create();
        }
        
        ptrSI->ptrEnterBehavior->addBehavior(bvrPtr);
        return true;
    }
    
    bool SCRole::addExitBehavior2Strategy(const int nStrategyID,SCBehavior::Ptr bvrPtr)
    {
        auto ptrSI = this->getStrategyInfo(nStrategyID);
        SC_RETURN_IF(ptrSI==nullptr, false);
        
        if(ptrSI->ptrExitBehavior==nullptr)
        {
            ptrSI->ptrExitBehavior = SCBehaviorGroup::create();
        }
        
        ptrSI->ptrExitBehavior->addBehavior(bvrPtr);
        
        return true;
    }
    
    void SCRole::updateVariationActor()
    {
        if(!_removeActorList.empty())
        {
            for(auto it : _removeActorList)
            {
                _actorList.remove_if([it](const SCActor::Ptr ptrActor) -> bool
                                     {
                                         return (ptrActor->getID()==it);
                                     });
            }
            _removeActorList.clear();
        }
        
        if(!_addActorList.empty())
        {
            for(auto it : _addActorList)
            {
                _actorList.push_back(it);
            }
            
            _addActorList.clear();
        }
    }
    
    void SCRole::update(SCMessage::Ptr ptrMsg)
    {
        SCASSERT(ptrMsg!=nullptr);
        _bUpdating = true;
        
        do
        {
            SC_BREAK_IF(_actorList.empty());
            SC_BREAK_IF(!this->getActive());
            SC_BREAK_IF(!_pOwnerStage->getActive());
            SC_BREAK_IF(!this->isFilterMsg(ptrMsg));
            
            for(auto it : _actorList)
            {
                SC_BREAK_IF(!this->getActive());
                SC_BREAK_IF(!_pOwnerStage->getActive());
                it->update(ptrMsg);
                SC_BREAK_IF(!ptrMsg->bContinue);
            }
        }while(0);
        
        _bUpdating = false;
        
        this->updateVariationActor();
    }
    
}
