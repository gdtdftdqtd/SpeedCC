//
//  SCStrategyCommon.hpp
//  libspeedcc
//
//  Created by Kevin on 2/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSTRATEGYCOMMON_H__
#define __SPEEDCC__SCSTRATEGYCOMMON_H__

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
        
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorCallFunc)
        SC_DEFINE_CLASS_PTR(SCBehaviorCallFunc)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorCallFunc)
        SC_DEFINE_CREATE_FUNC_1(SCBehaviorCallFunc,const std::function<void(const SCDictionary& par)>&)
        
        virtual void execute(const SCDictionary& par) override;
        
        void setOnStartFunc(const std::function<void(const SCDictionary& par)>& func);
        
    private:
        std::function<void(const SCDictionary& par)>  _startFunc;
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
        
        SC_DEFINE_CREATE_FUNC_2(SCBehaviorStrategySwitch,SCPerformer::Ptr,const int)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        SCBehaviorStrategySwitch(SCPerformer::Ptr performerPtr,const int nStragtegyID):
        _performerPtr(performerPtr),
        _nStragtegyID(nStragtegyID)
        {}
        
    private:
        SCPerformer::Ptr            _performerPtr;
        int                         _nStragtegyID;
    };
    
    ///----------- SCBehaviorRemovePerformer
    class SCBehaviorRemovePerformer : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorRemovePerformer)
        SC_DEFINE_CLASS_PTR(SCBehaviorRemovePerformer)
        
        SC_DEFINE_CREATE_FUNC_0(SCBehaviorRemovePerformer)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        SCBehaviorRemovePerformer()
        {}
    };
}

#endif // __SPEEDCC__SCSTRATEGYCOMMON_H__
