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
#include "SCMessage.h"
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
        
        SC_DEFINE_CREATE_FUNC_0(SCStage)
        
        virtual ~SCStage();
        
        void addRole(SCRole::Ptr rolePtr);
        void removeRole(const int nID);
        SCRole::Ptr getRole(const int nID);
        
        virtual void setUp(){}
        virtual SCStrategy::Ptr onCreateStrategy(const int nID) {SCASSERT(false); return NULL;}
        virtual void onSCMessageProcess(SCMessage::Ptr msgPtr) override;
        
        template<typename T1,typename T2,typename ...Ts>
        void createActorToRole(const int nRoleID,const int nActorID=SCActor::kDefaultID)
        {
            auto actor = SCActor::create(nActorID);
            actor->addProperty<T1,T2,Ts...>();
            auto role = this->getRole(nRoleID);
            role->addActor(actor);
        }
        
        template<typename T>
        void createActorToRole(const int nRoleID,const int nActorID=SCActor::kDefaultID)
        {
            auto actor = SCActor::create(nActorID);
            actor->addProperty<T>();
            auto role = this->getRole(nRoleID);
            role->addActor(actor);
        }
        
        template<typename T1,typename T2,typename ...Ts>
        void createActorToRole(const int nRoleID,const int nActorID,const T1& t1,const T2& t2,Ts... ts)
        {
            auto actor = SCActor::create(nActorID);
            actor->addProperty<T1,T2,Ts...>(t1,t2,ts...);
            auto role = this->getRole(nRoleID);
            role->addActor(actor);
        }
        
        template<typename T>
        void createActorToRole(const int nRoleID,const int nActorID,const T& t)
        {
            auto actor = SCActor::create(nActorID);
            actor->addProperty<T>(t);
            auto role = this->getRole(nRoleID);
            role->addActor(actor);
        }
        
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
