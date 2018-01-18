//
//  SCStage.cpp
//  libspeedcc
//
//  Created by Kevin on 26/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCStage.h"
#include "SCMessageDispatch.h"

namespace SpeedCC
{
    SCStage::SCStage()
    {
        SCMessageDispatch::getInstance()->addListener(this);
    }
    
    SCStage::~SCStage()
    {
        SCMessageDispatch::getInstance()->removeListener(this);
    }
    
    void SCStage::addRole(SCRole::Ptr ptrRole)
    {
        SCASSERT(ptrRole!=NULL);
        SCASSERT(ptrRole->getID()>0);
        
        _id2RoleMap[ptrRole->getID()] = ptrRole;
    }
    
    void SCStage::removeRole(const int nID)
    {
        _id2RoleMap.erase(nID);
    }
    
    SCRole::Ptr SCStage::getRole(const int nID)
    {
        SC_RETURN_IF(nID<=0,NULL);
        
        auto it = _id2RoleMap.find(nID);
        SC_RETURN_IF(it==_id2RoleMap.end(),NULL);
        return (*it).second;
    }
    
    void SCStage::onSCMessageProcess(SCMessage::Ptr ptrMsg)
    {
        SCASSERT(ptrMsg!=NULL);
        SC_RETURN_IF_V(_id2RoleMap.empty());
        SC_RETURN_IF_V(!this->getActive());
        
        for(auto it : _id2RoleMap)
        {
            SC_RETURN_IF_V(!this->getActive());
            SC_BREAK_IF(!ptrMsg->bContinue);
            it.second->update(ptrMsg);
        }
    }
    
    void SCStage::onActiveChanged(const bool bNewActive)
    {
        
    }
}


