

#include "SCBehavior.h"
#include "SCMacroDef.h"

namespace SpeedCC
{
    ///----------- SCBehavior
    void SCBehavior::setName(const SCString& strName)
    {
        _strName = strName;
    }
    
    bool SCBehavior::start(SCParameters& par)
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
    SCBehaviorCallFunc::Ptr SCBehaviorCallFunc::create(const SCString& strName)
    {
        SCASSERT(!strName.isEmpty());
        
        SCBehaviorCallFunc::Ptr ptrRet;
        ptrRet.createInstanceWithCon([strName](void* pData)
                                     {
                                         new(pData)SCBehaviorCallFunc(strName);
                                     });
        
        return ptrRet;
    }
    
    bool SCBehaviorCallFunc::start(SCParameters& par)
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
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<bool(SCParameters& par)>& func)
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
    bool SCBehaviorGroup::start(SCParameters& par)
    {
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
    }
    
    void SCBehaviorGroup::resume(void)
    {
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
    }
    
    void SCBehaviorGroup::addBehavior(const SCBehavior::Ptr& ptrBhv)
    {
        SC_RETURN_IF_V(ptrBhv==NULL);
        _behaviorList.push_back(ptrBhv);
    }
    
    void SCBehaviorGroup::removeBehavior(const SCString& strName)
    {
        SC_RETURN_IF_V(strName.isEmpty());
        _behaviorList.remove_if([strName](const SCBehavior::Ptr& ptrBhv)
                                 {
                                     return (ptrBhv->getName()==strName);
                                 });
    }
}

