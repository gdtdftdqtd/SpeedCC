

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacroDef.h"
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
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = (nResult==0) ? SCID::Msg::kSCMsgStorePurchaseSuccess : SCID::Msg::kSCMsgStorePurchaseFailed;
            ptrMsg->paramters.setValue(SC_KEY_IAP, SCString(pszIAP));
            SCMsgDisp()->postMessage(ptrMsg);
        }
        
        // nResult, 0: success; non-zero: failed
        void scbStoreRestoreItemResult(const char* pszIAP,int nResult)
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = ((nResult==0) ? SCID::Msg::kSCMsgStoreRestoreSuccess : SCID::Msg::kSCMsgStoreRestoreFailed);
            
            if(pszIAP!=NULL)
            {
                ptrMsg->paramters.setValue(SC_KEY_IAP, SCString(pszIAP));
            }
            SCMsgDisp()->postMessage(ptrMsg);
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
                SCMessage::Ptr ptrMsg = SCMessage::create();
                ptrMsg->nMsgID = SCID::Msg::kSCMsgStoreIAPInfoSuccess;
                ptrMsg->paramters.setValue(SC_KEY_IAP, SCString(pszIAP));
                ptrMsg->paramters.setValue("currency", SCString(pszCurrency));
                ptrMsg->paramters.setValue("price", fPrice);
                
                SCMsgDisp()->postMessage(ptrMsg);
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
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = SCID::Msg::kSCMsgAlertBoxSelected;
            ptrMsg->paramters.setValue("id", nAlertBoxID);
            ptrMsg->paramters.setValue("selected", nButton);
            SCMsgDisp()->postMessage(ptrMsg);
        }
        
        ///------------- app
        /*
        void scbAppEnterBackground()
        {
            SCMsgDisp()->sendMessage(SCID::Msg::kSCMsgAppEnterBackground);
        }
        
        void scbAppEnterForeground()
        {
            SCMsgDisp()->sendMessage(SCID::Msg::kSCMsgAppEnterForeground);
        }

        
        void scbAppLaunched()
        {
            SCMsgDisp()->sendMessage(SCID::Msg::kSCMsgAppLaunch);
        }
        */
        ///------------- network
        void scbInternetReachableChanged(const bool bNewState)
        {
            
        }
        
#ifdef __cplusplus
    }
#endif  // __cplusplus
}


