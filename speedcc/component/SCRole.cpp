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
    SCComponentHolder(nID),
    _pOwnerStage(pStage),
    _nInitStrategyID(0)
    {
        
    }
    
    bool SCRole::addPerformer(SCPerformer::Ptr performerPtr)
    {
        SCASSERT(performerPtr!=NULL);
        SC_RETURN_IF(performerPtr==NULL,false);
        SC_RETURN_IF(this->hasPerformer(performerPtr->getID()), false);
        _performerList.push_back(performerPtr);
        auto strategy = this->getStrategy(_nInitStrategyID);
        performerPtr->applyStrategy(strategy.getRawPointer());
        return true;
    }
    
    void SCRole::removePerformer(const int nID)
    {
        SC_RETURN_IF_V(nID<=0);
        _performerList.remove_if([nID](const SCPerformer::Ptr performerPtr) -> bool
                                 {
                                     return (performerPtr->getID()==nID);
                                 });
    }
    
    bool SCRole::hasPerformer(const int nID) const
    {
        SC_RETURN_IF(nID<=0, false);
        for(auto it : _performerList)
        {
            if(it->getID()==nID)
            {
                return true;
            }
        }
        
        return false;
    }
    
    SCPerformer::Ptr SCRole::getPerformer(const int nID)
    {
        SC_RETURN_IF(nID<=0, NULL);
        for(auto it : _performerList)
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
    
    void SCRole::forEach(const std::function<bool(const SCPerformer::Ptr& performerPtr)>& func) const
    {
        for(const auto& it : _performerList)
        {
            SC_RETURN_IF_V(!func(it));
        }
    }
    
    void SCRole::forEach(const std::function<bool(SCPerformer::Ptr& performerPtr)>& func)
    {
        for(auto& it : _performerList)
        {
            SC_RETURN_IF_V(!func(it));
        }
    }
    
    void SCRole::update(SCMessageInfo& mi)
    {
        SC_RETURN_IF_V(_performerList.empty());
        SC_RETURN_IF_V(!this->getActive());
        SC_RETURN_IF_V(!_pOwnerStage->getActive());
        
        for(auto it : _performerList)
        {
            SC_RETURN_IF_V(!this->getActive());
            SC_RETURN_IF_V(!_pOwnerStage->getActive());
            it->update(mi);
        }
    }
    
}
