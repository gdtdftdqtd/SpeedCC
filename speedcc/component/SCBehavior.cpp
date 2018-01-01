

#include "SCBehavior.h"
#include "SCMacroDef.h"

namespace SpeedCC
{
    ///----------- SCBehavior
    
    bool SCBehavior::start()
    {
        SC_RETURN_IF(_state!=STOPPED, false);
        _state = RUNNING;
        return true;
    }
    
    bool SCBehavior::start(SCDictionary& par)
    {
        SC_RETURN_IF(_state!=STOPPED, false);
        _state = RUNNING;
        return true;
    }
    
    void SCBehavior::pause(void)
    {
        _state = PAUSED;
    }
    
    void SCBehavior::resume(void)
    {
        _state = RUNNING;
    }
    
    void SCBehavior::stop(void)
    {
        _state = STOPPED;
    }
    
    ///----------- SCBehaviorCallFunc
    bool SCBehaviorCallFunc::start()
    {
        SC_RETURN_IF(!this->canStart(),false);
        SC_RETURN_IF(_start2Func==NULL,true);
        SC_RETURN_IF(!SCBehavior::start(),false);
        return _start2Func();
    }
    
    bool SCBehaviorCallFunc::start(SCDictionary& par)
    {
        SC_RETURN_IF(!this->canStart(),false);
        
        SC_RETURN_IF(_startFunc==NULL,true);
        SC_RETURN_IF(!SCBehavior::start(par),false);
        return _startFunc(par);
    }
    
    void SCBehaviorCallFunc::pause(void)
    {
        SC_RETURN_IF_V(!this->canPause());
        
        if(_pauseFunc!=NULL)
        {
            _pauseFunc();
        }
        SCBehavior::pause();
    }
    
    void SCBehaviorCallFunc::resume(void)
    {
        SC_RETURN_IF_V(!this->canResume());
        
        if(_resumeFunc!=NULL)
        {
            _resumeFunc();
        }
        SCBehavior::resume();
    }
    
    void SCBehaviorCallFunc::stop(void)
    {
        SC_RETURN_IF_V(this->getState()==STOPPED);
        
        if(_stopFunc!=NULL)
        {
            _stopFunc();
        }
        
        SCBehavior::stop();
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<bool()>& func)
    {
        _start2Func = func;
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<bool(SCDictionary& par)>& func)
    {
        _startFunc = func;
    }
    
    void SCBehaviorCallFunc::setOnPauseFunc(const std::function<void(void)>& func)
    {
        _pauseFunc = func;
    }
    
    void SCBehaviorCallFunc::setOnResumeFunc(const std::function<void(void)>& func)
    {
        _resumeFunc = func;
    }
    
    void SCBehaviorCallFunc::setOnStopFunc(const std::function<void(void)>& func)
    {
        _stopFunc = func;
    }
    
    ///----------- SCBehaviorGroup
    
    bool SCBehaviorGroup::start()
    {
        SC_RETURN_IF(!this->canStart(), false);
        for(auto& it : _behaviorList)
        {
            it->start();
        }
        
        SCBehavior::start();
        return true;
    }
    
    bool SCBehaviorGroup::start(SCDictionary& par)
    {
        SC_RETURN_IF(!this->canStart(), false);
        SCBehavior::start(par);
        
        for(auto& it : _behaviorList)
        {
            it->start(par);
        }
        
        return true;
    }
    
    void SCBehaviorGroup::pause(void)
    {
        SC_RETURN_IF_V(!this->canPause());
        for(auto& it : _behaviorList)
        {
            it->pause();
        }
        SCBehavior::pause();
    }
    
    void SCBehaviorGroup::resume(void)
    {
        SC_RETURN_IF_V(!this->canResume());
        for(auto& it : _behaviorList)
        {
            it->resume();
        }
        SCBehavior::resume();
    }
    
    void SCBehaviorGroup::stop(void)
    {
        SC_RETURN_IF_V(this->getState()==STOPPED);
        
        for(auto& it : _behaviorList)
        {
            it->stop();
        }
        SCBehavior::stop();
    }
    
    void SCBehaviorGroup::addBehavior(const SCBehavior::Ptr& ptrBvr)
    {
        SC_RETURN_IF_V(ptrBvr==NULL);
        _behaviorList.push_back(ptrBvr);
    }
    
    void SCBehaviorGroup::removeBehavior(const int nID)
    {
        SC_RETURN_IF_V(nID==0);
        _behaviorList.remove_if([nID](const SCBehavior::Ptr& ptrBvr)
                                 {
                                     return (ptrBvr->getID()==nID);
                                 });
    }
    
    ///---------------- SCBehaviorState
    bool SCBehaviorState::start()
    {
        SC_RETURN_IF(!this->canStart(), false);
        if(_targetBvrPtr!=NULL)
        {
            switch(_targetState)
            {
                case SCBehavior::RUNNING:
                    if(_targetBvrPtr->getState()==STOPPED)
                    {
                        _targetBvrPtr->start();
                    }
                    else if(_targetBvrPtr->getState()==PAUSED)
                    {
                        _targetBvrPtr->resume();
                    }
                    break;
                    
                case SCBehavior::PAUSED:
                    _targetBvrPtr->pause();
                    break;
                    
                case SCBehavior::STOPPED:
                    _targetBvrPtr->stop();
                    break;
                    
                default: break;
            }
        }
        return SCBehavior::start();
    }
    
    bool SCBehaviorState::start(SCDictionary& par)
    {
        SC_RETURN_IF(!this->canStart(), false);
        if(_targetBvrPtr!=NULL)
        {
            switch(_targetState)
            {
                case SCBehavior::RUNNING:
                    if(_targetBvrPtr->getState()==STOPPED)
                    {
                        _targetBvrPtr->start(par);
                    }
                    else if(_targetBvrPtr->getState()==PAUSED)
                    {
                        _targetBvrPtr->resume();
                    }
                    break;
                    
                case SCBehavior::PAUSED:
                    _targetBvrPtr->pause();
                    break;
                    
                case SCBehavior::STOPPED:
                    _targetBvrPtr->stop();
                    break;
                    
                default: break;
            }
        }
        return SCBehavior::start(par);
    }
}

