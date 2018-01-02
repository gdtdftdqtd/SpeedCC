

#include "SCBehavior.h"
#include "SCMacroDef.h"

namespace SpeedCC
{
    ///----------- SCBehavior
    
    bool SCBehavior::start()
    {
        SC_RETURN_IF(_state!=STOPPED, false);
        SC_RETURN_IF(_state==RUNNING,true);
        auto oldState = _state;
        _state = RUNNING;
        this->onStateChanged(oldState,_state);
        return true;
    }
    
    bool SCBehavior::start(SCDictionary& par)
    {
        SC_RETURN_IF(_state!=STOPPED, false);
        SC_RETURN_IF(_state==RUNNING,true);
        auto oldState = _state;
        _state = RUNNING;
        this->onStateChanged(oldState,_state);
        return true;
    }
    
    void SCBehavior::pause(void)
    {
        SC_RETURN_IF_V(_state==PAUSED);
        auto oldState = _state;
        _state = PAUSED;
        this->onStateChanged(oldState,_state);
    }
    
    void SCBehavior::resume(void)
    {
        SC_RETURN_IF_V(_state==RUNNING);
        auto oldState = _state;
        _state = RUNNING;
        this->onStateChanged(oldState,_state);
    }
    
    void SCBehavior::stop(void)
    {
        SC_RETURN_IF_V(_state==STOPPED);
        auto oldState = _state;
        _state = STOPPED;
        
        this->onStateChanged(oldState,_state);
    }
    
//    void SCBehavior::onStateChanged(EState oldState, EState newState)
//    {
//
//    }
    
//    void SCBehavior::onActiveChanged(const bool bNewActive)
//    {
//        if(bNewActive)
//        {
//            this->start();
//        }
//        else
//        {
//            this->stop();
//        }
//    }

}

