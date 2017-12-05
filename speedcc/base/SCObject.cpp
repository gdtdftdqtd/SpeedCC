

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
}
