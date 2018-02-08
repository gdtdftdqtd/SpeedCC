//
//  SCSystem.cpp
//  libspeedcc
//
//  Created by Kevin on 11/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCSystem.h"
#include "SCMacroDef.h"

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacroDef.h"
#include "../platform/SCOSSystem.h"
#include "../cocos/SCCocosDef.h"
#include "../cocos/SCScene.h"

#include <iostream>

using namespace cocos2d;

namespace SpeedCC
{
    int SCSystem::s_nSupportAssetType = kSCDefaultResolutionAsset;
    
    void SCSystem::setMultipleTouch(const bool bEnable)
    {
        ::scSetMultipleTouch(bEnable);
    }
    
    bool SCSystem::getMultipleTouch()
    {
        return ::scGetMultipleTouch();
    }
    
    void SCSystem::setGlobalDisableTouch(const bool bDisable)
    {
        auto pScene = SCCCDirector()->getRunningScene();
        const bool bHas = (pScene->getChildByTag(SCLayerDisableTouch::kTAG)!=NULL);
        
        if(bDisable && !bHas)
        {
            auto pLayer = SCLayerDisableTouch::create();
            pScene->addChild(pLayer);
        }
        else if(!bDisable && bHas)
        {
            pScene->removeChildByTag(SCLayerDisableTouch::kTAG);
        }
    }
    
    bool SCSystem::getGlobalDisableTouch()
    {
        auto pScene = SCCCDirector()->getRunningScene();
        return (pScene->getChildByTag(SCLayerDisableTouch::kTAG)!=NULL);
    }
    
    SCString SCSystem::getProductName()
    {
        char szBuffer[64+1] = {0};
        ::scGetProductName(szBuffer,SC_ARRAY_LENGTH(szBuffer));
        return szBuffer;
    }
    
    SCString SCSystem::getBundleID()
    {
        char szBuffer[64+1] = {0};
        ::scGetBundleID(szBuffer,SC_ARRAY_LENGTH(szBuffer));
        return szBuffer;
    }
    
    SCVersion SCSystem::getOSVersion()
    {
        SCVersion ret;
        ::scGetOSVersion(&ret.nMajor,&ret.nMinor,&ret.nFix);
        return ret;
    }
    
    SCVersion SCSystem::getAppVersion()
    {
        SCVersion ret;
        ::scGetAppVersion(&ret.nMajor,&ret.nMinor,&ret.nFix);
        return ret;
    }
    
    bool SCSystem::getFreeStorage(unsigned long* pInternal,unsigned long* pExternal)
    {
        return ::scGetFreeStorage(pInternal,pExternal);
    }
    
    int SCSystem::getSupportAssetSizeType()
    {
        return s_nSupportAssetType;
    }
    
    void SCSystem::setSupportAssetSizeType(int type)
    {
        const bool b = (s_nSupportAssetType==type);
        s_nSupportAssetType = type;
        
        if(!b)
        {
            SCSystem::adapterScreenResolution(false);
        }
    }
    
    bool SCSystem::getDeviceInfo(SDeviceInfo& di)
    {
        int nOS = 0;
        int nDistribution = 0;
        int nDeviceType = 0;
        int nIsSimulator = 0;
        int nStoreType = 0;
        char szHardware[64+1] = {0};
        
        bool bRet = ::scGetDeviceInfo(&nOS,
                                      &nDistribution,
                                      &nDeviceType,
                                      &nIsSimulator,
                                      &nStoreType,
                                      szHardware,
                                      SC_ARRAY_LENGTH(szHardware));
        
        switch(nOS)
        {
            case 1: di.osType = kOSiOS; break;
            case 2: di.osType = kOSAndroid; break;
            default: di.osType = kOSUnknown; break;
        }
        
        di.manufacture = nDistribution;
        
        // device type. 0: unkown; 1: phone; 2: tablet; 3: tv; 4:vehicle; 5: desktop
        switch(di.deviceType)
        {
            case 1: di.deviceType = kDevicePhone; break;
            case 2: di.deviceType = kDeviceTablet; break;
            case 3: di.deviceType = kDeviceTV; break;
            case 4: di.deviceType = kDeviceVehicle; break;
            case 5: di.deviceType = kDeviceDesktop; break;
            default: di.deviceType = kDeviceUnknown; break;
        }
        
        di.bIsSimulator = (nIsSimulator!=0);
        
        return bRet;
    }
    
