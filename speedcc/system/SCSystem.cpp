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

#include "SCSystem.h"
#include "SCBaseMacros.h"

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacros.h"
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
        const bool bHas = (pScene->getChildByTag(SCLayerDisableTouch::kTAG)!=nullptr);
        
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
        return (pScene->getChildByTag(SCLayerDisableTouch::kTAG)!=nullptr);
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
    
    SCSystem::EResolutionType SCSystem::getScreenSizeType()
    {
        static EResolutionType      _screenSizeType = kResolutionUnkown;
        
        SC_RETURN_IF(_screenSizeType!=kResolutionUnkown,_screenSizeType);
        
        const cocos2d::Size& screenSize = SCScreenSize;
        
        const int nScreenSquare = screenSize.width * screenSize.height*CC_CONTENT_SCALE_FACTOR()*CC_CONTENT_SCALE_FACTOR();
        
        const int nDiffOfXLarge = abs(nScreenSquare - kSCWidthOfResolutionXLarge*kSCHeightOfResolutionXLarge);
        const int nDiffOfLarge = abs(nScreenSquare - kSCWidthOfResolutionLarge*kSCHeightOfResolutionLarge);
        const int nDiffOfMedium = abs(nScreenSquare - kSCWidthOfResolutionMedium*kSCHeightOfResolutionMedium);
        const int nDiffOfSmall = abs(nScreenSquare - kSCWidthOfResolutionSmall*kSCHeightOfResolutionSmall);
        
        int nMinimum = std::min(nDiffOfXLarge,std::min(nDiffOfLarge,std::min(nDiffOfMedium,nDiffOfSmall)));
        
        SCString strScreenSize(0,"%d x %d",(int)screenSize.width,(int)screenSize.height);
        if(nMinimum==nDiffOfXLarge)
        {
            SCLog("Detected Screen Resolution is 'XLarge'. %s",strScreenSize.c_str());
            _screenSizeType = kResolutionXLarge;
        }
        else if(nMinimum==nDiffOfLarge)
        {
            SCLog("Detected Screen Resolution is 'Large'. %s",strScreenSize.c_str());
            _screenSizeType = kResolutionLarge;
        }
        else if(nMinimum==nDiffOfMedium)
        {
            SCLog("Detected Screen Resolution is 'Medium'. %s",strScreenSize.c_str());
            _screenSizeType = kResolutionMedium;
        }
        else
        {
            SCASSERT(nMinimum==nDiffOfSmall);
            SCLog("Detected Screen Resolution is 'Small'. %s",strScreenSize.c_str());
            _screenSizeType = kResolutionSmall;
        }
        
        return _screenSizeType;
    }
    
    SCSystem::EResolutionType SCSystem::getAssetSizeType(const bool bCache)
    {
        static EResolutionType      _resourceSizeType = kResolutionUnkown;
        
        SC_RETURN_IF(_resourceSizeType!=kResolutionUnkown && bCache,_resourceSizeType);
        
        const EResolutionType screenSize = SCSystem::getScreenSizeType();
        
        switch(screenSize)
        {
            case kResolutionXLarge:
            {
                if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge))
                {
                    SCLog("Using 'XLarge' Resolution Assets");
                    _resourceSizeType = kResolutionXLarge;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskLarge))
                {
                    SCLog("Using 'Large' Resolution Assets");
                    _resourceSizeType = kResolutionLarge;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskMedium))
                {
                    SCLog("Using 'Medium' Resolution Assets");
                    _resourceSizeType = kResolutionMedium;
                }
                else
                {
                    SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskSmall));
                    SCLog("Using 'Small' Resolution Assets");
                    _resourceSizeType = kResolutionSmall;
                }
            }
                break;
                
            case kResolutionLarge:
            {
                if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskLarge))
                {
                    SCLog("Using 'Large' Resolution Assets");
                    _resourceSizeType = kResolutionLarge;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskMedium))
                {
                    SCLog("Using 'Medium' Resolution Assets");
                    _resourceSizeType = kResolutionMedium;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge))
                {
                    SCLog("Using 'XLarge' Resolution Assets");
                    _resourceSizeType = kResolutionXLarge;
                }
                else
                {
                    SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskSmall));
                    SCLog("Using 'Small' Resolution Assets");
                    _resourceSizeType = kResolutionSmall;
                }
            }
                break;
                
            case kResolutionMedium:
            {
                if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskMedium))
                {
                    SCLog("Using 'Medium' Resolution Assets");
                    _resourceSizeType = kResolutionMedium;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskSmall))
                {
                    SCLog("Using 'Small' Resolution Assets");
                    _resourceSizeType = kResolutionSmall;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskLarge))
                {
                    SCLog("Using 'Large' Resolution Assets");
                    _resourceSizeType = kResolutionLarge;
                }
                else
                {
                    SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge));
                    SCLog("Using 'XLarge' Resolution Assets");
                    _resourceSizeType = kResolutionXLarge;
                }
            }
                break;
                
            case kResolutionSmall:
            {
                if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskSmall))
                {
                    SCLog("Using 'Small' Resolution Assets");
                    _resourceSizeType = kResolutionSmall;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskMedium))
                {
                    SCLog("Using 'Medium' Resolution Assets");
                    _resourceSizeType = kResolutionMedium;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskLarge))
                {
                    SCLog("Using 'Large' Resolution Assets");
                    _resourceSizeType = kResolutionLarge;
                }
                else if(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge))
                {
                    SCASSERT(SC_BIT_HAS_OR(s_nSupportAssetType,kResolutionBitMaskXLarge));
                    SCLog("Using 'XLarge' Resolution Assets");
                    _resourceSizeType = kResolutionXLarge;
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
        ::scInitSpeedCC(nullptr);
        SCSystem::adapterScreenResolution();
        SCMsgDisp()->sendMessage(SCID::Msg::kMsgAppLaunch);
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
            case kResolutionXLarge:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetXLarge "/");
                break;
                
            case kResolutionLarge:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetLarge "/");
                break;
                
            case kResolutionMedium:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetMedium "/");
                break;
                
            case kResolutionSmall:
                newSearchVector.insert(newSearchVector.begin(), kSCFolderOfAssetSmall "/");
                break;
                
            default:
                SCASSERT(false);
                break;
        }
        
        SCCCFileUtils()->setSearchResolutionsOrder(newSearchVector);
        
        auto screenSize = SCCCDirector()->getOpenGLView()->getFrameSize();
        float fContentScale = 1.0f;
        
        const bool bPortrait = ::scGetDeviceOrientation()<3;
        
        if(bPortrait)
        {
            switch(assetSizeType)
            {
                case kResolutionXLarge:fContentScale = (kSCWidthOfResolutionXLarge/kSCWidthOfResolutionBaseline); break;
                case kResolutionLarge: fContentScale = (kSCWidthOfResolutionLarge/kSCWidthOfResolutionBaseline);break;
                case kResolutionMedium: fContentScale = (kSCWidthOfResolutionMedium/kSCWidthOfResolutionBaseline);break;
                case kResolutionSmall: fContentScale = (kSCWidthOfResolutionSmall/kSCWidthOfResolutionBaseline);break;
                default: SCASSERT(false); break;
            }
            
            SCCCDirector()->getOpenGLView()->setDesignResolutionSize(kSCWidthOfResolutionBaseline,
                                                                     kSCHeightOfResolutionBaseline,
                                                                     ResolutionPolicy::FIXED_WIDTH);
        }
        else
        {
            switch(assetSizeType)
            {
                case kResolutionXLarge:
                    fContentScale = (kSCHeightOfResolutionXLarge/kSCHeightOfResolutionBaseline);
                    break;
                case kResolutionLarge:
                    fContentScale = (kSCHeightOfResolutionLarge/kSCHeightOfResolutionBaseline);
                    break;
                case kResolutionMedium:
                    fContentScale = (kSCHeightOfResolutionMedium/kSCHeightOfResolutionBaseline);
                    break;
                case kResolutionSmall:
                    fContentScale = (kSCHeightOfResolutionSmall/kSCHeightOfResolutionBaseline);
                    break;
                default: SCASSERT(false); break;
            }
            
            SCCCDirector()->getOpenGLView()->setDesignResolutionSize(kSCHeightOfResolutionBaseline,
                                                                     kSCWidthOfResolutionBaseline,
                                                                     ResolutionPolicy::FIXED_HEIGHT);
        }
        
        SCLog("Content Scale Factor: %.2f",fContentScale);
        SCCCDirector()->setContentScaleFactor(fContentScale);
    }
    
    int SCSystem::showAlertBox(const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const std::function<void(int)>& resultFunc)
    {
        return SCSystem::showAlertBox(strTitle,strText,strButton1,"","",resultFunc);
    }
    
    int SCSystem::showAlertBox(const SCString& strTitle,
                            const SCString& strText,
                            const SCString& strButton1,
                            const SCString& strButton2,
                            const std::function<void(int)>& resultFunc)
    {
        return SCSystem::showAlertBox(strTitle,strText,strButton1,strButton2,"",resultFunc);
    }
    
    int SCSystem::showAlertBox(const SCString& strTitle,
                                const SCString& strText,
                                const SCString& strButton1,
                                const SCString& strButton2,
                                const SCString& strButton3,
                                const std::function<void(int)>& resultFunc)
    {
        int nAlertBoxID = (int)::time(nullptr);
        
        if(resultFunc!=nullptr)
        {
            SCMsgDisp()->getDefaultProc()->addAlertBoxCallback(resultFunc,nAlertBoxID);
        }

        ::scShowSystemAlertBox(strTitle,
                               strText,
                               strButton1,
                               strButton2,
                               strButton3,
                               nAlertBoxID);
        
        return nAlertBoxID;
    }
    
    int SCSystem::showAlertBox(SCBehaviorSceneGoto::Ptr ptrBvr,
                               const SCString& strTitle,
                               const SCString& strText,
                               const SCString& strButton1,
                               const SCString& strButton2,
                               const SCString& strButton3,
                               const std::function<void(int)>& resultFunc)
    {
        int nAlertBoxID = (int)::time(nullptr);
        
        SCDictionary::SPair pairArray[] =
        {
            {SC_KEY_TITLE,strTitle},
            {SC_KEY_TEXT,strText},
            {SC_KEY_ID,nAlertBoxID},
            {SC_KEY_STRING0,strButton1},
            {SC_KEY_STRING1,strButton2},
            {SC_KEY_STRING2,strButton3}
        };
        
        SCDictionary dic(pairArray,SC_ARRAY_LENGTH(pairArray));
        
        if(resultFunc!=nullptr)
        {
            SCSceneController::FinishFunc_t call = [resultFunc](void* pUserData)
            {
                int nIndex = SC_PVOID_2_NUM(pUserData);
                resultFunc(nIndex);
            };
            
            dic.setValue(SC_KEY_FINISHFUNC, call);
        }
        ptrBvr->setSceneParameter(dic);
        ptrBvr->execute();
        
        return nAlertBoxID;
    }
    
    void SCSystem::log(const char* pszFormat,...)
    {
        SC_RETURN_V_IF(pszFormat==nullptr);
        SC_RETURN_V_IF(*pszFormat==0);
        
        char szMessage[1024+1] = {0};
        
        va_list argList;
        va_start(argList, pszFormat);
        vsprintf(szMessage, pszFormat, argList);
        va_end(argList);
        
        struct timeval  tv;
        ::gettimeofday(&tv, nullptr);
        
        time_t now;
        time(&now);
        struct tm* p= localtime(&now);
        
        char szBuf[64] = {0};
        sprintf(szBuf, "[%02d:%02d:%02d.%03d] ",(int)p->tm_hour,(int)p->tm_min,(int)p->tm_sec,(int)tv.tv_usec/1000);
        
        static std::mutex* pLock = nullptr;
        
        if(pLock==nullptr)
        {
            pLock = new std::mutex();
        }
        
        SCASSERT(pLock!=nullptr);
        SCAutoLock(*pLock);
        
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
        __android_log_print(ANDROID_LOG_DEBUG, "SpeedCC DEBUG", "%s SpeedCC: %s", szBuf,szMessage);
#else
        std::cout << szBuf << "SpeedCC: " <<szMessage<<std::endl;
#endif
    }
}


