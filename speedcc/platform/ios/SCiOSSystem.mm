


#import "SCiOSSystem.h"

#import <Foundation/Foundation.h>
#import <AdSupport/AdSupport.h>

#include <sys/sysctl.h>

UIViewController* s_rootViewController = nil;

#ifdef __cplusplus
extern "C" {
#endif  // __cplusplus
    
    bool scinGetVersion(NSString* versionString,int* pMajor,int* pMinor,int* pFix);
    
    ///---------------- datetime related
    
    // datetime
    int scGetMonthName(char* pszBuf,const int nBufSize,const int nMonth,const bool bShort)
    {
        int nRet = 0;
        
        if(nMonth<=12 && nMonth>0)
        {
            NSDateFormatter* df = [[NSDateFormatter alloc] init];
            NSString* monthName = [ (bShort ? [df shortMonthSymbols] : [df monthSymbols]) objectAtIndex:(nMonth-1)];
            
            if(pszBuf && monthName.length<nBufSize)
            {
                strcpy(pszBuf,[monthName UTF8String]);
                nRet = (int)monthName.length;
            }
            else if(!pszBuf)
            {
                nRet = (int)monthName.length + 2;
            }
        }
        
        return nRet;
    }
    
    int scGetWeekName(char* pszBuf,const int nBufSize,const int nWeek,const bool bShort)
    {
        int nRet = 0;
        
        if(nWeek<=7 && nWeek>0)
        {
            NSDateFormatter* df = [[NSDateFormatter alloc] init];
            NSString* weekName = [ (bShort ? [df shortWeekdaySymbols] : [df weekdaySymbols]) objectAtIndex:(nWeek-1)];
            
            if(pszBuf && weekName.length<nBufSize)
            {
                strcpy(pszBuf,[weekName UTF8String]);
                nRet = (int)weekName.length;
            }
            else if(!pszBuf)
            {
                nRet = (int)weekName.length + 2;
            }
        }
        
        return nRet;
    }
    
    ////---------------- system related
    void scInitSpeedCC(void* pController)
    {
        s_rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    }
    
    void scSetMultipleTouch(const bool bEnable)
    {
        assert(s_rootViewController!=nil);
        [s_rootViewController.view setMultipleTouchEnabled:bEnable?YES:NO];
    }
    
    bool scGetMultipleTouch()
    {
        assert(s_rootViewController!=nil);
        return s_rootViewController.view.multipleTouchEnabled ? true : false;
    }
    
    bool scGetOSVersion(int* pMajor,int* pMinor,int* pFix)
    {
        return scinGetVersion([UIDevice currentDevice].systemVersion,pMajor,pMinor,pFix);
    }
    
    // OS type. 0: unknown; 1: iOS; 2: Android
    // OS distribution. 0: unkown; 1: offical;
    // device type. 0: unkown; 1: phone; 2: tablet; 3: tv; 4:vehicle;
    // store type. 0:unkown; 1: apple app store; 2: google play; 3: amazon;
    bool scGetDeviceInfo(int* pOSMainType,
                         int* pOSDistributionType,
                         int* pDeviceType,
                         int* pIsSimulator,
                         int* pStoreType,
                         char* pszHwBuffer,
                         const int nHwBufferSize)
    {
        if(pOSMainType)
        {
            *pOSMainType = 1; // iOS
        }
        
        if(pOSDistributionType)
        {
            *pOSDistributionType = 1; // offical
        }
        
        if(pStoreType)
        {
            *pStoreType = 1; // app store
        }
        
        if(pDeviceType)
        {
            switch([UIDevice currentDevice].userInterfaceIdiom)
            {
                case UIUserInterfaceIdiomUnspecified:   *pDeviceType = 0; break;
                case UIUserInterfaceIdiomPhone:         *pDeviceType = 1; break;
                case UIUserInterfaceIdiomPad:           *pDeviceType = 2; break;
                case UIUserInterfaceIdiomTV:            *pDeviceType = 3; break;
                case UIUserInterfaceIdiomCarPlay:       *pDeviceType = 4; break;
            }
        }
        
        if(pszHwBuffer)
        {
            size_t size;
            sysctlbyname("hw.machine", NULL, &size, NULL, 0);
            char* machine = (char*)malloc(size);
            sysctlbyname("hw.machine", machine, &size, NULL, 0);
            NSString *platform = [NSString stringWithUTF8String:machine];
            free(machine);
            
            if(pszHwBuffer && platform.length<nHwBufferSize)
            {
                strcpy(pszHwBuffer,[platform UTF8String]);
            }
        }
        
        if(pIsSimulator)
        {
            *pIsSimulator = [[[UIDevice currentDevice] model] isEqualToString:@"iPhone Simulator"];
        }
        
        return true;
    }
    
    bool scGetFreeStorage(unsigned long* pInternal,unsigned long* pExternal)
    {
        bool bRet = false;
        
        if(pExternal)
        {
            *pExternal = 0;
        }
        
        if(pInternal)
        {
            uint64_t totalSpace = 0;
            uint64_t totalFreeSpace = 0;
            NSError* error = nil;
            NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
            NSDictionary *dictionary = [[NSFileManager defaultManager] attributesOfFileSystemForPath:[paths lastObject]
                                                                                               error: &error];
            
            if (dictionary)
            {
                NSNumber *fileSystemSizeInBytes = [dictionary objectForKey: NSFileSystemSize];
                NSNumber *freeFileSystemSizeInBytes = [dictionary objectForKey:NSFileSystemFreeSize];
                totalSpace = [fileSystemSizeInBytes unsignedLongLongValue];
                totalFreeSpace = [freeFileSystemSizeInBytes unsignedLongLongValue];
                NSLog(@"Memory Capacity of %llu MiB with %llu MiB Free memory available.", ((totalSpace/1024ll)/1024ll), ((totalFreeSpace/1024ll)/1024ll));
                
                *pInternal = totalFreeSpace;
                
                bRet = true;
            }
        }
        
        return bRet;
    }
    
    // 0: unknown; 1: portrait; 2: portrait upside down;
    // 3: landscape right; 4: landscape left
    int scGetDeviceOrientation()
    {
        switch([UIApplication sharedApplication].statusBarOrientation)
        {
            case UIInterfaceOrientationUnknown: return 0;
            case UIInterfaceOrientationPortrait: return 1;
            case UIInterfaceOrientationPortraitUpsideDown: return 2;
            case UIInterfaceOrientationLandscapeLeft: return 4;
            case UIInterfaceOrientationLandscapeRight: return 3;
        }
    }
    
    void scGetScreenSize(float* pWidth, float* pHeight)
    {
        CGRect bounds = [[UIScreen mainScreen]bounds];
        
        bool b = (::scGetDeviceOrientation()<3);
        
        if(pWidth)
        {
            *pWidth = b ? bounds.size.width : bounds.size.height;
        }
        
        if(pHeight)
        {
            *pHeight = b ? bounds.size.height : bounds.size.width;
        }
    }
    
    ///-------- app related
    
    bool scGetAppVersion(int* pMajor,int* pMinor,int* pFix)
    {
        NSString* versionString = [[[NSBundle mainBundle] infoDictionary] objectForKey:@"CFBundleShortVersionString"];
        return scinGetVersion(versionString,pMajor,pMinor,pFix);
    }
    
    int scGetProductName(char* pszBuffer, int nBufferSize)
    {
        NSString *prodName = [[[NSBundle mainBundle] infoDictionary] objectForKey:(NSString *)kCFBundleNameKey];
        
        if(pszBuffer==NULL)
        {
            return (int)prodName.length;
        }
        else
        {
            if(prodName.length<nBufferSize)
            {
                strcpy(pszBuffer,[prodName cStringUsingEncoding:NSUTF8StringEncoding]);
                return (int)prodName.length;
            }
        }
        
        return 0;
    }
    
    int scGetBundleID(char* pszBuffer, const int nBufferSize)
    {
        int nLength = (int)[[NSBundle mainBundle] bundleIdentifier].length;
        
        if(pszBuffer==NULL)
        {
            return nLength;
        }
        else
        {
            if(nBufferSize>nLength)
            {
                strcpy(pszBuffer,[[[NSBundle mainBundle] bundleIdentifier] UTF8String]);
                return nLength;
            }
        }
        
        return 0;
    }
    
    ///---------------- internal functions
    bool scinGetVersion(NSString* versionString,int* pMajor,int* pMinor,int* pFix)
    {
        NSArray *version = [versionString componentsSeparatedByString:@"."];
        
        if(version==nil || version.count<2)
        {
            return false;
        }
        
        if(pMajor)
        {
            *pMajor = [[version objectAtIndex:0] intValue];
        }
        
        if(pMinor)
        {
            *pMinor = [[version objectAtIndex:1] intValue];
        }
        
        if(pFix)
        {
            *pFix = (version.count>2) ? [[version objectAtIndex:2] intValue] : 0;
        }
        
        return true;
    }
    

#ifdef __cplusplus
}
#endif  // __cplusplus

