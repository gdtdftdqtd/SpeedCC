//

#ifndef __SPEEDCC__SCMESSAGEDEF_H__
#define __SPEEDCC__SCMESSAGEDEF_H__

#include "../base/SCBaseCommon.h"

namespace SpeedCC
{
    enum
    {
        // no parameter
        SCMessage_NULL  =  0,
        
        // no parameter
        SCMessage_Quit,
        
        // app new launch
        // no parameter
        SCMessage_AppLaunch,
        
        // game enter foreground
        // no parameter
        SCMessage_AppEnterForeground,
        
        // game enter background
        // no parameter
        SCMessage_AppEnterBackground,
        
        // "number" => int; number of scenes to back
        SCMessage_SceneBack,
        
        // "layer" => cocos2d::Ref*; touch belong to layer
        SCMessage_Touch,
        
        // user message define must begin from this value
        // "name" => SCString; required parameter
        SCMessage_User = 65535
    };
    
    
    struct SSCMessageInfo
    {
        int                 nMsgID;
        SCParameters        paramter;
        bool                bContinue;
        
    public:
        SSCMessageInfo():
        nMsgID(SCMessage_NULL),
        bContinue(true)
        {}
    };

}

#endif // __SPEEDCC__SCMESSAGEDEF_H__
