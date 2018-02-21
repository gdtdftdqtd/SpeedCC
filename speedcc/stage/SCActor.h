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

#ifndef __SPEEDCC__SCACTOR_H__
#define __SPEEDCC__SCACTOR_H__

#include "SCPerformObject.h"
#include "SCMessage.h"

namespace SpeedCC
{
    class SCStrategy;
    class SCRole;
    
    class SCActor : public SCPropertyHolder
    {
        friend class SCRole;
    public:
        SC_AVOID_CLASS_COPY(SCActor)
        SC_DEFINE_CLASS_PTR(SCActor)
        
        SC_DEFINE_CREATE_FUNC_1(SCActor,const int)
        
        bool applyStrategy(SCStrategy* pStrategy);
        void removeFromRole();
        
        inline SCRole* getRole() const {return _pOwnerRole;}
        inline SCStrategy* getStrategy() const { return _pCurStrategy;}
        
        virtual void update(SCMessage::Ptr ptrMsg);
        
    protected:
        SCActor(const int nID);
        
        void setRole(SCRole* pRole) {_pOwnerRole = pRole; }
        
    private:
        SCStrategy*             _pCurStrategy;
        SCRole*                 _pOwnerRole;
    };
    
}

#endif // __SPEEDCC__SCACTOR_H__
