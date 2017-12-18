

#ifndef __SPEEDCC__SCOBJECT_H__
#define __SPEEDCC__SCOBJECT_H__

#include "SCObjPtrT.h"

namespace SpeedCC
{
    class SCObject
    {
        template<typename T1,bool T2> friend class SCObjPtrT;
        
    public:
        SC_DEFINE_CLASS_PTR(SCObject)
        SCObject();
        virtual ~SCObject();
        
        template<typename T>
        SCObjPtrT<T> makeObjPtr()
        {
            return SCObjPtrT<T>(_pObjPtrData);
        }
        
    private:
        void setObjPtrData(void* pData);
        
    private:
        void*       _pObjPtrData;
    };
}

#endif //__SPEEDCC__SCOBJECT_H__
