

#import <Foundation/Foundation.h>
#include <sys/sysctl.h>

#include "SCiOSStore.h"

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

@implementation SCiOSStore

static SCiOSStore* s_shareStore = nil;

+(SCiOSStore*) shareStore
{
    if(s_shareStore==nil)
    {
        s_shareStore = [[SCiOSStore alloc]init];
    }
    
    return s_shareStore;
}

-(id) init
{
    if(self=[super init])
    {
    }
    
    return self ;
}

-(BOOL) purchase:(NSString*)iap
{
    return NO;
}

-(BOOL) restore
{
    return NO;
}

-(void) requestPrice:(NSString*)iap
{
    
}

@end
