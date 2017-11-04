//



#ifndef __SC__BASECOMMON_H__
#define __SC__BASECOMMON_H__

#include "SCString.h"
#include "SCValue.h"

namespace SpeedCC
{
    ///------------ SCError
    struct SCError
    {
    public:
        enum EErrorCode
        {
            Unkown = -1,
            Success = 0,
        };
        
        SCString        strMessage;
        EErrorCode      ecCode;
    };
    
    
    
    ///------------- SCDictionary
    
}

#endif // __SC__BASECOMMON_H__
