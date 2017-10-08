

#ifndef __SC__BASEDEF_H__
#define __SC__BASEDEF_H__

#include "SCMacroDef.h"

namespace SpeedCC
{
    ///-------------------- enum definition
    enum EMessageType
    {
        SCMessage_Unknown   = 0,
        SCMessage_AppLaunch,
        SCMessage_AppEnterBackground,
        SCMessage_AppEnterForeground,
        SCMessage_AppWillTerminate,
        SCMessage_AppWillInactive,
        SCMessage_AppDidActive,
        SCMessage_PageInitCreate,
        SCMessage_PageUILayout,
        
        SCMessage_User
    };
    
    
    ///-------------------- structure definition
    
    ///-------------------- function pointer type
    class SCMessageListener;
    class SCMessageInfo;
    
    typedef void (SCMessageListener::*SCFUN_MessageListen_t)(SCMessageInfo& msg);
}


#endif //__SC__BASEDEF_H__
