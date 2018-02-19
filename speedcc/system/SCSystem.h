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
#include "../SCConfig.h"
#include "../base/SCVersion.h"
#include "../stage/SCBehaviorCocos.h"

namespace SpeedCC
{
    /*
    template<typename T>
    struct SCSystemTmpUtils
    {
        int showAlertBox(const SCString& strTitle,
                         const SCString& strText,
                         const SCString& strButton1,
                         const SCString& strButton2,
                         const SCString& strButton3,
                         const std::function<void(int)>& resultFunc)
        {
            
        }
    };
    
    template<>
    struct SCSystemTmpUtils<SCClassNull>
    {
        int showAlertBox(const SCString& strTitle,
                         const SCString& strText,
                         const SCString& strButton1,
                         const SCString& strButton2,
                         const SCString& strButton3,
                         const std::function<void(int)>& resultFunc)
        {
            int nAlertBoxID = ::rand();
//            const SCDictionary::SPair pairArray[] =
//            {
//                {SC_KEY_TITLE,strTitle},
//                {SC_KEY_TEXT,strText},
//                {SC_KEY_STRING0,strButton1},
//                {SC_KEY_STRING1,strButton2},
//                {SC_KEY_STRING2,strButton3},
//                {SC_KEY_ID,nAlertBoxID},
//            };
//            SCDictionary dic(pairArray,SC_ARRAY_LENGTH(pairArray));
//
//            auto ptrMsg = SCMessage::create(SCID::Msg::kSCMsgShowAlertBox, dic);
//            SCMsgDisp()->postMessage(ptrMsg);
            
            return nAlertBoxID;
        }
    };
    */
    
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
        
        static int showAlertBox(const SCString& strTitle,
                                 const SCString& strText,
                                 const SCString& strButton1,
                                 const SCString& strButton2,
                                 const SCString& strButton3,
                                 const std::function<void(int)>& resultFunc = NULL);
        
        static int showAlertBox(const SCString& strTitle,
                                const SCString& strText,
                                const SCString& strButton1,
                                const std::function<void(int)>& resultFunc = NULL);
        
        static int showAlertBox(const SCString& strTitle,
                                const SCString& strText,
                                const SCString& strButton1,
                                const SCString& strButton2,
                                const std::function<void(int)>& resultFunc = NULL);
        
        template<typename T>
        static int showAlertBox(const SCString& strTitle,
                                const SCString& strText,
                                const SCString& strButton1,
                                const std::function<void(int)>& resultFunc = NULL)
        {
            auto ptrBvr = SCBehaviorSceneNavigate::create<T>(SCSceneNavigator::kSceneModal);
            return SCSystem::showAlertBox(ptrBvr,strTitle,strText,strButton1,"","",resultFunc);
        }
        
        template<typename T>
        static int showAlertBox(const SCString& strTitle,
                                const SCString& strText,
                                const SCString& strButton1,
                                const SCString& strButton2,
                                const std::function<void(int)>& resultFunc = NULL)
        {
            auto ptrBvr = SCBehaviorSceneNavigate::create<T>(SCSceneNavigator::kSceneModal);
            return SCSystem::showAlertBox(ptrBvr,strTitle,strText,strButton1,strButton2,"",resultFunc);
        }
        
        template<typename T>
        static int showAlertBox(const SCString& strTitle,
                                const SCString& strText,
                                const SCString& strButton1,
                                const SCString& strButton2,
                                const SCString& strButton3,
                                const std::function<void(int)>& resultFunc = NULL)
        {
            auto ptrBvr = SCBehaviorSceneNavigate::create<T>(SCSceneNavigator::kSceneModal);
            return SCSystem::showAlertBox(ptrBvr,strTitle,strText,strButton1,strButton2,strButton3,resultFunc);
        }
        
        static bool getDeviceInfo(SDeviceInfo& di);
        static SCString getProductName();
        static SCString getBundleID();
        static ESizeType getScreenSizeType();
        static void initSpeedCC(const int nSupportAssetType=kSCDefaultResolutionAsset);
        static ESizeType getAssetSizeType(const bool bCache=true);
        static void adapterScreenResolution(const bool bCache=true);
        static void log(const char* pszFormat,...);
        
    private:
        static int showAlertBox(SCBehaviorSceneNavigate::Ptr ptrBvr,
                                const SCString& strTitle,
                                const SCString& strText,
                                const SCString& strButton1,
                                const SCString& strButton2= "",
                                const SCString& strButton3 = "",
                                const std::function<void(int)>& resultFunc = NULL);
        
    private:
        static int     s_nSupportAssetType;
    };
}

#endif // __SPEEDCC__SCSYSTEM_H__
