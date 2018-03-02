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

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacroDef.h"
#include "../base/SCBaseMacros.h"
#include "../cocos/SCCocosDef.h"

namespace SpeedCC
{
#ifdef __cplusplus
    extern "C"
    {
#endif  // __cplusplus
        
        ///------------ store
        // nResult, 0: success; non-zero: failed
        void scbStorePurchaseItemResult(const char* pszIAP,int nResult)
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = (nResult==0) ? SCID::Msg::kMsgStorePurchaseSuccess : SCID::Msg::kMsgStorePurchaseFailed;
            ptrMsg->parameters.setValue(SC_KEY_IAP, SCString(pszIAP));
            SCMsgDisp()->postMessage(ptrMsg);
        }
        
        // nResult, 0: success; non-zero: failed
        void scbStoreRestoreItemResult(const char* pszIAP,int nResult)
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = ((nResult==0) ? SCID::Msg::kMsgStoreRestoreSuccess : SCID::Msg::kMsgStoreRestoreFailed);
            
            if(pszIAP!=NULL)
            {
                ptrMsg->parameters.setValue(SC_KEY_IAP, SCString(pszIAP));
            }
            SCMsgDisp()->postMessage(ptrMsg);
        }
        
        void scbStoreUserCancelled()
        {
            SCMsgDisp()->postMessage(SCID::Msg::kMsgStoreUserCancelled);
        }
        
        // nResult, 0: success; non-zero: failed
        void scbStoreRetrieveItemInfoResult(const char* pszIAP, const char* pszCurrency, float fPrice,int nResult)
        {
            if(nResult==0 && pszIAP!=NULL)
            {// all are fine
                SCMessage::Ptr ptrMsg = SCMessage::create();
                ptrMsg->nMsgID = SCID::Msg::kMsgStoreIAPInfoSuccess;
                ptrMsg->parameters.setValue(SC_KEY_IAP, SCString(pszIAP));
                ptrMsg->parameters.setValue(SC_KEY_CURRENCY, SCString(pszCurrency));
                ptrMsg->parameters.setValue(SC_KEY_PRICE, fPrice);
                
                SCMsgDisp()->postMessage(ptrMsg);
            }
            else if(nResult!=0 && pszIAP!=NULL)
            {// the IAP is invalid
                
            }
            else if(nResult!=0 && pszIAP==NULL)
            {// the retrieve all failed
                SCMsgDisp()->postMessage(SCID::Msg::kMsgStoreIAPInfoFailed);
            }
        }
        
        ///------------- system
        void scbAlertBoxSelected(const int nAlertBoxID,const int nButton)
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = SCID::Msg::kMsgAlertBoxSelected;
            ptrMsg->parameters.setValue(SC_KEY_ID, nAlertBoxID);
            ptrMsg->parameters.setValue(SC_KEY_RESULT, nButton);
            SCMsgDisp()->postMessage(ptrMsg);
        }
        
        ///------------- app
        /*
        void scbAppEnterBackground()
        {
            SCMsgDisp()->sendMessage(SCID::Msg::kMsgAppEnterBackground);
        }
        
        void scbAppEnterForeground()
        {
            SCMsgDisp()->sendMessage(SCID::Msg::kMsgAppEnterForeground);
        }

        
        void scbAppLaunched()
        {
            SCMsgDisp()->sendMessage(SCID::Msg::kMsgAppLaunch);
        }
        */
        ///------------- network
        void scbInternetReachableChanged(const bool bNewState)
        {
            
        }
        
#ifdef __cplusplus
    }
#endif  // __cplusplus
}


