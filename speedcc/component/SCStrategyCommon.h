//
//  SCStrategyCommon.hpp
//  libspeedcc
//
//  Created by Kevin on 2/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSTRATEGYCOMMON_H__
#define __SPEEDCC__SCSTRATEGYCOMMON_H__

#include "SCBehavior.h"
#include "SCRole.h"

namespace SpeedCC
{
    
    ///-------------- SCBehaviroCallFunc
    class SCBehaviorCallFunc : public SCBehavior
    {
    protected:
        
        SCBehaviorCallFunc()
        {}
        
        SCBehaviorCallFunc(const std::function<bool()>& startFunc)
        {
            this->setOnStartFunc(startFunc);
        }
        
        SCBehaviorCallFunc(const std::function<bool(SCDictionary& par)>& startFunc)
        {
            this->setOnStartFunc(startFunc);
        }
        
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorCallFunc)
        SC_DEFINE_CLASS_PTR(SCBehaviorCallFunc)
        
        SC_DEFINE_CREATE_FUNC0(SCBehaviorCallFunc)
        SC_DEFINE_CREATE_FUNC1(SCBehaviorCallFunc,const std::function<bool(SCDictionary& par)>&)
        SC_DEFINE_CREATE_FUNC1(SCBehaviorCallFunc,const std::function<bool()>&)
        //        SC_DEFINE_CREATE_FUNC1(SCBehaviorCallFunc,const SCString&)
        
        virtual bool start();
        virtual bool start(SCDictionary& par);
        virtual void pause(void);
        virtual void resume(void);
        virtual void stop(void);
        
        void setOnStartFunc(const std::function<bool()>& func);
        void setOnStartFunc(const std::function<bool(SCDictionary& par)>& func);
        void setOnPauseFunc(const std::function<void(void)>& func);
        void setOnResumeFunc(const std::function<void(void)>& func);
        void setOnStopFunc(const std::function<void(void)>& func);
        
    private:
        std::function<bool()>                   _start2Func;
        std::function<bool(SCDictionary& par)>  _startFunc;
        std::function<void(void)>               _pauseFunc;
        std::function<void(void)>               _resumeFunc;
        std::function<void(void)>               _stopFunc;
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
        
        SC_DEFINE_CREATE_FUNC0(SCBehaviorGroup)
        
        virtual bool start();
        virtual bool start(SCDictionary& par);
        virtual void pause(void);
        virtual void resume(void);
        virtual void stop(void);
        
        void addBehavior(const SCBehavior::Ptr& ptrBvr);
        void removeBehavior(const int nID);
        
    private:
        std::list<SCBehavior::Ptr> _behaviorList;
    };
    
    ///--------------- SCBehaviorState
    class SCBehaviorState : public SCBehavior
    {
    protected:
        SCBehaviorState(SCBehavior::Ptr bvrPtr, EState state):
        _targetBvrPtr(bvrPtr),
        _targetState(state)
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorState)
        SC_DEFINE_CLASS_PTR(SCBehaviorState)
        
        SC_DEFINE_CREATE_FUNC2(SCBehaviorState,SCBehavior::Ptr,EState)
        
        virtual bool start() override;
        virtual bool start(SCDictionary& par) override;
        
    private:
        SCBehavior::Ptr     _targetBvrPtr;
        EState              _targetState;
    };
    
    ///---------------- SCBehaviorStrategySwitch
    class SCBehaviorStrategySwitch : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorStrategySwitch)
        SC_DEFINE_CLASS_PTR(SCBehaviorStrategySwitch)
        
        SC_DEFINE_CREATE_FUNC2(SCBehaviorStrategySwitch,SCPerformer::Ptr,const int)
        
        virtual bool start() override;
        virtual bool start(SCDictionary& par) override;
        
    protected:
        SCBehaviorStrategySwitch(SCPerformer::Ptr performerPtr,const int nStragtegyID):
        _performerPtr(performerPtr),
        _nStragtegyID(nStragtegyID)
        {}
        
    private:
        SCPerformer::Ptr            _performerPtr;
        int                         _nStragtegyID;
    };
}

#endif // __SPEEDCC__SCSTRATEGYCOMMON_H__
