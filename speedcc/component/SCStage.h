//
//  SCStage.hpp
//  libspeedcc
//
//  Created by Kevin on 26/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSTAGE_H__
#define __SPEEDCC__SCSTAGE_H__

//#include "SCStrategy.h"
#include "SCRole.h"
#include "SCMessageDef.h"

namespace SpeedCC
{
    class SCStage : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCStage)
        SC_DEFINE_CLASS_PTR(SCStage)
        
//        void addRole(SCRole::Ptr rolePtr);
//        void addStrategy(SCStrategy::Ptr strategyPtr);
        
        void removeRole(const SCString& strName);
//        void removeStrategy(const SCString& strName);
        
        void setCreateRoleFun(const std::function<SCRole::Ptr (const SCString& strName)>& fun);
        void setCreateStrategyFun(const std::function<SCStrategy::Ptr (const SCString& strName)>& fun);
        
//        SCRole::Ptr getRole(const SCString& );
        
        virtual void update(SCMessageInfo& mi);
        virtual void setUp();
        
    private:
        struct SFlowInfo
        {
            SCRole::Ptr                 rolePtr;
            std::list<SCStrategy::Ptr>  strategyPtrList;
        };
        
    protected:
        SCStage();
        
    private:
        std::map<SCString,SCRole::Ptr>          _name2RoleMap;
        
        std::function<SCRole::Ptr (const SCString& strName)>        _createRoleFun;
        std::function<SCStrategy::Ptr (const SCString& strName)>    _createStrategyFun;
    };
}

#endif // __SPEEDCC__SCSTAGE_H__
