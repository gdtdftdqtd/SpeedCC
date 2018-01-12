//
//  SCStrategy.hpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSTRATEGY_H__
#define __SPEEDCC__SCSTRATEGY_H__

#include "SCMessage.h"
#include "SCPerformObject.h"

#define SC_BVR_ARG_ACTOR            "actor" // SCActor::Ptr
#define SC_BVR_ARG_STRATEGY         "strategy" // SCStrategy::Ptr
#define SC_BVR_ARG_ROLE             "role" // SCRole::Ptr
#define SC_BVR_ARG_MESSAGE          "message"   // SCMessage::Ptr


namespace SpeedCC
{
    class SCActor;
    
    class SCStrategy : public SCPerformObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategy)
        SC_DEFINE_CLASS_PTR(SCStrategy)
        
        SC_DEFINE_CREATE_FUNC_1(SCStrategy,const int)
        
        virtual void update(SCActor* pActor,SCMessage::Ptr ptrMsg);
        void enter(SCActor* pActor);
        void exit(SCActor* pActor);
        
        bool addBehavior(const int nMsgID,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr=NULL);
        bool addBehavior(const SCString& strCommand,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr=NULL);
        bool addBehavior(SCMessageMatcher::Ptr matcherPtr,SCBehavior::Ptr bvrPtr);
        
        void addEnterBehavior(SCBehavior::Ptr bvrPtr);
        void addExitBehavior(SCBehavior::Ptr bvrPtr);
        
    protected:
        SCStrategy(const int nID):
        SCPerformObject(nID)
        {}
        
    private:
        struct SBehaviorInfo
        {
            SCMessageMatcher::Ptr   ptrMatcher;
            SCBehavior::Ptr         ptrBehavior;
        };
        
    private:
        SCStrategy*                             _pParentStrategy;
        std::list<SCBehavior::Ptr>              _enterBehaviorPtrList;
        std::list<SCBehavior::Ptr>              _exitBehaviorPtrList;
        
        std::map<int,SBehaviorInfo>             _msgID2BehaviorMap;
        std::map<SCString,SBehaviorInfo>        _command2BehaviorMap;
    };
    
    ///------------- SCStrategyEmpty
    class SCStrategyEmpty : public SCStrategy
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategyEmpty)
        SC_DEFINE_CLASS_PTR(SCStrategyEmpty)
        
        SC_DEFINE_CREATE_FUNC_0(SCStrategyEmpty)
        
    protected:
        SCStrategyEmpty():
        SCStrategy(SCID::Stg::kSCStgEmpty)
        {
        }
    };
    
    ///-------------- SCStrategyFunc
    class SCStrategyFunc : public SCStrategy
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategyFunc)
        SC_DEFINE_CLASS_PTR(SCStrategyFunc)
        
        SC_DEFINE_CREATE_FUNC_2(SCStrategyFunc,const int,const std::function<void(SCActor* pActor, SCMessage::Ptr ptrMsg)>&)
        
        virtual void update(SCActor* pActor,SCMessage::Ptr ptrMsg) override;
    protected:
        SCStrategyFunc(const int nID,const std::function<void(SCActor* pActor,SCMessage::Ptr ptrMsg)>& func):
        SCStrategy(nID),
        _func(func)
        {}
        
    private:
        std::function<void(SCActor* pActor,SCMessage::Ptr ptrMsg)>  _func;
    };
}

#endif // __SPEEDCC__SCSTRATEGY_H__
