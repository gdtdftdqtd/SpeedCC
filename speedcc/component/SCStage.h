//
//  SCStage.hpp
//  libspeedcc
//
//  Created by Kevin on 26/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSTAGE_H__
#define __SPEEDCC__SCSTAGE_H__

#include "SCPerformObject.h"
#include "SCRole.h"
#include "SCMessageDef.h"
#include "SCMessageDispatch.h"

namespace SpeedCC
{
    class SCStage :
    public SCPerformObject,
    public SCMessageListener
    {
    public:
        SC_AVOID_CLASS_COPY(SCStage)
        SC_DEFINE_CLASS_PTR(SCStage)
        
        SC_DEFINE_CREATE_FUNC0(SCStage)
        
        virtual ~SCStage();
        
        void removeRole(const SCString& strName);
        
        void setCreateRoleFunc(const std::function<SCRole::Ptr (const SCString& strName)>& fun);
        void setCreateStrategyFunc(const std::function<SCStrategy::Ptr (const SCString& strName)>& fun);
        
        void addRole(SCRole::Ptr rolePtr);
        virtual void setUp(){}
        
        virtual void onSCMessageProcess(SCMessageInfo& mi);
    private:
        struct SFlowInfo
        {
            SCRole::Ptr                 rolePtr;
            std::list<SCStrategy::Ptr>  strategyPtrList;
        };
        
    protected:
        SCStage();
        
    private:
        std::map<SCString,SCRole::Ptr>                              _name2RoleMap;
        
        std::function<SCRole::Ptr (const SCString& strName)>        _createRoleFun;
        std::function<SCStrategy::Ptr (const SCString& strName)>    _createStrategyFun;
    };
}

#endif // __SPEEDCC__SCSTAGE_H__
