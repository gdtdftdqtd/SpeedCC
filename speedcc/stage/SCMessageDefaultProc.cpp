//
//  SCMessageDefaultProc.cpp
//  libspeedcc
//
//  Created by Kevin on 26/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCMessageDefaultProc.h"

#include "../system/SCSetting.h"
#include "../system/SCStore.h"
#include "../system/SCSystem.h"

#include "../platform/SCOSSystem.h"

namespace SpeedCC
{
    void SCMessageDefaultProc::addAlertBoxCallback(const std::function<void(int)>& func,
                                                   const int nAlertBoxID)
    {
        SCASSERT(func!=NULL);
        SCASSERT(nAlertBoxID>0);
        _alertBoxID2CBMap[nAlertBoxID] = func;
    }
    
    void SCMessageDefaultProc::processMessage(SCMessage::Ptr ptrMsg)
    {
        SCASSERT(ptrMsg!=NULL);
        
        switch(ptrMsg->nMsgID)
        {
            case SCID::Msg::kSCMsgAppEnterBackground:
            {
                SCSetting::getInstance()->flush();
            }
                break;
                
                // store relative
            case SCID::Msg::kSCMsgStoreUserCancelled:
            {
                SCLog("IAP operation cancelled by user.");
                SCSystem::setGlobalDisableTouch(false);
            }
                break;
                
            case SCID::Msg::kSCMsgStorePurchaseSuccess:
            {
                SCLog("IAP Purchase success.");
                bool bResult = false;
                auto strIAP = ptrMsg->parameters.getValue(SC_KEY_IAP).getObject<SCString>(&bResult);
                SCASSERT(bResult);
                
                if(bResult)
                {
                    SCStore::getInstance()->setIAPPurchsed(strIAP);
                }
                
                SCSystem::setGlobalDisableTouch(false);
            }
                break;
                
            case SCID::Msg::kSCMsgStorePurchaseFailed:
            {
                SCLog("IAP Purchase failed.");
                SCSystem::setGlobalDisableTouch(false);
            }
                break;
                
            case SCID::Msg::kSCMsgStoreRestoreSuccess:
            {
                SCLog("Restored IAP success.");
                bool bResult = false;
                auto strIAP = ptrMsg->parameters.getValue(SC_KEY_IAP).getObject<SCString>(&bResult);
                SCASSERT(bResult);
                
                if(bResult)
                {
                    SCStore::getInstance()->setIAPPurchsed(strIAP);
                }
                
                SCSystem::setGlobalDisableTouch(false);
            }
                break;
                
            case SCID::Msg::kSCMsgStoreRestoreFailed:
            {
                SCLog("Restored IAP failed.");
                SCSystem::setGlobalDisableTouch(false);
            }
                break;
                
            case SCID::Msg::kSCMsgStoreIAPInfoSuccess:
            {
                SCLog("Request IAP info success.");
                bool bResult = false;
                auto strIAP = ptrMsg->parameters.getValue(SC_KEY_IAP).getObject<SCString>(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strCurrency = ptrMsg->parameters.getValue(SC_KEY_CURRENCY).getObject<SCString>(&bResult);
                SCASSERT(bResult);
                float fPrice = ptrMsg->parameters.getValue(SC_KEY_PRICE).getFloat();
                if(bResult)
                {
                    SCStore::getInstance()->setIAPInfo(strIAP, fPrice, strCurrency);
                }
            }
                break;
                
            case SCID::Msg::kSCMsgStoreIAPInfoFailed:
            {
                SCLog("Request IAP info failed.");
            }
                break;
                /*
            case SCID::Msg::kSCMsgShowAlertBox:
            {
                bool bResult = false;
                auto strTitle = ptrMsg->parameters.getValue(SC_KEY_TITLE).getString(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strMessage = ptrMsg->parameters.getValue(SC_KEY_TEXT).getString(&bResult);
                SCASSERT(bResult);
                auto nAlertBoxID = ptrMsg->parameters.getValue(SC_KEY_ID).getInt();
                bResult = false;
                auto strButton1 = ptrMsg->parameters.getValue(SC_KEY_STRING0).getString(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strButton2 = ptrMsg->parameters.getValue(SC_KEY_STRING1).getString(&bResult);
                SCString strButton3;
                if(bResult)
                {
                    bResult = false;
                    strButton3 = ptrMsg->parameters.getValue(SC_KEY_STRING2).getString(&bResult);
                }
                
                ::scShowSystemAlertBox(strTitle,
                                          strMessage,
                                          strButton1,
                                          strButton2,
                                          strButton3,
                                          nAlertBoxID);
            }
                break;
                */
            case SCID::Msg::kSCMsgAlertBoxSelected:
            {
                auto nAlertBoxID = ptrMsg->parameters.getValue(SC_KEY_ID).getInt();
                auto it = _alertBoxID2CBMap.find(nAlertBoxID);
                if(it!=_alertBoxID2CBMap.end())
                {
                    auto nSelected = ptrMsg->parameters.getValue(SC_KEY_RESULT).getInt();
                    (*it).second(nSelected);
                    _alertBoxID2CBMap.erase(it);
                }
            }
                break;
                
            case SCID::Msg::kSCMsgQuit:
                exit(0);
                break;
        }
    }
}
