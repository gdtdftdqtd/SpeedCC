//
//  SCStage.cpp
//  libspeedcc
//
//  Created by Kevin on 26/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCStage.h"

namespace SpeedCC
{
    SCStage::SCStage()
    {
        
    }
    
//    void SCStage::addRole(SCRole::Ptr rolePtr)
//    {
//        
//    }
    
//    void SCStage::addStrategy(SCStrategy::Ptr strategyPtr)
//    {
//
//    }
    
    void SCStage::removeRole(const SCString& strName)
    {
        
    }
    
//    void SCStage::removeStrategy(const SCString& strName)
//    {
//        
//    }
    
    void SCStage::setCreateRoleFun(const std::function<SCRole::Ptr (const SCString& strName)>& fun)
    {
        _createRoleFun = fun;
    }
    
    void SCStage::setCreateStrategyFun(const std::function<SCStrategy::Ptr (const SCString& strName)>& fun)
    {
        _createStrategyFun = fun;
    }
    
    void SCStage::update(SCMessageInfo& mi)
    {
        
    }
    
    void SCStage::setUp()
    {
        
    }
}


