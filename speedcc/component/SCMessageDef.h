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
        
        // MSG_KEY_COMMAND => SCString
        kSCMsgUserCommand,
        
        // user message define must begin from this value
        // "name" => SCString; required parameter
        kSCMsgUser = 65535
    };
    
    
    struct SCMessageInfo
    {
        int                 nMsgID;
        SCDictionary        paramters;
        bool                bContinue;
        
        SCMessageInfo():
        nMsgID(kSCMsgNULL),
        bContinue(true)
        {}
        
        inline bool operator==(const SCMessageInfo& mi) const
        {
            return (nMsgID==mi.nMsgID);
        }
        
        inline bool operator<(const SCMessageInfo& mi) const
        {
            return (nMsgID<mi.nMsgID);
        }
        
        inline bool operator>(const SCMessageInfo& mi) const
        {
            return (nMsgID>mi.nMsgID);
        }
    };
    
    class SCMessageMatcher : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCMessageMatcher)
        SC_DEFINE_CLASS_PTR(SCMessageMatcher)
        
        SC_DEFINE_CREATE_FUNC2(SCMessageMatcher,const int,const std::function<bool (const SCMessageInfo& mi)>&)
//        SC_DEFINE_CREATE_FUNC2(SCMessageMatcher,const SCString&,const std::function<bool (const SCMessageInfo& mi)>&)
        
        bool isMatch(const SCMessageInfo& mi) const
        {
            if(_func==NULL || _nMsgID!=mi.nMsgID)
            {
                return false;
            }
            
            return _func(mi);
        }
        
        inline int getCommand() const { return _nCommand; }
        inline int getMessageID() const { return _nMsgID; }
        
    protected:
        SCMessageMatcher(const int nMsgID,const std::function<bool (const SCMessageInfo& mi)>& func):
        _nMsgID(nMsgID),
        _func(func)
        {
        }
        
//        SCMessageMatcher(const SCString& strCommand,const std::function<bool (const SCMessageInfo& mi)>& func):
//        _strCommand(strCommand),
//        _nMsgID(kSCMsgUserCommand),
//        _func(func)
//        {
//        }
        
    private:
        int                                             _nCommand;
        int                                             _nMsgID;
        std::function<bool (const SCMessageInfo& mi)>   _func;
    };

}

#endif // __SPEEDCC__SCMESSAGEDEF_H__
