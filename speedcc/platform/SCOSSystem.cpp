

#include "../component/SCMessageDispatch.h"
#include "../base/SCMacroDef.h"

namespace SpeedCC
{
#ifdef __cplusplus
    extern "C"
    {
#endif  // __cplusplus
        
        ///------------ store
        
        void scbStorePurchaseItemResult(const char* pszIAP,int nResult)
        {
            
        }
        
        void scbStoreItemRestoreResult(const char* pszIAP,int nResult)
        {
            
        }
        
        void scbStoreRetriveItemInfoResult(const char* pszIAP, const char* pszCurrency, float fPrice)
        {
            
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


