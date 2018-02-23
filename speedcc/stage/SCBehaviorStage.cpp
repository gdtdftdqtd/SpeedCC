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

#include "SCBehaviorStage.h"
#include "SCStage.h"
#include "SCStageMacroDef.h"

namespace SpeedCC
{
    ///--------------- SCBehaviorStrategySwitch
    
    void SCBehaviorStrategySwitch::execute(const SCDictionary& par)
    {
        SC_RETURN_V_IF(!this->getActive());
        SC_RETURN_V_IF(_nStragtegyID==0);
        auto actorValue = par.getValue(SC_KEY_ACTOR);
        SC_RETURN_V_IF(!actorValue.isValidObject<SCActor::Ptr>());
        
        auto ptrActor = actorValue.getObject<SCActor::Ptr>();
        
        auto stragtegy = ptrActor->getRole()->getStrategy(_nStragtegyID);
        SC_RETURN_V_IF(stragtegy==nullptr);
        
        ptrActor->applyStrategy(stragtegy.getRawPointer());
    }
    
    ///--------------- SCBehaviorRemoveActor
    
    void SCBehaviorRemoveActor::execute(const SCDictionary& par)
    {
        SC_RETURN_V_IF(!this->getActive());
        auto actorValue = par.getValue(SC_KEY_ACTOR);
        SC_RETURN_V_IF(!actorValue.isValidObject<SCActor::Ptr>());
        
        auto ptrActor = actorValue.getObject<SCActor::Ptr>();
        if(_nActorID==0)
        {// remove all actors
            ptrActor->removeFromRole();
        }
        else if(_nActorID==ptrActor->getID())
        {
            ptrActor->removeFromRole();
        }
    }
    
    ///--------------- SCBehaviorRoleActive
    void SCBehaviorRoleActive::execute(const SCDictionary& par)
    {
        auto actorValue = par.getValue(SC_KEY_ACTOR);
        SC_RETURN_V_IF(!actorValue.isValidObject<SCActor::Ptr>());
        auto ptrActor = actorValue.getObject<SCActor::Ptr>();
        
        if(_nRoleID==0 || _nRoleID==ptrActor->getRole()->getID())
        {
            ptrActor->getRole()->setActive(_bActive);
        }
        else
        {
            ptrActor->getRole()->getStage()->getRole(_nRoleID)->setActive(_bActive);
        }
    }
    
    ///--------------- SCBehaviorDeliverMessage
    SCBehaviorDeliverMessage::SCBehaviorDeliverMessage(const bool bSend,SCMessage::Ptr ptrMsg):
    _bSend(bSend)
    {
        SCASSERT(ptrMsg!=nullptr);
        _ptrMsg = ptrMsg->clone();
    }
    
    SCBehaviorDeliverMessage::SCBehaviorDeliverMessage(const bool bSend,const int nMsgID):
    _bSend(bSend)
    {
        _ptrMsg = SCMessage::create(nMsgID);
    }
    
    SCBehaviorDeliverMessage::SCBehaviorDeliverMessage(const bool bSend,const SCString& strCmd):
    _bSend(bSend)
    {
        _ptrMsg = SCMessage::create(strCmd);
    }
    
    void SCBehaviorDeliverMessage::execute(const SCDictionary& par)
    {
        SCASSERT(_ptrMsg!=nullptr);
        
        if(_bSend)
        {
            SCMsgDisp()->sendMessage(_ptrMsg);
        }
        else
        {
            SCMsgDisp()->postMessage(_ptrMsg);
        }
    }
}
