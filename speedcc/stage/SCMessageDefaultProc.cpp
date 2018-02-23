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
        SCASSERT(func!=nullptr);
        SCASSERT(nAlertBoxID>0);
        _alertBoxID2CBMap[nAlertBoxID] = func;
    }
    
    void SCMessageDefaultProc::processMessage(SCMessage::Ptr ptrMsg)
    {
        SCASSERT(ptrMsg!=nullptr);
        
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
                auto strIAP = ptrMsg->parameters.getValue(SC_KEY_IAP).getString(&bResult);
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
                auto strIAP = ptrMsg->parameters.getValue(SC_KEY_IAP).getString(&bResult);
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
                auto strIAP = ptrMsg->parameters.getValue(SC_KEY_IAP).getString(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strCurrency = ptrMsg->parameters.getValue(SC_KEY_CURRENCY).getString(&bResult);
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
