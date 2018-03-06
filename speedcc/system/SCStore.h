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

#ifndef __SPEEDCC__SCSTORE_H__
#define __SPEEDCC__SCSTORE_H__

#include "../base/SCString.h"
#include "../base/SCObject.h"
#include "../base/SCWatchNumberT.h"
#include "../stage/SCMessageDispatch.h"

namespace SpeedCC
{
    class SCStore : public SCMessageListener
    {
        friend class SCMessageDefaultProc;
        
    public:
        struct SIAPInfo
        {
            SCWatchFloat::Ptr   ptrPrice;
            SCString            strCurrency;
//            SCString            strTitle;
//            SCString            strDescription;
            
            SIAPInfo()
            {
                ptrPrice = SCWatchFloat::create();
            }
        };
        
        enum class EResultType
        {
            kSuccess,
            kFailed,
            kUserCancelled,
        };
        
        typedef std::function<void(SCString strProductID,EResultType result,void* pInfo)>   ResultFunc_t;
        
    public:
        SC_AVOID_CLASS_COPY(SCStore)
        
        static SCStore* getInstance();
        
        virtual ~SCStore();
        
        // there are 3 combinations
        // 1) nFeatureID: yes; strProductID: yes; nPointID: yes;  Consumable IAP
        // 2) nFeatureID: yes; strProductID: yes; nPointID: no;   Non-Consumable IAP
        // 3) nFeatureID: yes; strProductID: no; nPointID: yes;   consume point
        bool setUpFeature(const int nFeatureID,const SCString& strProductID,const int nPointID=0,const int nPointInc=0);
        bool setPointIncByFeature(const int nFeatureID,const int nPointInc);
        bool purchaseFeature(const int nFeatureID,const ResultFunc_t& resultFunc = nullptr);
        bool isFeatureEnabled(const int nFeatureID) const;
        bool setFeatureEnabled(const int nFeatureID,const bool bEnable);
        
        bool getPriceInfoByProduct(const SCString& strProductID,SIAPInfo& info);
        bool getPriceInfoByFeature(const int nFeatureID,SIAPInfo& info);
        SCString getProductIDByFeature(const int nFeatureID);
        
        int getPointIDByFeature(const int nFeatureID);
        SCWatchInt::Ptr getPointByID(const int nPointID) const;
        bool restorePurchased(const ResultFunc_t& resultFunc = nullptr);
        bool requestIAPPriceInfo(const ResultFunc_t& resultFunc = nullptr);
        
    private:
        enum EBuyType
        {
            kBUY_UNKNOWN,
            kBUY_CONSUMABLE,
            kBUY_NONCONSUMABLE,
            kBUY_CONSUME_POINT
        };
        
        struct SFeaturePointInfo
        {
            /*
             1) (nFeatureID > 0) and (strProductID != "")
                 after feature be purchased
                    - if nPointID > 0; SCWatchInt of nPointID will increase by nPointInc
                    - if nPointID == 0; bFeatureLocked will be set to false
             
             2) (nFeatureID > 0) and (strProductID == "")
                after feature be purchased, SCWatchInt of nPointID will decrease by nPointInc
            */
            int             nFeatureID;
            int             nPointID;
            SCString        strProductID;
            int             nPointInc;
            SCWatchBool::Ptr ptrFeatureLocked;
            
            SFeaturePointInfo():
            nFeatureID(0),
            nPointID(0),
            nPointInc(0)
            {
                ptrFeatureLocked = SCWatchBool::create(true);
            }
        };
        
        SCStore();
        
        bool bindPoint2Setting(const int nPointID,const SCString& strSettingKey,const bool bUseSetting);
        bool unbindPoint2Setting(const int nPointID);
        bool bindFeature2Setting(const int nFeatureID,const SCString& strSettingKey,const bool bUseSetting);
        bool unbindFeature(const int nFeatureID);
        
        bool isFeatureExist(const int nFeatureID) const;
        bool isPointExist(const int nPointID) const;
        bool isProductExit(const SCString& strProductID) const;
        EBuyType getBuyTypeByFeature(const int nFeatureID);
        EBuyType getBuyTypeByInfo(const SFeaturePointInfo& info);
        
        // called by message default processor
        void setIAPPurchsed(const SCString& strProductID);
        void setIAPInfo(const SCString& strProductID,const float fPrice,const SCString& strCurrency);
        
        virtual void onSCMessageProcess(SCMessage::Ptr ptrMsg) override;
        
    private:
        std::map<int,SCWatchInt::Ptr>           _pointID2WatchIntMap;
        std::map<int,SFeaturePointInfo>         _feature2InfoMap;
        std::map<SCString,SIAPInfo>             _iap2PriceInfoMap;
        SCString                                _strCurrentProductID;
        ResultFunc_t                            _purchaseResultFunc;
        ResultFunc_t                            _restoreResultFunc;
        ResultFunc_t                            _requestIAPInfoResultFunc;
        static SCStore*                         s_pInstance;
    };
}

#endif //__SPEEDCC__SCSTORE_H__
