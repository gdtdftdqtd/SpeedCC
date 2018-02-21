/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

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
#define SC_KEY_CCREF          "sc-cc-ref"        // SCRef2Ptr::Ptr
#define SC_KEY_TOUCH          "sc-touch"           // cocos2d::Touch*
#define SC_KEY_TOUCHES        "sc-touches"        // std::vector<cocos2d::Touch*>
#define SC_KEY_DELTA          "sc-delta"         // float
#define SC_KEY_RESULT         "sc-result"        // for sendMessage() result, relying on specific message definition
#define SC_KEY_ID             "sc-id"     // int
#define SC_KEY_FINISHFUNC       "sc-finish-func"    // SCSceneController::FinishFunc_t
    
    // for SCBehavior parameters in it's Dictionary
#define SC_KEY_ACTOR            "sc-actor" // SCActor::Ptr
#define SC_KEY_STRATEGY         "sc-strategy" // SCStrategy::Ptr
#define SC_KEY_ROLE             "sc-role" // SCRole::Ptr
#define SC_KEY_MESSAGE          "sc-message"   // SCMessage::Ptr
    
    // alertbox
#define SC_KEY_TITLE            "sc-title" // SCString
#define SC_KEY_TEXT             "sc-text"   // SCString
#define SC_KEY_STRING0          "sc-button0"    // SCString
#define SC_KEY_STRING1          "sc-button1"    // SCString
#define SC_KEY_STRING2          "sc-button2"    // SCString
    
    // IAP
#define SC_KEY_IAP              "sc-iap"           // SCString
#define SC_KEY_PRICE            "sc-price" // SCString
#define SC_KEY_CURRENCY         "sc-currency" // SCString
    
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
            // SC_KEY_TITLE => SCString
            // SC_KEY_TEXT => SCString
            // SC_KEY_ID => int
            // SC_KEY_STRING0 => SCString
            // SC_KEY_STRING1 => SCString (optional)
            // SC_KEY_STRING2 => SCString (optional)
//            kSCMsgShowAlertBox,
            
            // SC_KEY_ID => int
            // SC_KEY_RESULT => int
            kSCMsgAlertBoxSelected,
            //        // "number" => int; number of scenes to back
            //        kSCMsgSceneBack,
            
            // store prcoess cancelled by user
            // no parameter
            kSCMsgStoreUserCancelled,
            
            // IAP purchased is success
            // SC_KEY_IAP => SCString
            kSCMsgStorePurchaseSuccess,
            
            // IAP purchased is failed
            // SC_KEY_IAP => SCString
            kSCMsgStorePurchaseFailed,
            
            // IAP restored is success
            // delivery: post
            kSCMsgStoreRestoreSuccess,
            
            // IAP restored is failed
            // delivery: post
            kSCMsgStoreRestoreFailed,
            
            // retrieve IAP success
            // SC_KEY_IAP => SCString
            // SC_KEY_CURRENCY => SCString
            // SC_KEY_PRICE => float
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
