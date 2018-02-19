

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
            return _pObjPtrData==NULL ? NULL : SCObjPtrT<typename T::type>(_pObjPtrData);
        }
        
        template<typename T>
        SCObjPtrT<typename std::decay<typename std::remove_pointer<T>::type>::type> makeObjPtr(T)
        {
            return _pObjPtrData==NULL ? NULL : SCObjPtrT<typename std::decay<typename std::remove_pointer<T>::type>::type>(_pObjPtrData);
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
