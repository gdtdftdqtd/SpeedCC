

#ifndef __SPEEDCC__SCBEHAVIOR_H__
#define __SPEEDCC__SCBEHAVIOR_H__

#include "SCComponent.h"
#include "../base/SCDictionary.h"

namespace SpeedCC
{
    ///-------------- SCBehavior
    class SCBehavior : public SCComponent
    {
    protected:
        SCBehavior(const SCString& strName):
        SCComponent(),
        _strName(strName),
        _state(STOPPED)
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCBehavior);
        SC_DEFINE_CLASS_PTR(SCBehavior);
        
        enum EState {RUNNING,PAUSED,STOPPED};
        
        void setName(const SCString& strName);
        inline SCString getName() const { return _strName; }
        inline EState getState() const {return _state;}
        
        virtual bool start(SCDictionary& par);
        virtual void pause(void);
        virtual void resume(void);
        virtual void stop(void);
        
    private:
        SCString    _strName;
        EState      _state;
    };
    
    ///-------------- SCBehaviroCallFunc
    class SCBehaviorCallFunc : public SCBehavior
    {
    protected:
        SCBehaviorCallFunc(const SCString& strName):
        SCBehavior(strName)
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorCallFunc);
        SC_DEFINE_CLASS_PTR(SCBehaviorCallFunc);
        
        static Ptr create();
        static Ptr create(const SCString& strName);
        
        virtual bool start(SCDictionary& par);
        virtual void pause(void);
        virtual void resume(void);
        virtual void stop(void);
        
        void setOnStartFunc(const std::function<bool(SCDictionary& par)>& func);
        void setOnPauseFunc(const std::function<void(void)>& func);
        void setOnResumeFunc(const std::function<void(void)>& func);
        void setOnStopFunc(const std::function<void(void)>& func);
        
    private:
        std::function<bool(SCDictionary& par)>  _startFunc;
        std::function<void(void)>               _pauseFunc;
        std::function<void(void)>               _resumeFunc;
        std::function<void(void)>               _stopFunc;
    };
    
    ///-------------- SCBehaviorGroup
    class SCBehaviorGroup : public SCBehavior
    {
    protected:
        SCBehaviorGroup(const SCString& strName):
        SCBehavior(strName)
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorGroup);
        SC_DEFINE_CLASS_PTR(SCBehaviorGroup);
        
        virtual bool start(SCDictionary& par);
        virtual void pause(void);
        virtual void resume(void);
        virtual void stop(void);
        
        void addBehavior(const SCBehavior::Ptr& ptrBvr);
        void removeBehavior(const SCString& strName);
        
    private:
        std::list<SCBehavior::Ptr> _behaviorList;
    };
}

#endif // __SPEEDCC__SCBEHAVIOR_H__
