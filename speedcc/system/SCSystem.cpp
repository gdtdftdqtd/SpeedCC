//
//  SCSystem.cpp
//  libspeedcc
//
//  Created by Kevin on 11/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SpeedCC.h"
#include "SCSystem.h"
#include "SCMacroDef.h"
#include "../SCConfig.h"
#include "../platform/SCOSSystem.h"

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
        
        di.nDistribution = nDistribution;
        
            // device type. 0: unkown; 1: phone; 2: tablet; 3: tv; 4:vehicle;
        switch(di.deviceType)
        {
            case 1: di.deviceType = kDevicePhone; break;
            case 2: di.deviceType = kDeviceTablet; break;
            case 3: di.deviceType = kDeviceTV; break;
            case 4: di.deviceType = kDeviceVehicle; break;
            default: di.deviceType = kDeviceUnknown; break;
        }
        
        di.bIsSimulator = (nIsSimulator!=0);
        
        return bRet;
    }
    
    cocos2d::Size SCSystem::getScreenSize()
    {
        cocos2d::Size size;
        ::scGetScreenSize(&size.width,&size.height);
        size.width *= CC_CONTENT_SCALE_FACTOR();
        size.height *= CC_CONTENT_SCALE_FACTOR();
        return size;
    }
    
    SCSystem::EScreenSizeType SCSystem::getScreenSizeType()
    {
        static EScreenSizeType      _screenSizeType = kScreenSizeUnkown;
        
        if(_screenSizeType==kScreenSizeUnkown)
        {
            const cocos2d::Size& screenSize = SCCCDirector()->getWinSize();
            
            const int squareOfScreen = screenSize.width * screenSize.height*CC_CONTENT_SCALE_FACTOR()*CC_CONTENT_SCALE_FACTOR();
            
            const int diffOfXLarge = abs(squareOfScreen - kSCWidthOfAssetDesignLarge*kSCHeightOfAssetDesignLarge);
            const int diffOfLarge = abs(squareOfScreen - kSCWidthOfAssetDesignLarge*kSCHeightOfAssetDesignLarge);
            const int diffOfMedium = abs(squareOfScreen - kSCWidthOfAssetDesignMedium*kSCHeightOfAssetDesignMedium);
            const int diffOfSmall = abs(squareOfScreen - kSCWidthOfAssetDesignSmall*kSCHeightOfAssetDesignSmall);
            
            int nMinimum = std::min(diffOfXLarge,std::min(diffOfLarge,std::min(diffOfMedium,diffOfSmall)));
            
            if(nMinimum==diffOfXLarge)
            {
                SCLog("detected screen size is 'XLarge'");
                _screenSizeType = kScreenSizeXLarge;
            }
            else if(nMinimum==diffOfLarge)
            {
                SCLog("detected screen size is 'Large'");
                _screenSizeType = kScreenSizeLarge;
            }
            else if(nMinimum==diffOfMedium)
            {
                SCLog("detected screen size is 'Medium'");
                _screenSizeType = kScreenSizeMedium;
            }
            else
            {
                SCASSERT(nMinimum==diffOfSmall);
                SCLog("detected screen size is 'Small'");
                _screenSizeType = kScreenSizeSmall;
            }
        }
        
        return _screenSizeType;
    }
    
    SCSystem::EScreenSizeType SCSystem::getAssetSizeType(const bool bCache)
    {
        static EScreenSizeType      _resourceSizeType = kScreenSizeUnkown;
        
        if(_resourceSizeType==kScreenSizeUnkown || !bCache)
        {
            const EScreenSizeType screenSize = SCSystem::getScreenSizeType();
            
            switch(screenSize)
            {
                case kScreenSizeXLarge:
                {
                    if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge))
                    {
                        SCLog("use 'XLarge' resolution images");
                        _resourceSizeType = kScreenSizeXLarge;
                    }
                    else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskLarge))
                    {
                        SCLog("use 'Large' resolution images");
                        _resourceSizeType = kScreenSizeLarge;
                    }
                    else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskMedium))
                    {
                        SCLog("use 'Medium' resolution images");
                        _resourceSizeType = kScreenSizeMedium;
                    }
                    else
                    {
                        SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskSmall));
                        SCLog("use 'Small' resolution images");
                        _resourceSizeType = kScreenSizeSmall;
                    }
                }
                    break;
                    
                case kScreenSizeLarge:
                {
                    if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskLarge))
                    {
                        SCLog("use 'Large' resolution images");
                        _resourceSizeType = kScreenSizeLarge;
                    }
                    else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskMedium))
                    {
                        SCLog("use 'Medium' resolution images");
                        _resourceSizeType = kScreenSizeMedium;
                    }
                    else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge))
                    {
                        SCLog("use 'XLarge' resolution images");
                        _resourceSizeType = kScreenSizeXLarge;
                    }
                    else
                    {
                        SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskSmall));
                        SCLog("use 'Small' resolution images");
                        _resourceSizeType = kScreenSizeSmall;
                    }
                }
                    break;
                    
                case kScreenSizeMedium:
                {
                    if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskMedium))
                    {
                        SCLog("use 'Medium' resolution images");
                        _resourceSizeType = kScreenSizeMedium;
                    }
                    else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskSmall))
                    {
                        SCLog("use 'Small' resolution images");
                        _resourceSizeType = kScreenSizeSmall;
                    }
                    else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskLarge))
                    {
                        SCLog("use 'Large' resolution images");
                        _resourceSizeType = kScreenSizeLarge;
                    }
                    else
                    {
                        SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge));
                        SCLog("use 'XLarge' resolution images");
                        _resourceSizeType = kScreenSizeXLarge;
                    }
                }
                    break;
                    
                case kScreenSizeSmall:
                {
                    if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskSmall))
                    {
                        SCLog("use 'Small' resolution images");
                        _resourceSizeType = kScreenSizeSmall;
                    }
                    else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskMedium))
                    {
                        SCLog("use 'Medium' resolution images");
                        _resourceSizeType = kScreenSizeMedium;
                    }
                    else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskLarge))
                    {
                        SCLog("use 'Large' resolution images");
                        _resourceSizeType = kScreenSizeLarge;
                    }
                    else if(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge))
                    {
                        SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kAssetBitMaskXLarge));
                        SCLog("use 'XLarge' resolution images");
                        _resourceSizeType = kScreenSizeXLarge;
                    }
                }
                    break;
                    
                default:
                    SCASSERT(false);
                    break;
            }
            
        }
        
        return _resourceSizeType;
    }
    
    void SCSystem::initSpeedCC(void* pController)
    {
        SCLog("SpeedCC v%d.%d.%d",(int)SPEEDCC_VERSION_MAJOR,(int)SPEEDCC_VERSION_MINOR,(int)SPEEDCC_VERSION_FIX);
        ::scInitSpeedCC(pController);
        SCSystem::adapterScreenResolution();
    }
    
    void SCSystem::adapterScreenResolution(const bool bCache)
    {
        const bool bPortrait = ::scGetDeviceOrientation()<3;
        
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
            case kScreenSizeXLarge:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetXLarge "/");
                break;
                
            case kScreenSizeLarge:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetLarge "/");
                break;
                
            case kScreenSizeMedium:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetMedium "/");
                break;
                
            case kScreenSizeSmall:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetSmall "/");
                break;
                
            default: SCASSERT(false); break;
        }
        
        SCCCFileUtils()->setSearchResolutionsOrder(newSearchVector);
        
        float fContentScale =  1.0f;
        
        switch(assetSizeType)
        {
            case kScreenSizeXLarge:
                fContentScale = (bPortrait ? kSCWidthOfAssetDesignXLarge/kSCWidthOfAssetDesignBaseline
                                 : kSCHeightOfAssetDesignXLarge/kSCHeightOfAssetDesignBaseline);
                break;
                
            case kScreenSizeLarge:
                fContentScale = (bPortrait ? kSCWidthOfAssetDesignLarge/kSCWidthOfAssetDesignBaseline
                                 : kSCHeightOfAssetDesignLarge/kSCHeightOfAssetDesignBaseline);
                break;
                
            case kScreenSizeMedium:
                fContentScale = (bPortrait ? kSCWidthOfAssetDesignMedium/kSCWidthOfAssetDesignBaseline
                                 : kSCHeightOfAssetDesignMedium/kSCHeightOfAssetDesignBaseline);
                break;
                
            case kScreenSizeSmall:
                fContentScale = (bPortrait ? kSCWidthOfAssetDesignSmall/kSCWidthOfAssetDesignBaseline
                                 : kSCHeightOfAssetDesignSmall/kSCHeightOfAssetDesignBaseline);
                break;
                
            default: SCASSERT(false); break;
        }
        
        ResolutionPolicy policy = bPortrait ? ResolutionPolicy::FIXED_WIDTH : ResolutionPolicy::FIXED_HEIGHT;
        SCCCDirector()->getOpenGLView()->setDesignResolutionSize(bPortrait?kSCWidthOfAssetDesignBaseline:kSCHeightOfAssetDesignBaseline,
                                                                  bPortrait?kSCHeightOfAssetDesignBaseline:kSCWidthOfAssetDesignBaseline,
                                                                  policy);
        
        SCCCDirector()->setContentScaleFactor(fContentScale);
    }
    
    void SCSystem::log(const char* pszFormat,...)
    {
        SC_RETURN_IF_V(pszFormat==NULL);
        SC_RETURN_IF_V(*pszFormat==0);
        
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
        __android_log_print(ANDROID_LOG_DEBUG, "SpeedCC DEBUG", "%s Foshan: %s", szBuf,szMessage);
#else
        std::cout << szBuf << "SpeedCC: " <<szMessage<<std::endl;
#endif
    }
}


