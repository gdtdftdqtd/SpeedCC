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
#define MSG_KEY_IAP            "iap"           // SCString
    
    enum
    {
        // no parameter
        kSCMsgNULL  =  0,
        
        // no parameter
        kSCMsgQuit,
        
        // “code”: EErrorCode
        // "message": SCString
        kSCMsgError,
        
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
        kSCMsgInternetReachableChanged,
        
        // show alert box,
        // must block it if want to show customize alert box
        // otherwise will show with system alert box
        // "title" => SCString
        // "message" => SCString
        // "id" => int
        // "button0" => SCString
        // "button1" => SCString (optional)
        // "button2" => SCString (optional)
        kSCMsgShowAlertBox,
        
        // "id" => int
        // "selected" => int
        kSCMsgAlertBoxSelected,
//        // "number" => int; number of scenes to back
//        kSCMsgSceneBack,
        
        // store prcoess cancelled by user
        // no parameter
        kSCMsgStoreUserCancelled,
        
        // IAP purchased is success
        // "iap" => SCString
        kSCMsgStorePurchaseSuccess,
        
        // IAP purchased is failed
        // "iap" => SCString
        kSCMsgStorePurchaseFailed,
        
        // IAP restored is success
        kSCMsgStoreRestoreSuccess,
        
        // IAP restored is failed
        kSCMsgStoreRestoreFailed,
        
        // retrieve IAP success
        // "iap" => SCString
        // "currency" => SCString
        // "price" => float
        kSCMsgStoreIAPInfoSuccess,
        
        // retrieve IAP failed
        kSCMsgStoreIAPInfoFailed,
        
        // "layer" => cocos2d::Ref*; touch belong to layer
//        kSCMsgTouch,
        
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
