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
                auto strIAP = ptrMsg->paramters.getValue(MSG_KEY_IAP).getObject<SCString>(&bResult);
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
                auto strIAP = ptrMsg->paramters.getValue(MSG_KEY_IAP).getObject<SCString>(&bResult);
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
                auto strIAP = ptrMsg->paramters.getValue(MSG_KEY_IAP).getObject<SCString>(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strCurrency = ptrMsg->paramters.getValue("currency").getObject<SCString>(&bResult);
                SCASSERT(bResult);
                float fPrice = ptrMsg->paramters.getValue("price").getFloat();
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
                
            case SCID::Msg::kSCMsgShowAlertBox:
            {
                bool bResult = false;
                auto strTitle = ptrMsg->paramters.getValue("title").getObject<SCString>(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strMessage = ptrMsg->paramters.getValue("message").getObject<SCString>(&bResult);
                SCASSERT(bResult);
                auto nAlertBoxID = ptrMsg->paramters.getValue("id").getInt();
                bResult = false;
                auto strButton1 = ptrMsg->paramters.getValue("button0").getObject<SCString>(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strButton2 = ptrMsg->paramters.getValue("button1").getObject<SCString>(&bResult);
                SCString strButton3;
                if(bResult)
                {
                    bResult = false;
                    strButton3 = ptrMsg->paramters.getValue("button2").getObject<SCString>(&bResult);
                }
                
                ::scShowSystemAlertBox(strTitle,
                                          strMessage,
                                          strButton1,
                                          strButton2,
                                          strButton3,
                                          nAlertBoxID);
            }
                break;
                
            case SCID::Msg::kSCMsgQuit:
                exit(0);
                break;
        }
    }
}
