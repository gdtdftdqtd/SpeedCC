//
//  SCSystem.hpp
//  libspeedcc
//
//  Created by Kevin on 11/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSYSTEMUTILS_H__
#define __SPEEDCC__SCSYSTEMUTILS_H__

#include "cocos2d.h"
#include "SCVersion.h"

namespace SpeedCC
{
    class SCSystem
    {
    public:
        enum EScreenSizeType
        {
            kScreenSizeUnkown               = 0,
            kScreenSizeSmall                = 1,
            kScreenSizeMedium               = 2,
            kScreenSizeLarge                = 3,
            kScreenSizeXLarge               = 4,
        };
        
        enum EOSType
        {
            kOSUnknown      = 0,
            kOSiOS          = 1,
            kOSAndroid      = 2,
        };
        
        enum EAssetSizeBitMaskType
        {
            kAssetBitMaskSmall       = (1<<kScreenSizeSmall),
            kAssetBitMaskMedium      = (1<<kScreenSizeMedium),
            kAssetBitMaskLarge       = (1<<kScreenSizeLarge),
            kAssetBitMaskXLarge      = (1<<kScreenSizeXLarge),
        };
        
        enum EDeviceType
        {
            kDeviceUnknown  = 0,
            kDevicePhone    = 1,
            kDeviceTablet   = 2,
            kDeviceTV       = 3,
            kDeviceVehicle  = 4,
        };
        
        enum EStoreType
        {
            kStoreUnknown            = 0,
            kStoreAppStore           = 1,
            kStoreGooglePlay         = 2,
            kStoreAmazon             = 3,
        };
        
        struct SDeviceInfo
        {
            EOSType         osType;
            int             nDistribution; // OS distribution. 0: unkown; 1: offical;
            EDeviceType     deviceType;
            bool            bIsSimulator;
            SCString        strHardware;
        };
        
        static EDeviceType getDeviceType();
        static SCVersion getOSVersion();
        static SCVersion getAppVersion();
        static bool getFreeStorage(unsigned long* pInternal,unsigned long* pExternal=NULL);
        
        static void setMultipleTouch(const bool bEnable);
        static bool getMultipleTouch();
        
        static int getSupportAssetSizeType();
        
        static bool getDeviceInfo(SDeviceInfo& di);
        static SCString getProductName();
        static SCString getBundleID();
        static cocos2d::Size getScreenSize();
        static EScreenSizeType getScreenSizeType();
        static void initSpeedCC(void* pController=NULL);
        static EScreenSizeType getAssetSizeType(const bool bCache=true);
        static void adapterScreenResolution(const bool bCache=true);
        static void log(const char* pszFormat,...);
        
    private:
        static int     s_nSupportAssetType;
    };
}

#endif // __SPEEDCC__SCSYSTEMUTILS_H__
