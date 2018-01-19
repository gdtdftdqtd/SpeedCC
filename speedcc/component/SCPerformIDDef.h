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
#define MSG_KEY_CONTROLLER     "sc-controller"     // SCController*
#define MSG_KEY_NUMBER         "sc-number"         // int
#define MSG_KEY_NAME           "sc-name"           // SCString
#define MSG_KEY_COMMAND        "sc-command"        // SCString
#define MSG_KEY_STATE          "sc-state"          // ESCState
#define MSG_KEY_IAP            "sc-iap"           // SCString
#define MSG_KEY_CCREF           "sc-cc-ref"        // cocos2d::Ref*
#define MSG_KEY_TOUCH          "sc-touch"           // cocos2d::Touch*
#define MSG_KEY_TOUCHES        "sc-touches"        // std::vector<cocos2d::Touch*>
#define MSG_KEY_DELTA           "sc-delta"         // float
#define MSG_KEY_RESULT          "sc-result"        // for sendMessage() result, relying on specific message definition
    
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
            // key: MSG_KEY_STATE
            kSCMsgInternetReachableChanged,
            
            // key: MSG_KEY_CONTROLLER
            // lisenter: owner scene controller
            kSCMsgSceneEnter,
            
            // key: MSG_KEY_CONTROLLER
            // lisenter: owner scene controller
            kSCMsgSceneEnterTransitionDidFinish,
            
            // key: MSG_KEY_CONTROLLER
            // lisenter: owner scene controller
            kSCMsgSceneExit,
            
            // key: MSG_KEY_CONTROLLER
            // lisenter: owner scene controller
            kSCMsgSceneExitTransitionDidStart,
            
            // key: MSG_KEY_TOUCH       (if single touch)
            // key: "result" => bool  (result from receiver, by defualt is true)
            // key: MSG_KEY_TOUCHES     (if multiple touch)
            // lisenter: owner scene controller
            kSCMsgTouchBegan,
            
            // key: MSG_KEY_TOUCH       (if single touch)
            // key: MSG_KEY_TOUCHES     (if multiple touch)
            // lisenter: owner scene controller
            kSCMsgTouchMoved,
            
            // key: MSG_KEY_TOUCH       (if single touch)
            // key: MSG_KEY_TOUCHES     (if multiple touch)
            // lisenter: owner scene controller
            kSCMsgTouchEnded,
            
            // key: MSG_KEY_TOUCH       (if single touch)
            // key: MSG_KEY_TOUCHES     (if multiple touches)
            // lisenter: owner scene controller
            kSCMsgTouchCancelled,
            
            // key: MSG_KEY_CONTROLLER
            // key: MSG_KEY_CCREF
            kSCMsgButtonClicked,
            
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
            // key: MSG_KEY_DELTA
            kSCMsgFrame,
            
            // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
            kSCMsgModalSceneGotFocus,
            
            // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
            kSCMsgModalSceneLostFocus,
            
            //        // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
            //        kSCMsgPushModalScene,
            
            // MSG_KEY_COMMAND => SCString
            kSCMsgCommand,
            
            // user message define must begin from this value
            // "name" => SCString; required parameter
            kSCMsgUser = 65535
        };
        
        enum Stg
        {
            kSCStgNull  = 0,
            
            kSCStgEmpty,
            
            kSCStgUser = 65535
        };
        
        enum Act
        {
            kSCActNull = 0,
            kSCActDefault,
            
            kSCActUser = 65535
        };
        
    };
}

#endif // __SPEEDCC__SCPERFORMIDDEF_H__
