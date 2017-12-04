

#include "SCObject.h"

namespace SpeedCC
{
    SCObject::SCObject():
    _isRefObject(false)
    {
    }
    
    SCObject::SCObject(const bool isRef):
    _isRefObject(isRef)
    {
    }
}
