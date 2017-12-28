

#include "SCBehavior.h"
#include "SCMacroDef.h"

namespace SpeedCC
{
    ///----------- SCBehavior
    void SCBehavior::setName(const SCString& strName)
    {
        _strName = strName;
    }
    
    bool SCBehavior::start()
    {
        _state = RUNNING;
        return true;
    }
    
    bool SCBehavior::start(SCDictionary& par)
    {
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
        SC_RETURN_IF(_start2Func==NULL,true);
        SCBehavior::start();
        return _start2Func();
    }
    
    bool SCBehaviorCallFunc::start(SCDictionary& par)
    {
        SC_RETURN_IF(_startFunc==NULL,true);
        SCBehavior::start(par);
        return _startFunc(par);
    }
    
    void SCBehaviorCallFunc::pause(void)
    {
        SCBehavior::pause();
        if(_pauseFunc!=NULL)
        {
            _pauseFunc();
        }
    }
    
    void SCBehaviorCallFunc::resume(void)
    {
        SCBehavior::resume();
        if(_resumeFunc!=NULL)
        {
            _resumeFunc();
        }
    }
    
    void SCBehaviorCallFunc::stop(void)
    {
        SCBehavior::stop();
        if(_stopFunc!=NULL)
        {
            _stopFunc();
        }
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
        SCBehavior::start();
        for(auto& it : _behaviorList)
        {
            it->start();
        }
        
        return true;
    }
    
    bool SCBehaviorGroup::start(SCDictionary& par)
    {
        SCBehavior::start(par);
        
        for(auto& it : _behaviorList)
        {
            it->start(par);
        }
        
        return true;
    }
    
    void SCBehaviorGroup::pause(void)
    {
        for(auto& it : _behaviorList)
        {
            it->pause();
        }
        SCBehavior::pause();
    }
    
    void SCBehaviorGroup::resume(void)
    {
        SCBehavior::resume();
        for(auto& it : _behaviorList)
        {
            it->resume();
        }
    }
    
    void SCBehaviorGroup::stop(void)
    {
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
    
    void SCBehaviorGroup::removeBehavior(const SCString& strName)
    {
        SC_RETURN_IF_V(strName.isEmpty());
        _behaviorList.remove_if([strName](const SCBehavior::Ptr& ptrBvr)
                                 {
                                     return (ptrBvr->getName()==strName);
                                 });
    }
}

