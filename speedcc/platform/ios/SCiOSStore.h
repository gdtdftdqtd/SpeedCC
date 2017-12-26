
#ifndef __SPEEDCC__SCiOSSTORE_H__
#define __SPEEDCC__SCiOSSTORE_H__

#import <UIKit/UIKit.h>
#import <StoreKit/StoreKit.h>

@interface SCiOSStore : NSObject<SKPaymentTransactionObserver,SKRequestDelegate, SKProductsRequestDelegate>
{
    NSMutableDictionary*     _productID2ProductDic;
}

typedef NS_ENUM(NSInteger, IAPPurchaseNotificationStatus)
{
    IAPPurchaseFailed, // Indicates that the purchase was unsuccessful
    IAPPurchaseSucceeded, // Indicates that the purchase was successful
    IAPRestoredFailed, // Indicates that restoring products was unsuccessful
    IAPRestoredSucceeded, // Indicates that restoring products was successful
};

+(SCiOSStore*) sharedStore;

-(id) init;
-(BOOL) purchase:(NSString*)iap;
-(BOOL) restore;
-(void) requestIAPInfo:(NSArray<NSString*>*)iapArray;
@end


#endif // __SPEEDCC__SCiOSSTORE_H__
