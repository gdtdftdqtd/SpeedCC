//

#ifndef __SPEEDCC__SCMESSAGEDEF_H__
#define __SPEEDCC__SCMESSAGEDEF_H__

#include "../base/SCDictionary.h"

namespace SpeedCC
{
#define MSG_KEY_CONTROLLER     "controller"     // SCController*
#define MSG_KEY_NUMBER         "number"         // int
#define MSG_KEY_NAME           "name"           // SCString
#define MSG_KEY_STATE          "state"          // ESCState
    
    enum
    {
        // no parameter
        kSCMsgNULL  =  0,
        
        // no parameter
        kSCMsgQuit,
        
        // app launch
        // no parameter
        kSCMsgAppLaunch,
        
        // game enter foreground
        // no parameter
        kSCMsgAppEnterForeground,
        
        // game enter background
        // no parameter
        kSCMsgAppEnterBackground,
        
        // internet reachable changed
        // key: MSG_KEY_STATE
        kSCMsg_InternetReachableChanged,
        
        // "number" => int; number of scenes to back
        kSCMsgSceneBack,
        
        // "layer" => cocos2d::Ref*; touch belong to layer
        kSCMsgTouch,
        
        // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
        kSCMsgModalSceneGotFocus,
        
        // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
        kSCMsgModalSceneLostFocus,
        
//        // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
//        kSCMsgPushModalScene,
        
        // user message define must begin from this value
        // "name" => SCString; required parameter
        kSCMsgUser = 65535
    };
    
    
    struct SSCMessageInfo
    {
        int                 nMsgID;
        SCDictionary        paramters;
        bool                bContinue;
        
    public:
        SSCMessageInfo():
        nMsgID(kSCMsgNULL),
        bContinue(true)
        {}
    };

}

#endif // __SPEEDCC__SCMESSAGEDEF_H__
