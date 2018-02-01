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
#include "../SCConfig.h"

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
        
        enum EDeviceManufacture
        {
            kDeviceManufactureUnknown       = 0,
            kDeviceManufactureApple         = 1,
            kDeviceManufactureGoogle        = 2,
            kDeviceManufactureSamsung       = 3,
            kDeviceManufactureHuawei        = 4,
            kDeviceManufactureLGE           = 5,
            kDeviceManufactureOnePlus       = 6,
            kDeviceManufactureSony          = 7,
            kDeviceManufactureXiaomi        = 8,
            kDeviceManufactureMeizu         = 9,
            kDeviceManufactureAmazon        = 10,
        };
        
        struct SDeviceInfo
        {
            EOSType                 osType;
            int                     manufacture; // EDeviceManufacture
            EDeviceType             deviceType;
            bool                    bIsSimulator;
            SCString                strHardware;
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
        static ESizeType getScreenSizeType();
        static void initSpeedCC(const int nSupportAssetType=kSCDefaultResolutionAsset);
        static ESizeType getAssetSizeType(const bool bCache=true);
        static void adapterScreenResolution(const bool bCache=true);
        static void log(const char* pszFormat,...);
        
    private:
        static int     s_nSupportAssetType;
    };
}

#endif // __SPEEDCC__SCSYSTEM_H__