    SCSystem::ESizeType SCSystem::getScreenSizeType()
    {
        static ESizeType      _screenSizeType = kSizeUnkown;
        
        SC_RETURN_IF(_screenSizeType!=kSizeUnkown,_screenSizeType);
        
        const cocos2d::Size& screenSize = SCScreenSize;
        
        const int nScreenSquare = screenSize.width * screenSize.height*CC_CONTENT_SCALE_FACTOR()*CC_CONTENT_SCALE_FACTOR();
        
        const int nDiffOfXLarge = abs(nScreenSquare - kSCWidthOfAssetDesignXLarge*kSCHeightOfAssetDesignXLarge);
        const int nDiffOfLarge = abs(nScreenSquare - kSCWidthOfAssetDesignLarge*kSCHeightOfAssetDesignLarge);
        const int nDiffOfMedium = abs(nScreenSquare - kSCWidthOfAssetDesignMedium*kSCHeightOfAssetDesignMedium);
        const int nDiffOfSmall = abs(nScreenSquare - kSCWidthOfAssetDesignSmall*kSCHeightOfAssetDesignSmall);
        
        int nMinimum = std::min(nDiffOfXLarge,std::min(nDiffOfLarge,std::min(nDiffOfMedium,nDiffOfSmall)));
        
        SCString strScreenSize(0,"%d x %d",(int)screenSize.width,(int)screenSize.height);
        if(nMinimum==nDiffOfXLarge)
        {
            SCLog("Detected Screen Size is 'XLarge'. %s",strScreenSize.c_str());
            _screenSizeType = kSizeXLarge;
        }
        else if(nMinimum==nDiffOfLarge)
        {
            SCLog("Detected Screen Size is 'Large'. %s",strScreenSize.c_str());
            _screenSizeType = kSizeLarge;
        }
        else if(nMinimum==nDiffOfMedium)
        {
            SCLog("Detected Screen Size is 'Medium'. %s",strScreenSize.c_str());
            _screenSizeType = kSizeMedium;
        }
        else
        {
            SCASSERT(nMinimum==nDiffOfSmall);
            SCLog("Detected Screen Size is 'Small'. %s",strScreenSize.c_str());
            _screenSizeType = kSizeSmall;
        }
        
        return _screenSizeType;
    }
    
