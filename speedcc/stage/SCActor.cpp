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

#include "SCActor.h"
#include "SCRole.h"
#include "SCStage.h"

namespace SpeedCC
{
    SCActor::SCActor(const int nID):
    _pCurStrategy(nullptr),
    _pOwnerRole(nullptr)
    {
        this->setID(nID);
    }
    
    bool SCActor::applyStrategy(SCStrategy* pStrategy)
    {
        SC_RETURN_IF(_pOwnerRole==nullptr,false);
        SC_RETURN_IF(!_pOwnerRole->getActive(),false);
        SC_RETURN_IF(!_pOwnerRole->getStage()->getActive(),false);
        
        
        if(_pCurStrategy!=nullptr)
        {
            _pCurStrategy->exit(this);
        }
        
        _pCurStrategy = pStrategy;
        
        if(_pCurStrategy!=nullptr)
        {
            _pCurStrategy->enter(this);
        }
        
        return true;
    }
    
    void SCActor::removeFromRole()
    {
        SC_RETURN_V_IF(_pOwnerRole==nullptr);
        _pOwnerRole->removeActor(this->getID());
    }
    
    void SCActor::update(SCMessage::Ptr ptrMsg)
    {
        SCASSERT(ptrMsg!=nullptr);
        SC_RETURN_V_IF(_pCurStrategy==nullptr);
        SC_RETURN_V_IF(!this->getActive());
        _pCurStrategy->update(this,ptrMsg);
    }
}


