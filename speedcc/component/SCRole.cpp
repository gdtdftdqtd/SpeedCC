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
        SCASSERT(ptrActor!=NULL);
        SC_RETURN_IF(ptrActor==NULL,false);
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
        SC_RETURN_IF_V(nID<=0);
        
        auto ptrActor = this->getActor(nID);
        if(ptrActor!=NULL)
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
        SC_RETURN_IF(nID<=0, NULL);
        SC_RETURN_IF(this->isActorInRemovedList(nID),NULL);
        
        for(auto it : _actorList)
        {
            if(it->getID()==nID)
            {
                return it;
            }
        }
        
        return NULL;
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
    
    void SCRole::addStrategy(SCStrategy::Ptr ptrStrategy,const bool bInit)
    {
        SCASSERT(ptrStrategy!=NULL);
        SCASSERT(ptrStrategy->getID()>0);
        
        _id2StrategyMap[ptrStrategy->getID()] = ptrStrategy;
        
        if(bInit)
        {
            _nInitStrategyID = ptrStrategy->getID();
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
    
    void SCRole::forEach(const std::function<bool(const SCActor::Ptr& ptrActor)>& func) const
    {
        for(const auto& it : _actorList)
        {
            SC_RETURN_IF_V(!func(it));
        }
    }
    
    void SCRole::forEach(const std::function<bool(SCActor::Ptr& ptrActor)>& func)
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
    
    bool SCRole::filterMsg(SCMessage::Ptr ptrMsg)
    {
        SC_RETURN_IF(!_bFilterMsg, true);
        SC_RETURN_IF(_msgID2FilterCounterMap.empty(), false);
        
        if(ptrMsg->nMsgID==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_IF(_cmd2FilterCounterMap.empty(), false);
            bool bResult = false;
            auto strCommand = ptrMsg->paramters.getValue(MSG_KEY_COMMAND).getString(&bResult);
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
        _bUpdating = true;
        
        do
        {
            SC_BREAK_IF(_actorList.empty());
            SC_BREAK_IF(!this->getActive());
            SC_BREAK_IF(!_pOwnerStage->getActive());
            SC_BREAK_IF(!this->filterMsg(ptrMsg));
            
            for(auto it : _actorList)
            {
                SC_BREAK_IF(!this->getActive());
                SC_BREAK_IF(!_pOwnerStage->getActive());
                it->update(ptrMsg);
            }
        }while(0);
        
        _bUpdating = false;
        
        this->updateVariationActor();
    }
    
}
