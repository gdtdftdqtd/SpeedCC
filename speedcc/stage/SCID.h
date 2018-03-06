/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
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

#ifndef __SPEEDCC__SCID_H__
#define __SPEEDCC__SCID_H__

namespace SpeedCC
{
    // for SCMessage parameters in it's Dictionary
#define SC_KEY_CONTROLLER       "sc-controller"     // SCController*
#define SC_KEY_NUMBER           "sc-number"         // int
#define SC_KEY_NAME             "sc-name"           // SCString
#define SC_KEY_COMMAND          "sc-command"        // SCString
#define SC_KEY_STATE            "sc-state"          // ESCState
#define SC_KEY_CCREF            "sc-cc-ref"        // SCRef2Ptr::Ptr
#define SC_KEY_DELTA            "sc-delta"         // float
#define SC_KEY_RESULT           "sc-result"        // for sendMessage() result, relying on specific message definition
#define SC_KEY_ID               "sc-id"     // int
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
#define SC_KEY_IAP_PRODUCT              "sc-iap"           // SCString
#define SC_KEY_PRICE            "sc-price" // SCString
#define SC_KEY_CURRENCY         "sc-currency" // SCString
    
    // touch
#define SC_KEY_TOUCH            "sc-touch"           // cocos2d::Touch*
#define SC_KEY_TOUCHES          "sc-touches"        // std::vector<cocos2d::Touch*>
#define SC_KEY_CCEVENT          "sc-cc-event"       // cocos2d::Event*
    
    // acceleration
#define SC_KEY_X                "sc-x" // double or float
#define SC_KEY_Y                "sc-y" // double or float
#define SC_KEY_Z                "sc-z" // double or float
#define SC_KEY_TIMESTAMP        "sc-timestamp" // double
    
    // keyboard
#define SC_KEY_KEYBOARDCODE     "sc-keyboard-code"  // cocos2d::EventKeyboard::KeyCode
    
    struct SCID
    {
        enum Msg
        {
            // no parameter
            kMsgNULL  =  0,
            
            // no parameter
            kMsgQuit,
            
            // “code”: EErrorCode
            // "message": SCString
            kMsgError,
            
            // app launch
            // no parameter
            kMsgAppLaunch,
            
            // game enter foreground
            // no parameter
            kMsgAppEnterForeground,
            
            // game enter background
            // no parameter
            kMsgAppEnterBackground,
            
            // internet reachable changed
            // key: SC_KEY_STATE
            kMsgInternetReachableChanged,
            
            // key: SC_KEY_CONTROLLER
            // lisenter: owner scene controller
            kMsgSceneEnter,
            
            // key: SC_KEY_CONTROLLER
            // lisenter: owner scene controller
            kMsgSceneEnterTransitionDidFinish,
            
            // key: SC_KEY_CONTROLLER
            // lisenter: owner scene controller
            kMsgSceneExit,
            
            // key: SC_KEY_CONTROLLER
            // lisenter: owner scene controller
            kMsgSceneExitTransitionDidStart,
            
            // key: SC_KEY_TOUCH       (for single touch)
            // key: SC_RESULT  (result from receiver, by defualt is true)
            // key: SC_KEY_TOUCHES     (for multiple touch)
            // key: SC_KEY_CCEVENT
            // lisenter: owner scene controller
            kMsgTouchBegan,
            
            // key: SC_KEY_TOUCH       (for single touch)
            // key: SC_KEY_TOUCHES     (for multiple touch)
            // key: SC_KEY_CCEVENT
            // lisenter: owner scene controller
            kMsgTouchMoved,
            
            // key: SC_KEY_TOUCH       (for single touch)
            // key: SC_KEY_TOUCHES     (for multiple touch)
            // key: SC_KEY_CCEVENT
            // lisenter: owner scene controller
            kMsgTouchEnded,
            
            // key: SC_KEY_TOUCH       (for single touch)
            // key: SC_KEY_TOUCHES     (for multiple touches)
            // key: SC_KEY_CCEVENT
            // lisenter: owner scene controller
            kMsgTouchCancelled,
            
            // key: SC_KEY_X
            // key: SC_KEY_Y
            // key: SC_KEY_Z
            // key: SC_KEY_TIMESTAMP
            // key: SC_KEY_CCEVENT
            kMsgAcceleration,
            
            // key: SC_KEY_KEYBOARDCODE
            // key: SC_KEY_CCEVENT
            kMsgKeyboardKeyDown,
            
            // key: SC_KEY_KEYBOARDCODE
            // key: SC_KEY_CCEVENT
            kMsgKeyboardKeyUp,
            
            // key: SC_KEY_CCREF
            kMsgNodeClicked,
            
            kMsgSettingMusicChanged,
            kMsgSettingSoundChanged,
            // show alert box,
            // must block it if want to show customize alert box
            // otherwise will show with system alert box
            // SC_KEY_TITLE => SCString
            // SC_KEY_TEXT => SCString
            // SC_KEY_ID => int
            // SC_KEY_STRING0 => SCString
            // SC_KEY_STRING1 => SCString (optional)
            // SC_KEY_STRING2 => SCString (optional)
//            kMsgShowAlertBox,
            
            // SC_KEY_ID => int
            // SC_KEY_RESULT => int
            kMsgAlertBoxSelected,
            //        // "number" => int; number of scenes to back
            //        kMsgSceneBack,
            
            // store prcoess cancelled by user
            // no parameter
            kMsgStoreUserCancelled,
            
            // IAP purchased is success
            // SC_KEY_IAP_PRODUCT => SCString
            kMsgStorePurchaseSuccess,
            
            // IAP purchased is failed
            // SC_KEY_IAP_PRODUCT => SCString
            kMsgStorePurchaseFailed,
            
            // IAP restored is success
            // delivery: post
            kMsgStoreRestoreSuccess,
            
            // IAP restored is failed
            // delivery: post
            kMsgStoreRestoreFailed,
            
            // retrieve IAP success
            // SC_KEY_IAP_PRODUCT => SCString
            // SC_KEY_CURRENCY => SCString
            // SC_KEY_PRICE => float
            kMsgStoreIAPInfoSuccess,
            
            // retrieve IAP failed
            kMsgStoreIAPInfoFailed,
            
            // "layer" => cocos2d::Ref*; touch belong to layer
            //        kMsgTouch,
            
            // send this message every frame
            // delivery: send
            // key: SC_KEY_DELTA
            kMsgFrame,
            
            // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
            kMsgModalSceneGotFocus,
            
            // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
            kMsgModalSceneLostFocus,
            
            //        // MSG_ARG_KEY_CONTROLLER/"controller" => SCSceneController*
            //        kMsgPushModalScene,
            
            // SC_KEY_COMMAND => SCString
            kMsgCommand,
        };
        
        enum Stg
        {
            kStgNull  = 0,
            
            kStgEmpty,
        };
        
        enum Act
        {
            kActNull = 0,
            kActDefault,
        };
        
        enum {kUserID = 65535};
        
    };
}

#endif // __SPEEDCC__SCID_H__
