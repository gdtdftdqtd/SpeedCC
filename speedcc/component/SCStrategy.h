//
//  SCStrategy.hpp
//  libspeedcc
//
//  Created by Kevin on 27/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSTRATEGY_H__
#define __SPEEDCC__SCSTRATEGY_H__

#include "SCBehavior.h"
#include "SCMessageDef.h"

#define SC_BVR_ARG_PERFORMER    "performer"
#define SC_BVR_ARG_STRATEGY     "strategy"


namespace SpeedCC
{
    class SCPerformer;
    
    class SCStrategy : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategy)
        SC_DEFINE_CLASS_PTR(SCStrategy)
        
        SC_DEFINE_CREATE_FUNC0(SCStrategy)
        
        virtual void update(SCPerformer* pPerformer,SCMessageInfo& mi);
        void enter(SCPerformer* pPerformer);
        void exit(SCPerformer* pPerformer);
        
//        bool addStrategy(SCStrategy::Ptr strategyPtr);
//        SCStrategy::Ptr getStrategy(const int nID) const;
        
        bool addBehavior(const int nMsgID,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr=NULL);
        bool addBehaviorWithCommand(const int nCommand,SCBehavior::Ptr bvrPtr,SCMessageMatcher::Ptr matcherPtr=NULL);
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
//        std::map<SCString,SCStrategy::Ptr>      _name2ChildStrategyMap;
        
        std::map<int,SBehaviorInfo>             _msgID2BehaviorMap;
        std::map<int,SBehaviorInfo>             _userCommand2BehaviorMap;
    };
    
    
    class SCStrategyEmpty : public SCStrategy
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategyEmpty)
        SC_DEFINE_CLASS_PTR(SCStrategyEmpty)
        
        SC_DEFINE_CREATE_FUNC0(SCStrategyEmpty)
        
    protected:
        SCStrategyEmpty() {}
    };
}

#endif // __SPEEDCC__SCSTRATEGY_H__
