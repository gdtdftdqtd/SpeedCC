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
    SCRole::SCRole(const SCString& strName,SCStage* pStage):
    _pOwnerStage(pStage),
    _nIDCounter(0)
    {
    }
    
    int SCRole::addPerformer(SCPerformer::Ptr performerPtr)
    {
        SCASSERT(performerPtr!=NULL);
        ++_nIDCounter;
        performerPtr->setID(_nIDCounter);
        
        if(_initStrategyPtr!=NULL)
        {
            _initStrategyPtr->enter(performerPtr.getRawPointer());
        }
        return _nIDCounter;
    }
    
    bool SCRole::removePerformer(const int nID)
    {
        bool bRet = false;
        auto it = _id2PerformerPtrMap.find(nID);
        if(it!=_id2PerformerPtrMap.end())
        {
            if(_initStrategyPtr!=NULL)
            {
                _initStrategyPtr->exit((*it).second.getRawPointer());
            }
            
            SCSceneNav()->getCurrentController()->delayExecute(0, [nID,this]()
                                                               {
                                                                   _id2PerformerPtrMap.erase(nID);
                                                               });
            bRet = true;
        }
        
        return bRet;
    }
    
    void SCRole::setInitStrategy(SCStrategy::Ptr strategyPtr)
    {
        _initStrategyPtr = strategyPtr;
    }
    
    void SCRole::addStrategy(SCStrategy::Ptr strategyPtr)
    {
        SCASSERT(strategyPtr!=NULL);
        SCASSERT(strategyPtr->getID()>0);
        
        _name2StrategyMap[strategyPtr->getID()] = strategyPtr;
    }
    
    SCStrategy::Ptr SCRole::getStrategy(const SCString& strName) const
    {
        SC_RETURN_IF(_name2StrategyMap.empty() || strName.isEmpty(), NULL);
        
        auto it = _name2StrategyMap.find(strName);
        SC_RETURN_IF(it==_name2StrategyMap.end(), NULL);
        
        return (*it).second;
    }
    
    void SCRole::forEach(const std::function<bool(const SCPerformer::Ptr& performerPtr)>& func) const
    {
        for(const auto& it : _id2PerformerPtrMap)
        {
            SC_RETURN_IF_V(!func(it.second));
        }
    }
    
    void SCRole::forEach(const std::function<bool(SCPerformer::Ptr& performerPtr)>& func)
    {
        for(auto& it : _id2PerformerPtrMap)
        {
            SC_RETURN_IF_V(!func(it.second));
        }
    }
    
    void SCRole::update(SCMessageInfo& mi)
    {
        SC_RETURN_IF_V(_id2PerformerPtrMap.empty());
        SC_RETURN_IF_V(!this->getActive());
        
        for(auto it : _id2PerformerPtrMap)
        {
            SC_RETURN_IF_V(!this->getActive());
            it.second->update(mi);
        }
    }
    
}
