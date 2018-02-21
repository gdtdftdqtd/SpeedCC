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

#include "SCRoleBuilder.h"

namespace SpeedCC
{
    SCRoleBuilder::SCRoleBuilder():
    _pStage(nullptr)
    {
    }
    
    void SCRoleBuilder::begin(const int nRoleID,const int nInitStrategyID,SCStage* pStage)
    {
        SCASSERT(_strategyStack.empty());
        SCASSERT(nRoleID>0);
        SCASSERT(nInitStrategyID>0);
        SCASSERT(pStage!=nullptr);
        
        _pStage = pStage;
        _ptrRole = SCRole::create(nRoleID, pStage);
        
        this->beginStragtegy(nInitStrategyID);
        _ptrRole->setInitStrategyID(nInitStrategyID);
    }
    
    void SCRoleBuilder::end()
    {
        _strategyStack.pop();
        SCASSERT(_strategyStack.empty());
        _pStage->addRole(_ptrRole);
    }
    
    void SCRoleBuilder::beginStragtegy(const int nStrategyID)
    {
        SCASSERT(nStrategyID>0);
        
        int nParentStrategyID = 0;
        if(!_strategyStack.empty())
        {
            nParentStrategyID = _strategyStack.top().nCurrentStrategyID;
        }
        auto ptrStrategy = this->createStrategy(nStrategyID);
        
        _ptrRole->addStrategy(ptrStrategy,nParentStrategyID);
        
        SStrategyStackInfo ssi;
        ssi.nCurrentStrategyID = nStrategyID;
        
        _strategyStack.push(ssi);
    }
    
    void SCRoleBuilder::endStrategy()
    {
        _strategyStack.pop();
    }
    
    void SCRoleBuilder::insertBehaviorWithMsg(const SCRoleBuilder::MessagePurifier& msgPurifier,const BehaviorPurifier& bvrPurifier)
    {
//        SCASSERT(bvrPurifier.ptrBehavior !=nullptr);
        SCASSERT(!_strategyStack.empty());
        
        int nParentStrategyID = _strategyStack.top().nCurrentStrategyID;
        
        for(auto it : msgPurifier.msgList)
        {
            _ptrRole->addBehavior2Strategy(nParentStrategyID, it.nMsg, bvrPurifier.ptrBehavior,it.ptrMatcher);
        }
    }
    
    void SCRoleBuilder::insertBehaviorWithCmd(const SCString& strCmd,const BehaviorPurifier& bvrPurifier)
    {
        SCASSERT(!strCmd.isEmpty());
        SCASSERT(bvrPurifier.ptrBehavior!=nullptr);
        SCASSERT(!_strategyStack.empty());
        
        int nParentStrategyID = _strategyStack.top().nCurrentStrategyID;
        _ptrRole->addBehavior2Strategy(nParentStrategyID, strCmd, bvrPurifier.ptrBehavior);
    }
    
    void SCRoleBuilder::insertEnterBehavior(const BehaviorPurifier& bvrPurifier)
    {
        SCASSERT(bvrPurifier.ptrBehavior!=nullptr);
        SCASSERT(!_strategyStack.empty());
        
        int nParentStrategyID = _strategyStack.top().nCurrentStrategyID;
        _ptrRole->addEnterBehavior2Strategy(nParentStrategyID, bvrPurifier.ptrBehavior);
    }
    
    void SCRoleBuilder::insertExitBehavior(const BehaviorPurifier& bvrPurifier)
    {
        SCASSERT(bvrPurifier.ptrBehavior!=nullptr);
        SCASSERT(!_strategyStack.empty());
        
        int nParentStrategyID = _strategyStack.top().nCurrentStrategyID;
        _ptrRole->addExitBehavior2Strategy(nParentStrategyID, bvrPurifier.ptrBehavior);
    }
    
    SCStrategy::Ptr SCRoleBuilder::createStrategy(const int nStrategyID)
    {
        SCStrategy::Ptr ret ;
        if(nStrategyID==SCID::Stg::kSCStgEmpty)
        {
            ret = SCStrategyEmpty::create();
        }
        else
        {
            ret = _pStage->onCreateStrategy(nStrategyID);
        }
        ret->setID(nStrategyID);
        
        return ret;
    }
    
    ///--------------- utils
    
    SCRoleBuilder::BehaviorPurifier::BehaviorPurifier(const std::function<void(const SCDictionary& par)>& func)
    {
        ptrBehavior = SCBehaviorCallFunc::create([func](const SCDictionary& par)
                                                 {
                                                     func(par);
                                                 });
    }
    
    SCRoleBuilder::BehaviorPurifier::BehaviorPurifier(const std::function<void()>& func)
    {
        ptrBehavior = SCBehaviorCallFunc::create([func](const SCDictionary& par)
                                                 {
                                                     func();
                                                 });
    }
    
    SCRoleBuilder::MessagePurifier::MessagePurifier(const int nMsgID)
    {
        SMsgListInfo mli;
        mli.nMsg = nMsgID;
        mli.ptrMatcher = nullptr;
        
        msgList.push_back(mli);
    }
    
    SCRoleBuilder::MessagePurifier::MessagePurifier(SCMessageMatcher::Ptr ptrMatcher)
    {
        SMsgListInfo mli;
        mli.nMsg = ptrMatcher->getMessageID();
        mli.ptrMatcher = ptrMatcher;
        
        msgList.push_back(mli);
    }
    
    SCRoleBuilder::MessagePurifier::MessagePurifier(SCMessageGroup::Ptr ptrGroup)
    {
        auto ls = ptrGroup->getMessageList();
        for(auto it : ls)
        {
            SMsgListInfo mli;
            
            mli.nMsg = it->nMsgID;
            mli.ptrMatcher = nullptr;
            
            msgList.push_back(mli);
        }
    }
    
}
