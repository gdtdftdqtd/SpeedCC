
#ifndef __SC__SCiOSSYSTEM_H__
#define __SC__SCiOSSYSTEM_H__

#import <UIKit/UIKit.h>

@interface SCiOSSystem : NSObject

+(SCiOSSystem*) sharedSystem;
-(id)init;
-(void)showAlertView:(NSString*)title
            message:(NSString*)message
            button1:(NSString*)button1
            button2:(NSString*)button2
            button3:(NSString*)button3
           buttonID:(int)buttonID;

@end


#endif // __SC__SCiOSSYSTEM_H__
