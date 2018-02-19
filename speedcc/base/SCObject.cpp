

#include "SCObject.h"

namespace SpeedCC
{
    SCObject::SCObject():
    _pObjPtrData(NULL)
    {
    }
    
    SCObject::~SCObject()
    {
    }
    
    void SCObject::setObjPtrData(void* pData)
    {
        _pObjPtrData = pData;
    }
    
    void SCObject::addObject(SCObject::Ptr ptrObj)
    {
        SC_RETURN_V_IF(ptrObj==NULL);
        _objList.push_back(ptrObj);
    }
    
    void SCObject::removeObject(SCObject::Ptr ptrObj)
    {
        SC_RETURN_V_IF(ptrObj==NULL);
        _objList.remove_if([ptrObj](SCObject::Ptr ptrIt)
                           {
                               return (ptrIt==ptrObj);
                           });
    }
}
