//
//  SCPerformIDDef.h
//  libspeedcc
//
//  Created by Kevin on 8/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCPERFORMIDDEF_H__
#define __SPEEDCC__SCPERFORMIDDEF_H__

namespace SpeedCC
{
    // for SCMessage parameters in it's Dictionary
#define SC_KEY_CONTROLLER     "sc-controller"     // SCController*
#define SC_KEY_NUMBER         "sc-number"         // int
#define SC_KEY_NAME           "sc-name"           // SCString
#define SC_KEY_COMMAND        "sc-command"        // SCString
#define SC_KEY_STATE          "sc-state"          // ESCState
#define SC_KEY_IAP            "sc-iap"           // SCString
#define SC_KEY_CCREF          "sc-cc-ref"        // SCRef2Ptr::Ptr
#define SC_KEY_TOUCH          "sc-touch"           // cocos2d::Touch*
#define SC_KEY_TOUCHES        "sc-touches"        // std::vector<cocos2d::Touch*>
#define SC_KEY_DELTA          "sc-delta"         // float
#define SC_KEY_RESULT         "sc-result"        // for sendMessage() result, relying on specific message definition
    
// for SCBehavior parameters in it's Dictionary
#define SC_KEY_ACTOR            "sc-actor" // SCActor::Ptr
#define SC_KEY_STRATEGY         "sc-strategy" // SCStrategy::Ptr
#define SC_KEY_ROLE             "sc-role" // SCRole::Ptr
#define SC_KEY_MESSAGE          "sc-message"   // SCMessage::Ptr
    
    struct SCID
    {
        enum Msg
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
            // key: SC_KEY_STATE
            kSCMsgInternetReachableChanged,
            
            // key: SC_KEY_CONTROLLER
            // lisenter: owner scene controller
            kSCMsgSceneEnter,
            
            // key: SC_KEY_CONTROLLER
            // lisenter: owner scene controller
            kSCMsgSceneEnterTransitionDidFinish,
            
            // key: SC_KEY_CONTROLLER
            // lisenter: owner scene controller
            kSCMsgSceneExit,
            
            // key: SC_KEY_CONTROLLER
            // lisenter: owner scene controller
            kSCMsgSceneExitTransitionDidStart,
            
            // key: SC_KEY_TOUCH       (if single touch)
            // key: "result" => bool  (result from receiver, by defualt is true)
            // key: SC_KEY_TOUCHES     (if multiple touch)
            // lisenter: owner scene controller
            kSCMsgTouchBegan,
            
            // key: SC_KEY_TOUCH       (if single touch)
            // key: SC_KEY_TOUCHES     (if multiple touch)
            // lisenter: owner scene controller
            kSCMsgTouchMoved,
            
            // key: SC_KEY_TOUCH       (if single touch)
            // key: SC_KEY_TOUCHES     (if multiple touch)
            // lisenter: owner scene controller
            kSCMsgTouchEnded,
            
            // key: SC_KEY_TOUCH       (if single touch)
            // key: SC_KEY_TOUCHES     (if multiple touches)
            // lisenter: owner scene controller
            kSCMsgTouchCancelled,
            
            // key: SC_KEY_CCREF
            kSCMsgNodeClicked,
            
            kSCMsgSettingMusicChanged,
            kSCMsgSettingSoundChanged,
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
            // delivery: post
            kSCMsgStoreRestoreSuccess,
            
            // IAP restored is failed
            // delivery: post
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
            
            // send this message every frame
            // delivery: send
            // key: SC_KEY_DELTA
            kSCMsgFrame,
            
            // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
            kSCMsgModalSceneGotFocus,
            
            // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
            kSCMsgModalSceneLostFocus,
            
            //        // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
            //        kSCMsgPushModalScene,
            
            // SC_KEY_COMMAND => SCString
            kSCMsgCommand,
        };
        
        enum Stg
        {
            kSCStgNull  = 0,
            
            kSCStgEmpty,
        };
        
        enum Act
        {
            kSCActNull = 0,
            kSCActDefault,
        };
        
        enum {kSCUserID = 65535};
        
    };
}

#endif // __SPEEDCC__SCPERFORMIDDEF_H__
