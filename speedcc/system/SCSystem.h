//
//  SCSystem.hpp
//  libspeedcc
//
//  Created by Kevin on 11/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSYSTEM_H__
#define __SPEEDCC__SCSYSTEM_H__

#include "cocos2d.h"
#include "../base/SCVersion.h"

namespace SpeedCC
{
    class SCSystem final
    {
    public:
        enum ESizeType
        {
            kSizeUnkown               = 0,
            kSizeSmall                = 1,
            kSizeMedium               = 2,
            kSizeLarge                = 3,
            kSizeXLarge               = 4,
        };
        
        enum EOSType
        {
            kOSUnknown      = 0,
            kOSiOS          = 1,
            kOSAndroid      = 2,
        };
        
        enum EAssetSizeBitMaskType
        {
            kAssetBitMaskSmall       = (1<<kSizeSmall),
            kAssetBitMaskMedium      = (1<<kSizeMedium),
            kAssetBitMaskLarge       = (1<<kSizeLarge),
            kAssetBitMaskXLarge      = (1<<kSizeXLarge),
        };
        
        enum EDeviceType
        {
            kDeviceUnknown  = 0,
            kDevicePhone    = 1,
            kDeviceTablet   = 2,
            kDeviceTV       = 3,
            kDeviceVehicle  = 4,
            kDeviceDesktop  = 5,
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
        static void setSupportAssetSizeType(int type);
        static void setGlobalDisableTouch(const bool bDisable);
        static bool getGlobalDisableTouch();
        
        static bool getDeviceInfo(SDeviceInfo& di);
        static SCString getProductName();
        static SCString getBundleID();
        static cocos2d::Size getScreenSize();
        static ESizeType getScreenSizeType();
        static void initSpeedCC();
        static ESizeType getAssetSizeType(const bool bCache=true);
        static void adapterScreenResolution(const bool bCache=true);
        static void log(const char* pszFormat,...);
        
    private:
        static int     s_nSupportAssetType;
    };
}

#endif // __SPEEDCC__SCSYSTEM_H__
