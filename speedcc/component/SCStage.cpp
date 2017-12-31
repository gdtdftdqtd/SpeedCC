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
    
    void SCStage::addRole(SCRole::Ptr rolePtr)
    {
        SCASSERT(rolePtr->getID()>0);
        
        _name2RoleMap[rolePtr->getID()] = rolePtr;
    }
    
    void SCStage::removeRole(const SCString& strName)
    {
        _name2RoleMap.erase(strName);
    }
    
    void SCStage::setCreateRoleFunc(const std::function<SCRole::Ptr (const SCString& strName)>& fun)
    {
        _createRoleFun = fun;
    }
    
    void SCStage::setCreateStrategyFunc(const std::function<SCStrategy::Ptr (const SCString& strName)>& fun)
    {
        _createStrategyFun = fun;
    }
    
    void SCStage::onSCMessageProcess(SCMessageInfo& mi)
    {
        SC_RETURN_IF_V(_name2RoleMap.empty());
        SC_RETURN_IF_V(!this->getActive());
        
        for(auto it : _name2RoleMap)
        {
            SC_RETURN_IF_V(!this->getActive());
            it.second->update(mi);
        }
    }
    
}


