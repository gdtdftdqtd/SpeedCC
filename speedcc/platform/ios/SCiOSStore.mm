

#import <Foundation/Foundation.h>

#include <sys/sysctl.h>


#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
    // callback: scbPurchaseItemResult()
    bool scPurchaseItem(const char* pszIAP,const bool bConsumable)
    {
        return false;
    }
    
    // callback: scbPurchaseItemInfoResult()
    void scRequestPurchasedItemInfo(const char* pszIAP)
    {
        
    }
    
    // callback: scbPurchaseRestoreResult()
    bool scRestorePurchased()
    {
        return false;
    }
    

#ifdef __cplusplus
}
#endif  // __cplusplus

