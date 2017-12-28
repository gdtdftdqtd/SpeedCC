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
    void SCMessageDefaultProc::processMessage(SCMessageInfo& mi)
    {
        switch(mi.nMsgID)
        {
            case kSCMsgAppEnterBackground:
            {
                SCSetting::getInstance()->flush();
            }
                break;
                
                // store relative
            case kSCMsgStoreUserCancelled:
            {
                SCLog("IAP operation cancelled by user.");
                SCSystem::setGlobalNoTouch(false);
            }
                break;
                
            case kSCMsgStorePurchaseSuccess:
            {
                SCLog("IAP Purchase success.");
                bool bResult = false;
                auto strIAP = mi.paramters.getValue(MSG_KEY_IAP).getObject<SCString>(&bResult);
                SCASSERT(bResult);
                
                if(bResult)
                {
                    SCStore::getInstance()->setIAPPurchsed(strIAP);
                }
                
                SCSystem::setGlobalNoTouch(false);
            }
                break;
                
            case kSCMsgStorePurchaseFailed:
            {
                SCLog("IAP Purchase failed.");
                SCSystem::setGlobalNoTouch(false);
            }
                break;
                
            case kSCMsgStoreRestoreSuccess:
            {
                SCLog("Restored IAP success.");
                bool bResult = false;
                auto strIAP = mi.paramters.getValue(MSG_KEY_IAP).getObject<SCString>(&bResult);
                SCASSERT(bResult);
                
                if(bResult)
                {
                    SCStore::getInstance()->setIAPPurchsed(strIAP);
                }
                
                SCSystem::setGlobalNoTouch(false);
            }
                break;
                
            case kSCMsgStoreRestoreFailed:
            {
                SCLog("Restored IAP failed.");
                SCSystem::setGlobalNoTouch(false);
            }
                break;
                
            case kSCMsgStoreIAPInfoSuccess:
            {
                SCLog("Request IAP info success.");
                bool bResult = false;
                auto strIAP = mi.paramters.getValue(MSG_KEY_IAP).getObject<SCString>(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strCurrency = mi.paramters.getValue("currency").getObject<SCString>(&bResult);
                SCASSERT(bResult);
                float fPrice = mi.paramters.getValue("price").getFloat();
                if(bResult)
                {
                    SCStore::getInstance()->setIAPInfo(strIAP, fPrice, strCurrency);
                }
            }
                break;
                
            case kSCMsgStoreIAPInfoFailed:
            {
                SCLog("Request IAP info failed.");
            }
                break;
                
            case kSCMsgShowAlertBox:
            {
                bool bResult = false;
                auto strTitle = mi.paramters.getValue("title").getObject<SCString>(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strMessage = mi.paramters.getValue("message").getObject<SCString>(&bResult);
                SCASSERT(bResult);
                auto nAlertBoxID = mi.paramters.getValue("id").getInt();
                bResult = false;
                auto strButton1 = mi.paramters.getValue("button0").getObject<SCString>(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strButton2 = mi.paramters.getValue("button1").getObject<SCString>(&bResult);
                SCString strButton3;
                if(bResult)
                {
                    bResult = false;
                    strButton3 = mi.paramters.getValue("button2").getObject<SCString>(&bResult);
                }
                
                ::scShowSystemAlertBox(strTitle,
                                          strMessage,
                                          strButton1,
                                          strButton2,
                                          strButton3,
                                          nAlertBoxID);
            }
                break;
                
        }
    }
}
