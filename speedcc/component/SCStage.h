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
        
        void addRole(SCRole::Ptr rolePtr);
        void removeRole(const int nID);
        SCRole::Ptr getRole(const int nID);
        
        virtual void setUp(){}
        virtual SCStrategy::Ptr onCreateStrategy(const int nID) {SCASSERT(false); return NULL;}
        
        virtual void onSCMessageProcess(SCMessageInfo& mi) override;
    private:
        struct SFlowInfo
        {
            SCRole::Ptr                 rolePtr;
            std::list<SCStrategy::Ptr>  strategyPtrList;
        };
        
    protected:
        SCStage();
        
        virtual void onActiveChanged(const bool bNewActive) override;
        
    private:
        std::map<int,SCRole::Ptr>                              _id2RoleMap;
    };
}

#endif // __SPEEDCC__SCSTAGE_H__
