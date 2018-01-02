

#ifndef __SPEEDCC__SCBEHAVIOR_H__
#define __SPEEDCC__SCBEHAVIOR_H__

#include "SCPerformObject.h"
#include "../base/SCDictionary.h"

namespace SpeedCC
{
    ///-------------- SCBehavior
    class SCBehavior : public SCPerformObject
    {
    protected:
        SCBehavior():
        _state(STOPPED)
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCBehavior)
        SC_DEFINE_CLASS_PTR(SCBehavior)
        
        enum EState {RUNNING,PAUSED,STOPPED};
        
        inline EState getState() const {return _state;}
        
        virtual bool start();
        virtual bool start(SCDictionary& par);
        virtual void pause(void);
        virtual void resume(void);
        virtual void stop(void);
        
        bool getActive() const = delete;
        void setActive(const bool _bActive) = delete;
        
    protected:
//        virtual void onActiveChanged(const bool bNewActive) override;
        virtual void onStateChanged(EState oldState, EState newState) {}
        
        inline bool canStart() const { return (_state==STOPPED); }
        inline bool canPause() const { return (_state==RUNNING); }
        inline bool canResume() const { return (_state==PAUSED); }
        
    private:
        EState      _state;
    };
    
}

#endif // __SPEEDCC__SCBEHAVIOR_H__
