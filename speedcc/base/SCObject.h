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

#ifndef __SPEEDCC__SCOBJECT_H__
#define __SPEEDCC__SCOBJECT_H__

#include "SCObjPtrT.h"

namespace SpeedCC
{
    class SCObject
    {
        template<typename,bool> friend class SCObjPtrT;
        
    public:
        SC_DEFINE_CLASS_PTR(SCObject)
        SCObject();
        virtual ~SCObject();
        
        template<typename T>
        T makeObjPtr()
        {
            return _pObjPtrData==nullptr ? nullptr : SCObjPtrT<typename T::type>(_pObjPtrData);
        }
        
        template<typename T>
        SCObjPtrT<typename std::decay<typename std::remove_pointer<T>::type>::type> makeObjPtr(T)
        {
            return _pObjPtrData==nullptr ? nullptr : SCObjPtrT<typename std::decay<typename std::remove_pointer<T>::type>::type>(_pObjPtrData);
        }
        
        void addObject(SCObject::Ptr ptrObj);
        void removeObject(SCObject::Ptr ptrObj);
        
    private:
        void setObjPtrData(void* pData);
        
    private:
        void*                       _pObjPtrData;
        std::list<SCObject::Ptr>    _objList;
    };
}

#endif //__SPEEDCC__SCOBJECT_H__
