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

#include "SCStage.h"
#include "SCMessageDispatch.h"

namespace SpeedCC
{
    SCStage::SCStage()
    {
        SCMessageDispatch::getInstance()->addListener(this);
    }
    
    SCStage::~SCStage()
    {
        SCMessageDispatch::getInstance()->removeListener(this);
    }
    
    void SCStage::addRole(SCRole::Ptr ptrRole)
    {
        SCASSERT(ptrRole!=nullptr);
        SCASSERT(ptrRole->getID()>0);
        
        _id2RoleMap[ptrRole->getID()] = ptrRole;
    }
    
    void SCStage::removeRole(const int nID)
    {
        _id2RoleMap.erase(nID);
    }
    
    SCRole::Ptr SCStage::getRole(const int nID)
    {
        SC_RETURN_IF(nID<=0,nullptr);
        
        auto it = _id2RoleMap.find(nID);
        SC_RETURN_IF(it==_id2RoleMap.end(),nullptr);
        return (*it).second;
    }
    
    void SCStage::onSCMessageProcess(SCMessage::Ptr ptrMsg)
    {
        SCASSERT(ptrMsg!=nullptr);
        SC_RETURN_V_IF(_id2RoleMap.empty());
        SC_RETURN_V_IF(!this->getActive());
        
        for(auto it : _id2RoleMap)
        {
            SC_RETURN_V_IF(!this->getActive());
            SC_BREAK_IF(!ptrMsg->bContinue);
            it.second->update(ptrMsg);
            SC_BREAK_IF(!ptrMsg->bContinue);
        }
    }
    
    void SCStage::onActiveChanged(const bool bNewActive)
    {
        
    }
}


