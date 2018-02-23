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

#ifndef __SPEEDCC__SCROLEBUILDER_H__
#define __SPEEDCC__SCROLEBUILDER_H__

#include "SCRole.h"
#include "SCStage.h"

namespace SpeedCC
{    
    class SCRoleBuilder : public SCObject
    {
    private:
        struct SMsgListInfo
        {
            int                     nMsg;
            SCString                strCmd;
            SCMessageMatcher::Ptr   ptrMatcher;
        };
        
    public:
        struct BehaviorPurifier
        {
            template<typename T,
            typename = typename std::enable_if<std::is_convertible<T,SCBehavior::Ptr>::value,T>::type >
            BehaviorPurifier(T bvr):
            ptrBehavior(bvr)
            {}

            BehaviorPurifier(const std::function<void(const SCDictionary& par)>& func);
            BehaviorPurifier(const std::function<void()>& func);
            BehaviorPurifier(void*) {}
            
            SCBehavior::Ptr     ptrBehavior;
        };
        
        struct MessagePurifier
        {
            MessagePurifier(const int nMsgID);
            MessagePurifier(SCMessageMatcher::Ptr ptrMatcher);
            MessagePurifier(SCMessageGroup::Ptr ptrGroup);
            MessagePurifier(...) {}
            
            std::list<SMsgListInfo> msgList;
        };
        
    public:
        SC_AVOID_CLASS_COPY(SCRoleBuilder)
        SC_DEFINE_CLASS_PTR(SCRoleBuilder)
        
        SC_DEFINE_CREATE_FUNC_0(SCRoleBuilder)
        
        void begin(const int nRoleID,const int nInitStrategyID,SCStage* pStage);
        void end();
        
        void beginStragtegy(const int nStrategyID);
        void endStrategy();
        
        void insertBehaviorWithMsg(const MessagePurifier& msgPurifier,const BehaviorPurifier& ptrBvr);
        void insertBehaviorWithCmd(const SCString& strCmd,const BehaviorPurifier& ptrBvr);
        void insertEnterBehavior(const BehaviorPurifier& ptrBvr);
        void insertExitBehavior(const BehaviorPurifier& ptrBvr);
        
    protected:
        SCRoleBuilder();
        
    private:
        SCStrategy::Ptr createStrategy(const int nStrategyID);
        
        struct SStrategyStackInfo
        {
            int                         nCurrentStrategyID;
        };
        
    private:
        SCStage*                    _pStage;
        SCRole::Ptr                 _ptrRole;
        std::stack<SStrategyStackInfo>  _strategyStack;
    };
}

#endif // __SPEEDCC__SCROLEBUILDER_H__
