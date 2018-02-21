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

#ifndef __SPEEDCC__SCROLE_H__
#define __SPEEDCC__SCROLE_H__

#include "SCPerformObject.h"
#include "SCActor.h"
#include "SCStrategy.h"

namespace SpeedCC
{
    struct SCStrategyInfo : public SCObject
    {
        SC_AVOID_CLASS_COPY(SCStrategyInfo)
        SC_DEFINE_CLASS_PTR(SCStrategyInfo)
        
        SC_DEFINE_CREATE_FUNC_0(SCStrategyInfo);
        
        struct SBehaviorInfo
        {
            SCMessageMatcher::Ptr   ptrMatcher;
            SCBehaviorGroup::Ptr    ptrBehaviorGroup;
        };
        
        int                                     nParentStrategyID;
        SCStrategy::Ptr                         ptrStrategy;
        SCBehaviorGroup::Ptr                    ptrEnterBehavior;
        SCBehaviorGroup::Ptr                    ptrExitBehavior;
        
        std::map<int,SBehaviorInfo>             msgID2BehaviorMap;
        std::map<SCString,SBehaviorInfo>        command2BehaviorMap;
        
    protected:
        SCStrategyInfo() {}
    };
    
    class SCStage;
    class SCRoleBuilder;
    
    class SCRole : public SCPropertyHolder
    {
        friend class SCRoleBuilder;
    public:
        SC_AVOID_CLASS_COPY(SCRole)
        SC_DEFINE_CLASS_PTR(SCRole)
        
        SC_DEFINE_CREATE_FUNC_2(SCRole, const int,SCStage*);
        
        bool addActor(SCActor::Ptr ptrActor);
        void removeActor(const int nID);
        bool hasActor(const int nID) const;
        SCActor::Ptr getActor(const int nID);
        
        void forEach(const std::function<bool(const SCActor::Ptr& ptrActor)>& func) const;
        void forEach(const std::function<bool(SCActor::Ptr& ptrActor)>& func);
        
        bool setInitStrategyID(const int nID);
        void addStrategy(SCStrategy::Ptr ptrStrategy,const int nParentID=0);
        SCStrategy::Ptr getStrategy(const int nID) const;
        SCStrategyInfo::Ptr getStrategyInfo(const int nID) const;
        bool hasStrategy(const int nID) const;
        
        bool addBehavior2Strategy(const int nStrategyID,
                                  const int nMsgID,
                                  SCBehavior::Ptr bvrPtr,
                                  SCMessageMatcher::Ptr ptrMatcher=nullptr);
        bool addBehavior2Strategy(const int nStrategyID,
                                  const SCString& strCommand,
                                  SCBehavior::Ptr bvrPtr,
                                  SCMessageMatcher::Ptr ptrMatcher=nullptr);
        bool addBehavior2Strategy(const int nStrategyID,
                                  SCMessageMatcher::Ptr ptrMatcher,
                                  SCBehavior::Ptr bvrPtr);
        
        bool addEnterBehavior2Strategy(const int nStrategyID,SCBehavior::Ptr bvrPtr);
        bool addExitBehavior2Strategy(const int nStrategyID,SCBehavior::Ptr bvrPtr);
    
        inline SCStage* getStage() const { return _pOwnerStage;}
        virtual void update(SCMessage::Ptr ptrMsg);
        
        inline bool getMsgFilterEnabled() const {return _bFilterMsg;}
        inline void setMsgFilterEnabled(const bool bEnable) {_bFilterMsg = bEnable;}
        
    protected:
        SCRole(const int nID,SCStage* pStage);
        
    private:
        void markMsgUnfilter(const int nMsgID);
        void markCmdUnfilter(const SCString& strCmd);
        void unmarkMsgUnfilter(const int nMsgID);
        void unmarkCmdUnfilter(const SCString& strCmd);
        
        bool isFilterMsg(SCMessage::Ptr ptrMsg);
        void updateVariationActor();
        bool isActorInRemovedList(const int nID) const;
        
    private:
        bool                                    _bUpdating;
        int                                     _nInitStrategyID;
        std::list<SCActor::Ptr>                 _actorList;
        
        std::map<int,SCStrategyInfo::Ptr>           _id2StrategyInfoMap;
        SCStage*                                _pOwnerStage;
        bool                                    _bFilterMsg;
        
        std::map<int,int>                       _msgID2FilterCounterMap;
        std::map<SCString,int>                  _cmd2FilterCounterMap;
        
        std::list<int>                          _removeActorList;
        std::list<SCActor::Ptr>                 _addActorList;
    };
}

#endif // __SPEEDCC__SCROLE_H__
