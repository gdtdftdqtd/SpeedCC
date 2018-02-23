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

#ifndef __SPEEDCC__SCOBJECT_H__
#define __SPEEDCC__SCOBJECT_H__

#include "SCObjPtrT.h"

namespace SpeedCC
{
    /*!
        This class is SpeedCC object base class.
     
     /note Class must derived from SCObject if want to be owned by SCObjPtrT as smart pointer.
     
     */
    class SCObject
    {
        template<typename,bool> friend class SCObjPtrT;
        
    public:
        SC_DEFINE_CLASS_PTR(SCObject)
        SCObject();
        virtual ~SCObject();
        
        /*!
            Converts raw pointer to smart pointer
         
            /tparam T Type of smart pointer to target
         */
        template<typename T>
        T makeObjPtr()
        {
            return _pObjPtrData==nullptr ? nullptr : SCObjPtrT<typename T::type>(_pObjPtrData);
        }
        
        /*!
         Converts raw pointer to smart pointer
         Convenient method for conversion without caring about target type exactly.
         
         For example: auto ptr = this->makeObjPtr(this);
         
         /tparam T Type of smart pointer to target
         /param t For traits target type only, no use in run time.
         */
        template<typename T>
        SCObjPtrT<typename std::decay<typename std::remove_pointer<T>::type>::type> makeObjPtr(T t)
        {
            return _pObjPtrData==nullptr ? nullptr :
            SCObjPtrT<typename std::decay<typename std::remove_pointer<T>::type>::type>(_pObjPtrData);
        }
        
        /*!
            Adds SCObject to current object.
         
            The purpose of this method is to have the same life cycle with current object.
         
            /ptrObj Target object
         */
        void addObject(SCObject::Ptr ptrObj);
        
        /*!
         Removes SCObject from current object.
         
         /ptrObj Target object
         */
        void removeObject(SCObject::Ptr ptrObj);
        
    private:
        void setObjPtrData(void* pData);
        
    private:
        void*                       _pObjPtrData;   //!< The buffer of SCObjRefT's buffer
        std::list<SCObject::Ptr>    _objList;       //!< The list of owned objects
    };
}

#endif //__SPEEDCC__SCOBJECT_H__
