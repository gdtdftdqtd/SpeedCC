/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#ifndef __SPEEDCC__SCSYSTEM_H__
#define __SPEEDCC__SCSYSTEM_H__

#include "cocos2d.h"
#include "../base/SCVersion.h"
#include "../stage/SCBehaviorCocos.h"

namespace SpeedCC
{   
    class SCSystem final
    {
    public:
        enum EResolutionType
        {
            kResolutionUnkown               = 0,
            kResolutionSmall                = 1,
            kResolutionMedium               = 2,
            kResolutionLarge                = 3,
            kResolutionXLarge               = 4,
        };
        
        enum EOSType
        {
            kOSUnknown      = 0,
            kOSiOS          = 1,
            kOSAndroid      = 2,
        };
        
        enum EResolutionSizeBitMaskType
        {
            kResolutionBitMaskSmall       = (1<<kResolutionSmall),
            kResolutionBitMaskMedium      = (1<<kResolutionMedium),
            kResolutionBitMaskLarge       = (1<<kResolutionLarge),
            kResolutionBitMaskXLarge      = (1<<kResolutionXLarge),
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
            auto ptrBvr = SCBehaviorSceneGoto::create<T>(SCSceneNavigator::kSceneModal);
            return SCSystem::showAlertBox(ptrBvr,strTitle,strText,strButton1,"","",resultFunc);
        }
        
        template<typename T>
        static int showAlertBox(const SCString& strTitle,
                                const SCString& strText,
                                const SCString& strButton1,
                                const SCString& strButton2,
                                const std::function<void(int)>& resultFunc = NULL)
        {
            auto ptrBvr = SCBehaviorSceneGoto::create<T>(SCSceneNavigator::kSceneModal);
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
            auto ptrBvr = SCBehaviorSceneGoto::create<T>(SCSceneNavigator::kSceneModal);
            return SCSystem::showAlertBox(ptrBvr,strTitle,strText,strButton1,strButton2,strButton3,resultFunc);
        }
        
        static bool getDeviceInfo(SDeviceInfo& di);
        static SCString getProductName();
        static SCString getBundleID();
        static EResolutionType getScreenSizeType();
        static void initSpeedCC(const int nSupportAssetType);
        static EResolutionType getAssetSizeType(const bool bCache=true);
        static void adapterScreenResolution(const bool bCache=true);
        static void log(const char* pszFormat,...);
        
    private:
        static int showAlertBox(SCBehaviorSceneGoto::Ptr ptrBvr,
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
