/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
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

#ifndef __SPEEDCC__SCSTRATEGY_H__
#define __SPEEDCC__SCSTRATEGY_H__

#include "SCMessage.h"
#include "SCBehaviorCommon.h"

namespace SpeedCC
{
    class SCActor;
    
    class SCStrategy : public SCPerformObject
    {
    public:
        
    public:
        SC_AVOID_CLASS_COPY(SCStrategy)
        SC_DEFINE_CLASS_PTR(SCStrategy)
        
        SC_DEFINE_CREATE_FUNC_1(SCStrategy,const int)
        
        virtual void update(SCActor* pActor,SCMessage::Ptr ptrMsg);
        void enter(SCActor* pActor);
        void exit(SCActor* pActor);
        
    protected:
        SCStrategy(const int nID):
        SCPerformObject(nID)
        {}
        
    private:
        struct SBehaviorInfo
        {
            SCMessageMatcher::Ptr   ptrMatcher;
            SCBehaviorGroup::Ptr    ptrBehaviorGroup;
        };
        
    private:
        SCBehaviorGroup::Ptr                    _ptrEnterBehavior;
        SCBehaviorGroup::Ptr                    _ptrExitBehavior;
        
        std::map<int,SBehaviorInfo>             _msgID2BehaviorMap;
        std::map<SCString,SBehaviorInfo>        _command2BehaviorMap;
    };
    
    ///------------- SCStrategyEmpty
    class SCStrategyEmpty : public SCStrategy
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategyEmpty)
        SC_DEFINE_CLASS_PTR(SCStrategyEmpty)
        
        SC_DEFINE_CREATE_FUNC_0(SCStrategyEmpty)
        
    protected:
        SCStrategyEmpty():
        SCStrategy(SCID::Stg::kStgEmpty)
        {
        }
    };
    
    ///-------------- SCStrategyFunc
    class SCStrategyFunc : public SCStrategy
    {
    public:
        SC_AVOID_CLASS_COPY(SCStrategyFunc)
        SC_DEFINE_CLASS_PTR(SCStrategyFunc)
        
        SC_DEFINE_CREATE_FUNC_2(SCStrategyFunc,const int,const std::function<void(SCActor* pActor, SCMessage::Ptr ptrMsg)>&)
        
        virtual void update(SCActor* pActor,SCMessage::Ptr ptrMsg) override;
    protected:
        SCStrategyFunc(const int nID,const std::function<void(SCActor* pActor,SCMessage::Ptr ptrMsg)>& func):
        SCStrategy(nID),
        _func(func)
        {}
        
    private:
        std::function<void(SCActor* pActor,SCMessage::Ptr ptrMsg)>  _func;
    };
}

#endif // __SPEEDCC__SCSTRATEGY_H__
