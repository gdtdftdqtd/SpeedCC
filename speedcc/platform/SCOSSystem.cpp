

#include "../component/SCMessageDispatch.h"
#include "../base/SCMacroDef.h"

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
            SCMessageInfo mi;
            mi.nMsgID = (nResult==0) ? kSCMsgStorePurchaseSuccess : kSCMsgStorePurchaseFailed;
            mi.paramters.setValue(MSG_KEY_IAP, SCString(pszIAP));
            SCMsgDisp()->postMessage(mi);
        }
        
        // nResult, 0: success; non-zero: failed
        void scbStoreRestoreItemResult(const char* pszIAP,int nResult)
        {
            SCMessageInfo mi;
            mi.nMsgID = ((nResult==0) ? kSCMsgStoreRestoreSuccess : kSCMsgStoreRestoreFailed);
            
            if(pszIAP!=NULL)
            {
                mi.paramters.setValue(MSG_KEY_IAP, SCString(pszIAP));
            }
            SCMsgDisp()->postMessage(mi);
        }
        
        void scbStoreUserCancelled()
        {
            SCMsgDisp()->postMessage(kSCMsgStoreUserCancelled);
        }
        
        // nResult, 0: success; non-zero: failed
        void scbStoreRetrieveItemInfoResult(const char* pszIAP, const char* pszCurrency, float fPrice,int nResult)
        {
            if(nResult==0 && pszIAP!=NULL)
            {// all are fine
                SCMessageInfo mi;
                mi.nMsgID = kSCMsgStoreIAPInfoSuccess;
                mi.paramters.setValue(MSG_KEY_IAP, SCString(pszIAP));
                mi.paramters.setValue("currency", SCString(pszCurrency));
                mi.paramters.setValue("price", fPrice);
                
                SCMsgDisp()->postMessage(mi);
            }
            else if(nResult!=0 && pszIAP!=NULL)
            {// the IAP is invalid
                
            }
            else if(nResult!=0 && pszIAP==NULL)
            {// the retrieve all failed
                SCMsgDisp()->postMessage(kSCMsgStoreIAPInfoFailed);
            }
        }
        
        ///------------- system
        void scbAlertBoxSelected(const int nAlertBoxID,const int nButton)
        {
            SCMessageInfo mi;
            mi.nMsgID = kSCMsgAlertBoxSelected;
            mi.paramters.setValue("id", nAlertBoxID);
            mi.paramters.setValue("selected", nButton);
            SCMsgDisp()->postMessage(mi);
        }
        
        ///------------- app
        void scbAppEnterBackground()
        {
            SCMsgDisp()->postMessage(kSCMsgAppEnterBackground);
        }
        
        void scbAppEnterForeground()
        {
            SCMsgDisp()->postMessage(kSCMsgAppEnterForeground);
        }
        
        void scbAppLaunched()
        {
            SCMsgDisp()->postMessage(kSCMsgAppLaunch);
        }
        
        ///------------- network
        void scbInternetReachableChanged(const bool bNewState)
        {
            
        }
        
#ifdef __cplusplus
    }
#endif  // __cplusplus
}


