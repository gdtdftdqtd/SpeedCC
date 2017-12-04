

#ifndef __SPEEDCC__SCOBJECT_H__
#define __SPEEDCC__SCOBJECT_H__

#include "SCObjPtrT.h"

namespace SpeedCC
{
    class SCObject
    {
    public:
        SC_DEFINE_CLASS_PTR(SCObject);
        SCObject();
        SCObject(const bool isRef);
        
//        template<typename T>
//        typename T::Ptr cast()
//        {
//            if(_isRefObject && dynamic_cast<T*>(this))
//            {
//                SCObjPtrT<T> ret(this);
//                ret.increaseRef();
//                return ret;
//            }
//
//            return NULL;
//        }
        
    private:
        bool    _isRefObject;
    };
}

#endif //__SPEEDCC__SCOBJECT_H__