    SCSystem::ESizeType SCSystem::getAssetSizeType(const bool bCache)
    {
        static ESizeType      _resourceSizeType = kSizeUnkown;
        
        SC_RETURN_IF(_resourceSizeType!=kSizeUnkown && bCache,_resourceSizeType);
        
        const ESizeType screenSize = SCSystem::getScreenSizeType();
        
        switch(screenSize)
        {
            case kSizeXLarge:
            {
                if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge))
                {
                    SCLog("Using 'XLarge' Resolution Assets");
                    _resourceSizeType = kSizeXLarge;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskLarge))
                {
                    SCLog("Using 'Large' Resolution Assets");
                    _resourceSizeType = kSizeLarge;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskMedium))
                {
                    SCLog("Using 'Medium' Resolution Assets");
                    _resourceSizeType = kSizeMedium;
                }
                else
                {
                    SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskSmall));
                    SCLog("Using 'Small' Resolution Assets");
                    _resourceSizeType = kSizeSmall;
                }
            }
                break;
                
            case kSizeLarge:
            {
                if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskLarge))
                {
                    SCLog("Using 'Large' Resolution Assets");
                    _resourceSizeType = kSizeLarge;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskMedium))
                {
                    SCLog("Using 'Medium' Resolution Assets");
                    _resourceSizeType = kSizeMedium;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge))
                {
                    SCLog("Using 'XLarge' Resolution Assets");
                    _resourceSizeType = kSizeXLarge;
                }
                else
                {
                    SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskSmall));
                    SCLog("Using 'Small' Resolution Assets");
                    _resourceSizeType = kSizeSmall;
                }
            }
                break;
                
            case kSizeMedium:
            {
                if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskMedium))
                {
                    SCLog("Using 'Medium' Resolution Assets");
                    _resourceSizeType = kSizeMedium;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskSmall))
                {
                    SCLog("Using 'Small' Resolution Assets");
                    _resourceSizeType = kSizeSmall;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskLarge))
                {
                    SCLog("Using 'Large' Resolution Assets");
                    _resourceSizeType = kSizeLarge;
                }
                else
                {
                    SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge));
                    SCLog("Using 'XLarge' Resolution Assets");
                    _resourceSizeType = kSizeXLarge;
                }
            }
                break;
                
            case kSizeSmall:
            {
                if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskSmall))
                {
                    SCLog("Using 'Small' Resolution Assets");
                    _resourceSizeType = kSizeSmall;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskMedium))
                {
                    SCLog("Using 'Medium' Resolution Assets");
                    _resourceSizeType = kSizeMedium;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskLarge))
                {
                    SCLog("Using 'Large' Resolution Assets");
                    _resourceSizeType = kSizeLarge;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge))
                {
                    SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge));
                    SCLog("Using 'XLarge' Resolution Assets");
                    _resourceSizeType = kSizeXLarge;
                }
            }
                break;
                
            default:
                SCASSERT(false);
                break;
        }
        
        return _resourceSizeType;
    }
    
    void SCSystem::initSpeedCC(const int nSupportAssetType)
    {
        SCLog("SpeedCC v%d.%d.%d",(int)SPEEDCC_VERSION_MAJOR,(int)SPEEDCC_VERSION_MINOR,(int)SPEEDCC_VERSION_FIX);
        s_nSupportAssetType = nSupportAssetType;
        ::scInitSpeedCC(NULL);
        SCSystem::adapterScreenResolution();
        SCMsgDisp()->sendMessage(SCID::Msg::kSCMsgAppLaunch);
    }
    
    void SCSystem::adapterScreenResolution(const bool bCache)
    {
        auto assetSizeType = SCSystem::getAssetSizeType(bCache);
        auto searchOrderVector = SCCCFileUtils()->getSearchResolutionsOrder();
        
        std::vector<std::string> newSearchVector;
        for(const auto& it : searchOrderVector)
        {
            if(it.compare(kSCFolderOfAssetLarge "/") &&
               it.compare(kSCFolderOfAssetMedium "/") &&
               it.compare(kSCFolderOfAssetSmall "/") &&
                it.compare(kSCFolderOfAssetXLarge "/"))
            {
                newSearchVector.push_back(it);
            }
        }
        
        switch(assetSizeType)
        {
            case kSizeXLarge:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetXLarge "/");
                break;
                
            case kSizeLarge:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetLarge "/");
                break;
                
            case kSizeMedium:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetMedium "/");
                break;
                
            case kSizeSmall:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetSmall "/");
                break;
                
            default: SCASSERT(false); break;
        }
        
        SCCCFileUtils()->setSearchResolutionsOrder(newSearchVector);
        
        auto screenSize = SCCCDirector()->getOpenGLView()->getFrameSize();
        float fContentScale = 1.0f;
        
        const bool bPortrait = ::scGetDeviceOrientation()<3;
        
        if(bPortrait)
        {
            switch(assetSizeType)
            {
                case kSizeXLarge:fContentScale = (kSCWidthOfAssetDesignXLarge/kSCWidthOfAssetDesignBaseline); break;
                case kSizeLarge: fContentScale = (kSCWidthOfAssetDesignLarge/kSCWidthOfAssetDesignBaseline);break;
                case kSizeMedium: fContentScale = (kSCWidthOfAssetDesignMedium/kSCWidthOfAssetDesignBaseline);break;
                case kSizeSmall: fContentScale = (kSCWidthOfAssetDesignSmall/kSCWidthOfAssetDesignBaseline);break;
                default: SCASSERT(false); break;
            }
            
            SCCCDirector()->getOpenGLView()->setDesignResolutionSize(kSCWidthOfAssetDesignBaseline,
                                                                     kSCHeightOfAssetDesignBaseline,
                                                                     ResolutionPolicy::FIXED_WIDTH);
        }
        else
        {
            switch(assetSizeType)
            {
                case kSizeXLarge: fContentScale = (kSCHeightOfAssetDesignXLarge/kSCHeightOfAssetDesignBaseline); break;
                case kSizeLarge: fContentScale = (kSCHeightOfAssetDesignLarge/kSCHeightOfAssetDesignBaseline); break;
                case kSizeMedium: fContentScale = (kSCHeightOfAssetDesignMedium/kSCHeightOfAssetDesignBaseline); break;
                case kSizeSmall: fContentScale = (kSCHeightOfAssetDesignSmall/kSCHeightOfAssetDesignBaseline); break;
                default: SCASSERT(false); break;
            }
            
            SCCCDirector()->getOpenGLView()->setDesignResolutionSize(kSCHeightOfAssetDesignBaseline,
                                                                     kSCWidthOfAssetDesignBaseline,
                                                                     ResolutionPolicy::FIXED_HEIGHT);
        }
        
        SCLog("Content Scale Factor: %.2f",fContentScale);
        SCCCDirector()->setContentScaleFactor(fContentScale);
    }
    
    void SCSystem::log(const char* pszFormat,...)
    {
        SC_RETURN_V_IF(pszFormat==NULL);
        SC_RETURN_V_IF(*pszFormat==0);
        
        char szMessage[1024+1] = {0};
        
        va_list argList;
        va_start(argList, pszFormat);
        vsprintf(szMessage, pszFormat, argList);
        va_end(argList);
        
        struct timeval  tv;
        ::gettimeofday(&tv, NULL);
        
        time_t now;
        time(&now);
        struct tm* p= localtime(&now);
        
        char szBuf[64] = {0};
        sprintf(szBuf, "[%02d:%02d:%02d.%03d] ",(int)p->tm_hour,(int)p->tm_min,(int)p->tm_sec,(int)tv.tv_usec/1000);
        
        static std::mutex* pLock = NULL;
        
        if(pLock==NULL)
        {
            pLock = new std::mutex();
        }
        
        SCASSERT(pLock!=NULL);
        SCAutoLock(*pLock);
        
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
        __android_log_print(ANDROID_LOG_DEBUG, "SpeedCC DEBUG", "%s SpeedCC: %s", szBuf,szMessage);
#else
        std::cout << szBuf << "SpeedCC: " <<szMessage<<std::endl;
#endif
    }
}


