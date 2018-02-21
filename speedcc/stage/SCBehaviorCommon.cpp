/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "SCBehaviorCommon.h"
#include "../cocos/SCCocosDef.h"
#include "../system/SCSystem.h"

namespace SpeedCC
{
    ///----------- SCBehaviorCallFunc
    
    void SCBehaviorCallFunc::execute(const SCDictionary& par)
    {
        SC_RETURN_V_IF(!this->getActive());
        if(_startFunc!=nullptr)
        {
            _startFunc(par);
        }
        else if(_startFunc2!=nullptr)
        {
            _startFunc2();
        }
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<void(const SCDictionary& par)>& func)
    {
        _startFunc = func;
        _startFunc2 = nullptr;
    }
    
    void SCBehaviorCallFunc::setOnStartFunc(const std::function<void()>& func)
    {
        _startFunc2 = func;
        _startFunc = nullptr;
    }
    
    
    ///----------- SCBehaviorGroup
    
    SCBehaviorGroup::SCBehaviorGroup(SCBehavior::Ptr ptrBvr)
    {
        SCASSERT(ptrBvr!=nullptr);
        this->addBehavior(ptrBvr);
    }
    
    void SCBehaviorGroup::execute(const SCDictionary& par)
    {
        SC_RETURN_V_IF(!this->getActive());
        for(auto it : _behaviorList)
        {
            it->execute(par);
        }
    }
    
    void SCBehaviorGroup::addBehavior(const SCBehavior::Ptr& ptrBvr)
    {
        SC_RETURN_V_IF(ptrBvr==nullptr);
        _behaviorList.push_back(ptrBvr);
    }
    
    void SCBehaviorGroup::removeBehavior(const int nID)
    {
        SC_RETURN_V_IF(nID==0);
        _behaviorList.remove_if([nID](const SCBehavior::Ptr& ptrBvr)
                                {
                                    return (ptrBvr->getID()==nID);
                                });
    }
    
    ///------------- SCBehaviorDelayExecute
    SCBehaviorDelayExecute::~SCBehaviorDelayExecute()
    {
        SCCCScheduler()->unschedule(SCF(onDelayExecute),static_cast<cocos2d::Ref*>(this));
    }
    
    void SCBehaviorDelayExecute::execute(const SCDictionary& par)
    {
        if(!_bPost && _ptrBvr!=nullptr)
        {
            _bPost = true;
            SCCCScheduler()->schedule(SCF(onDelayExecute),static_cast<cocos2d::Ref*>(this),_fDelay,false);
        }
    }
    
    void SCBehaviorDelayExecute::onDelayExecute(float fDelta)
    {
        SCCCScheduler()->unschedule(SCF(onDelayExecute),static_cast<cocos2d::Ref*>(this));
        _bPost = false;
        if(_ptrBvr!=nullptr)
        {
            _ptrBvr->execute();
        }
    }
    
    bool SCBehaviorDelayExecute::setBehavior(SCBehavior::Ptr ptrBvr)
    {
        SC_RETURN_IF(_bPost, false);
        _ptrBvr = ptrBvr;
        return true;
    }
    
    bool SCBehaviorDelayExecute::setDelayTime(const float fDelay)
    {
        SC_RETURN_IF(_bPost, false);
        _fDelay = fDelay;
        _fDelay = _fDelay<0 ? 0 : _fDelay;
        return true;
    }
    
    ///------------ SCBehaviorBoolInvert
    SCBehaviorBoolInvert::SCBehaviorBoolInvert()
    {
        _ptrWatch = SCWatchBool::create();
    }
    
    SCBehaviorBoolInvert::SCBehaviorBoolInvert(const bool bInit)
    {
        _ptrWatch = SCWatchBool::create();
        (*_ptrWatch) = bInit;
    }
    
    SCBehaviorBoolInvert::SCBehaviorBoolInvert(SCWatchBool::Ptr ptrWatch):
    _ptrWatch(ptrWatch)
    {
    }
    
    void SCBehaviorBoolInvert::execute(const SCDictionary& par)
    {
        if(_ptrWatch!=nullptr)
        {
            (*_ptrWatch) = !(*_ptrWatch);
        }
    }
}


