

#ifndef __SPEEDCC__SCBASEDEF_H__
#define __SPEEDCC__SCBASEDEF_H__

//#include "SCMacroDef.h"
#include "SCString.h"
#include "cocos2d.h"

namespace SpeedCC
{
    ///-------------------- type definition
    enum ESCState
    {
        kSCSTATE_UNKNOWN    = 0,
        kSCSTATE_RUNNING    = 1,
        kSCSTATE_STOPPED    = 2,
        kSCSTATE_PAUSED     = 3,
    };
    
    enum EErrorCode
    {
        kERROR_DEVICE_NOT_SUPPORT_IAP,
    };
    
    ///-------------------- structure definition
    
    struct SErrorInfo
    {
        EErrorCode          code;
        SCString            strMsg;
    };
    
    ///-------------------- function pointer type

    
    
    
}


#endif //__SPEEDCC__SCBASEDEF_H__
