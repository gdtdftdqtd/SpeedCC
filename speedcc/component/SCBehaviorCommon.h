//
//  SCBehaviorCommon.hpp
//  libspeedcc
//
//  Created by Kevin on 2/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCBEHAVIORCOMMON_H__
#define __SPEEDCC__SCBEHAVIORCOMMON_H__

#include "SCRole.h"

namespace SpeedCC
{
    
    ///-------------- SCBehaviroCallFunc
    class SCBehaviorCallFunc : public SCBehavior
    {
    protected:
        SCBehaviorCallFunc()
        {}
        
        SCBehaviorCallFunc(const std::function<void(const SCDictionary& par)>& startFunc)
        {
            this->setOnStartFunc(startFunc);
        }
        
        SCBehaviorCallFunc(const std::function<void()>& startFunc)
        {
            this->setOnStartFunc(startFunc);
        }
        
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorCallFunc)
        SC_DEFINE_CLASS_PTR(SCBehaviorCallFunc)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorCallFunc)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorCallFunc,const std::function<void(const SCDictionary& par)>&)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorCallFunc,const std::function<void()>&)
        
        virtual void execute(const SCDictionary& par) override;
        
        void setOnStartFunc(const std::function<void(const SCDictionary& par)>& func);
        void setOnStartFunc(const std::function<void()>& func);
        
    private:
        std::function<void(const SCDictionary& par)>  _startFunc;
        std::function<void()>  _startFunc2;
    };
    
    ///-------------- SCBehaviorGroup
    class SCBehaviorGroup : public SCBehavior
    {
    protected:
        SCBehaviorGroup()
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorGroup)
        SC_DEFINE_CLASS_PTR(SCBehaviorGroup)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorGroup)
        
        virtual void execute(const SCDictionary& par) override;
        
        void addBehavior(const SCBehavior::Ptr& ptrBvr);
        void removeBehavior(const int nID);
        
    private:
        std::list<SCBehavior::Ptr> _behaviorList;
    };
    
    
    ///---------------- SCBehaviorStrategySwitch
    class SCBehaviorStrategySwitch : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorStrategySwitch)
        SC_DEFINE_CLASS_PTR(SCBehaviorStrategySwitch)
        
        SC_DEFINE_CREATE_FUNC_2(SCBehaviorStrategySwitch,SCActor::Ptr,const int)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        SCBehaviorStrategySwitch(SCActor::Ptr actorPtr,const int nStragtegyID):
        _actorPtr(actorPtr),
        _nStragtegyID(nStragtegyID)
        {}
        
    private:
        SCActor::Ptr            _actorPtr;
        int                         _nStragtegyID;
    };
    
    ///----------- SCBehaviorRemoveActor
    class SCBehaviorRemoveActor : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorRemoveActor)
        SC_DEFINE_CLASS_PTR(SCBehaviorRemoveActor)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorRemoveActor)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorRemoveActor,const int)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        // by default, remove all actors from role
        SCBehaviorRemoveActor():
        _nActorID(0)
        {}
        
        SCBehaviorRemoveActor(const int nActorID):
        _nActorID(nActorID)
        {}
        
    private:
        int     _nActorID;
    };
    
    ///----------- SCBehaviorRoleActive
    class SCBehaviorRoleActive : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorRoleActive)
        SC_DEFINE_CLASS_PTR(SCBehaviorRoleActive)
        
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorRoleActive,bool)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        SCBehaviorRoleActive()
        {}
        
        SCBehaviorRoleActive(const bool bActive):
        _bActive(bActive)
        {
        }
        
    private:
        bool        _bActive;
    };
}

#endif // __SPEEDCC__SCBEHAVIORCOMMON_H__
