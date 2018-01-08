//

#ifndef __SPEEDCC__SCMESSAGEDEF_H__
#define __SPEEDCC__SCMESSAGEDEF_H__

#include "../base/SCDictionary.h"
#include "../base/SCObject.h"

namespace SpeedCC
{
#define MSG_KEY_CONTROLLER     "controller"     // SCController*
#define MSG_KEY_NUMBER         "number"         // int
#define MSG_KEY_NAME           "name"           // SCString
#define MSG_KEY_COMMAND        "command"        // SCString
#define MSG_KEY_STATE          "state"          // ESCState
#define MSG_KEY_IAP            "iap"           // SCString
#define MSG_KEY_TOUCH          "touch"           // cocos2d::Touch*
#define MSG_KEY_TOUCHES        "touches"        // std::vector<cocos2d::Touch*>
    
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
        // key: MSG_KEY_TOUCHES     (if multiple touch)
        // lisenter: owner scene controller
        kSCMsgTouchCancelled,
        
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
    
    
    struct SCMessage : public SCObject
    {
    protected:
        SCMessage():
        nMsgID(kSCMsgNULL),
        bContinue(true)
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCMessage)
        SC_DEFINE_CLASS_PTR(SCMessage)
        
        SC_DEFINE_CREATE_FUNC_0(SCMessage)
        
        int                 nMsgID;
        SCDictionary        paramters;
        bool                bContinue;
    };
    
    class SCMessageMatcher : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCMessageMatcher)
        SC_DEFINE_CLASS_PTR(SCMessageMatcher)
        
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcher,const int,const std::function<bool (const SCMessage::Ptr mi)>&)
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcher,const SCString&,const std::function<bool (const SCMessage::Ptr mi)>&)
        
        bool isMatch(const SCMessage::Ptr mi) const
        {
            if(_func==NULL || mi==NULL || _nMsgID!=mi->nMsgID)
            {
                return false;
            }
            
            if(_nMsgID==kSCMsgCommand)
            {
                if(_strCommand.isEmpty())
                {
                    return false;
                }
                
                auto value = mi->paramters.getValue(MSG_KEY_COMMAND);
                if(!value.isValidObject<SCString>())
                {
                    return false;
                }
                
                auto command = value.getString();
                if(command!=_strCommand)
                {
                    return false;
                }
            }
            
            return _func(mi);
        }
        
        inline SCString getCommand() const { return _strCommand; }
        inline int getMessageID() const { return _nMsgID; }
        
    protected:
        SCMessageMatcher(const int nMsgID,const std::function<bool (SCMessage::Ptr mi)>& func):
        _nMsgID(nMsgID),
        _func(func)
        {
        }
        
        SCMessageMatcher(const SCString& strCommand,const std::function<bool (SCMessage::Ptr mi)>& func):
        _strCommand(strCommand),
        _nMsgID(kSCMsgCommand),
        _func(func)
        {
        }
        
    private:
        SCString                                        _strCommand;
        int                                             _nMsgID;
        std::function<bool (SCMessage::Ptr mi)>     _func;
    };

}

#endif // __SPEEDCC__SCMESSAGEDEF_H__
