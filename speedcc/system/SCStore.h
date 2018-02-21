/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
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

namespace SpeedCC
{
    class SCStore final
    {
        friend class SCMessageDefaultProc;
    public:
        struct SIAPInfo
        {
            SCWatchFloat::Ptr   fPricePtr;
            SCString            strCurrency;
//            SCString            strTitle;
//            SCString            strDescription;
            
            SIAPInfo()
            {
                fPricePtr = SCWatchFloat::create();
            }
        };
        
    public:
        SC_AVOID_CLASS_COPY(SCStore)
        
        static SCStore* getInstance();
        
        // there are 3 combinations
        // 1) nFeatureID: yes; strIAP: yes; nPointID: yes;  Consumable IAP
        // 2) nFeatureID: yes; strIAP: yes; nPointID: no;   Non-Consumable IAP
        // 3) nFeatureID: yes; strIAP: no; nPointID: yes;   consume point
        bool setUpFeatureID(const int nFeatureID,const SCString& strIAP,const int nPointID=0,const int nPointInc=0);
        bool setPointIncByFeature(const int nFeatureID,const int nPointInc);
        bool purchaseFeature(const int nFeatureID);
        bool isFeatureEnable(const int nFeatureID) const;
        bool setFeatureEnable(const int nFeatureID,const bool bEnable);
        
        bool getIAPPriceInfo(const SCString& strIAP,SIAPInfo& info);
        SCString getIAPByFeature(const int nFeatureID);
        
        int getPointIDByFeature(const int nFeatureID);
        bool addPoint(const int nPointID,const int nPointInc);
        bool restorePurchased();
        bool requestIAPPriceInfo();
        
        bool bindPoint2Setting(const int nPointID,const SCString& strSettingKey);
        bool bindFeature2Setting(const int nFeatureID,const SCString& strSettingKey);
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
             1) (nFeatureID > 0) and (strIAP != "")
                 after feature be purchased
                    - if nPointID > 0; SCWatchInt of nPointID will increase by nPointInc
                    - if nPointID == 0; bFeatureLocked will be set to false
             
             2) (nFeatureID > 0) and (strIAP == "")
                after feature be purchased, SCWatchInt of nPointID will decrease by nPointInc
            */
            int             nFeatureID;
            int             nPointID;
            SCString        strIAP;
            int             nPointInc;
            SCWatchBool::Ptr bFeatureLockedPtr;
            
            SFeaturePointInfo():
            nFeatureID(0),
            nPointID(0),
            nPointInc(0)
            {
                bFeatureLockedPtr = SCWatchBool::create(true);
            }
        };
        
        SCStore();
        
        bool isFeatureExist(const int nFeatureID) const;
        bool isPointExist(const int nPointID) const;
        bool isIAPExist(const SCString& strIAP) const;
        EBuyType getBuyTypeByFeature(const int nFeatureID);
        EBuyType getBuyTypeByInfo(const SFeaturePointInfo& info);
        
        // called by message default processor
        void setIAPPurchsed(const SCString& strIAP);
        void setIAPInfo(const SCString& strIAP,const float fPrice,const SCString& strCurrency);
        
    private:
        std::map<int,SCWatchInt::Ptr>           _pointID2WatchIntMap;
        std::map<int,SFeaturePointInfo>         _feature2InfoMap;
        std::map<SCString,SIAPInfo>             _iap2PriceInfoMap;
        static SCStore*                         s_pInstance;
    };
}

#endif //__SPEEDCC__SCSTORE_H__
