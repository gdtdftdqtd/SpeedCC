

#include "../component/SCMessageDispatch.h"
#include "../base/SCMacroDef.h"
#include "../cocos/SCCocosDef.h"

namespace SpeedCC
{
#ifdef __cplusplus
    extern "C"
    {
#endif  // __cplusplus
        
        ///------------ store
        // nResult, 0: success; non-zero: failed
        void scbStorePurchaseItemResult(const char* pszIAP,int nResult)
        {
            SCMessage::Ptr mi = SCMessage::create();
            mi->nMsgID = (nResult==0) ? SCID::Msg::kSCMsgStorePurchaseSuccess : SCID::Msg::kSCMsgStorePurchaseFailed;
            mi->paramters.setValue(MSG_KEY_IAP, SCString(pszIAP));
            SCMsgDisp()->postMessage(mi);
        }
        
        // nResult, 0: success; non-zero: failed
        void scbStoreRestoreItemResult(const char* pszIAP,int nResult)
        {
            SCMessage::Ptr mi = SCMessage::create();
            mi->nMsgID = ((nResult==0) ? SCID::Msg::kSCMsgStoreRestoreSuccess : SCID::Msg::kSCMsgStoreRestoreFailed);
            
            if(pszIAP!=NULL)
            {
                mi->paramters.setValue(MSG_KEY_IAP, SCString(pszIAP));
            }
            SCMsgDisp()->postMessage(mi);
        }
        
        void scbStoreUserCancelled()
        {
            SCMsgDisp()->postMessage(SCID::Msg::kSCMsgStoreUserCancelled);
        }
        
        // nResult, 0: success; non-zero: failed
        void scbStoreRetrieveItemInfoResult(const char* pszIAP, const char* pszCurrency, float fPrice,int nResult)
        {
            if(nResult==0 && pszIAP!=NULL)
            {// all are fine
                SCMessage::Ptr mi = SCMessage::create();
                mi->nMsgID = SCID::Msg::kSCMsgStoreIAPInfoSuccess;
                mi->paramters.setValue(MSG_KEY_IAP, SCString(pszIAP));
                mi->paramters.setValue("currency", SCString(pszCurrency));
                mi->paramters.setValue("price", fPrice);
                
                SCMsgDisp()->postMessage(mi);
            }
            else if(nResult!=0 && pszIAP!=NULL)
            {// the IAP is invalid
                
            }
            else if(nResult!=0 && pszIAP==NULL)
            {// the retrieve all failed
                SCMsgDisp()->postMessage(SCID::Msg::kSCMsgStoreIAPInfoFailed);
            }
        }
        
        ///------------- system
        void scbAlertBoxSelected(const int nAlertBoxID,const int nButton)
        {
            SCMessage::Ptr mi = SCMessage::create();
            mi->nMsgID = SCID::Msg::kSCMsgAlertBoxSelected;
            mi->paramters.setValue("id", nAlertBoxID);
            mi->paramters.setValue("selected", nButton);
            SCMsgDisp()->postMessage(mi);
        }
        
        ///------------- app
        void scbAppEnterBackground()
        {
            SCMsgDisp()->postMessage(SCID::Msg::kSCMsgAppEnterBackground);
        }
        
        void scbAppEnterForeground()
        {
            SCMsgDisp()->postMessage(SCID::Msg::kSCMsgAppEnterForeground);
        }
        
        void scbAppLaunched()
        {
            SCMsgDisp()->postMessage(SCID::Msg::kSCMsgAppLaunch);
        }
        
        ///------------- network
        void scbInternetReachableChanged(const bool bNewState)
        {
            
        }
        
#ifdef __cplusplus
    }
#endif  // __cplusplus
}


