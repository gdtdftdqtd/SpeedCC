//
//  SCStrategyCommon.cpp
//  libspeedcc
//
//  Created by Kevin on 2/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCStrategyCommon.h"

namespace SpeedCC
{
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
    
    ///--------------- SCBehaviorStrategySwitch
    bool SCBehaviorStrategySwitch::start()
    {
        SC_RETURN_IF(!this->canStart(), false);
        SC_RETURN_IF(_performerPtr==NULL || _nStragtegyID==0, false);
        
        auto stragtegy = _performerPtr->getRole()->getStrategy(_nStragtegyID);
        SC_RETURN_IF(stragtegy==NULL, false);
        _performerPtr->setStrategy(stragtegy.getRawPointer());
        
        return true;
    }
    
    bool SCBehaviorStrategySwitch::start(SCDictionary& par)
    {
        SC_RETURN_IF(!this->canStart(), false);
        SC_RETURN_IF(_performerPtr==NULL || _nStragtegyID==0, false);
        
        return true;
    }
}


