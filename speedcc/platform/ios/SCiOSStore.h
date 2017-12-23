
#ifndef __SPEEDCC__SCiOSSTORE_H__
#define __SPEEDCC__SCiOSSTORE_H__

#import <UIKit/UIKit.h>

@interface SCiOSStore : NSObject

+(SCiOSStore*) shareStore;

-(id) init;
-(BOOL) purchase:(NSString*)iap;
-(BOOL) restore;
-(void) requestPrice:(NSString*)iap;
@end


#endif // __SPEEDCC__SCiOSSTORE_H__
