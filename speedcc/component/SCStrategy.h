//
//  SCStrategy.hpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSTRATEGY_H__
#define __SPEEDCC__SCSTRATEGY_H__

#include "SCMessageDef.h"
#include "SCPerformObject.h"

#define SC_BVR_ARG_PERFORMER    "performer" // SCPerformer::Ptr
#define SC_BVR_ARG_STRATEGY     "strategy" // SCStrategy::Ptr
#define SC_BVR_ARG_ROLE         "role" // SCRole::Ptr
#define SC_BVR_ARG_MESSAGE      "message"   // SCMessage::Ptr


namespace SpeedCC
{
    class SCPerformer;
    
    class SCStrategy : public SCPerformObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategy)
        SC_DEFINE_CLASS_PTR(SCStrategy)
        
        SC_DEFINE_CREATE_FUNC_0(SCStrategy)
        
        virtual void update(SCPerformer* pPerformer,SCMessage::Ptr mi);
        void enter(SCPerformer* pPerformer);
        void exit(SCPerformer* pPerformer);
        
        bool addBehavior(const int nMsgID,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr=NULL);
        bool addBehavior(const SCString& strCommand,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr=NULL);
        bool addBehavior(SCMessageMatcher::Ptr matcherPtr,SCBehavior::Ptr bvrPtr);
        
        void setEnterBehavior(SCBehavior::Ptr bvrPtr);
        void setExitBehavior(SCBehavior::Ptr bvrPtr);
        
    protected:
        SCStrategy()
        {}
        
    private:
        struct SBehaviorInfo
        {
            SCMessageMatcher::Ptr   matcherPtr;
            SCBehavior::Ptr         behaviorPtr;
        };
        
    private:
        SCStrategy*                             _pParentStrategy;
        SCBehavior::Ptr                         _enterBehaviorPtr;
        SCBehavior::Ptr                         _exitBehaviorPtr;
        
        std::map<int,SBehaviorInfo>             _msgID2BehaviorMap;
        std::map<SCString,SBehaviorInfo>        _command2BehaviorMap;
    };
    
    
    class SCStrategyEmpty : public SCStrategy
    {
    public:
//        enum {ID = 1;}
        SC_AVOID_CLASS_COPY(SCStrategyEmpty)
        SC_DEFINE_CLASS_PTR(SCStrategyEmpty)
        
        SC_DEFINE_CREATE_FUNC_0(SCStrategyEmpty)
        
    protected:
        SCStrategyEmpty() {}
    };
}

#endif // __SPEEDCC__SCSTRATEGY_H__
