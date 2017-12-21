//
//  SCStore.cpp
//  libspeedcc
//
//  Created by Kevin on 21/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "SCStore.h"
#include "../platform/SCOSSystem.h"

namespace SpeedCC
{
    SCStore*      SCStore::s_pInstance = NULL;
    
    SCStore::SCStore()
    {
    }
    
    SCStore* SCStore::getInstance()
    {
        if(s_pInstance==NULL)
        {
            s_pInstance = new SCStore();
        }
        
        return s_pInstance;
    }
    
    bool SCStore::setUpFeatureID(const int nFeatureID,const SCString& strIAP,const int nPointID,const int nPointInc)
    {
        SCASSERT(nFeatureID>0);
        SFeaturePointInfo info;
        info.nFeatureID = nFeatureID;
        info.strIAP = strIAP;
        info.nPointID = nPointID;
        info.nPointInc = nPointInc;
        
        const auto type = this->getBuyTypeByInfo(info);
        
        SC_RETURN_IF(type==kBUY_UNKNOWN,false);
        SC_RETURN_IF(this->isFeatureExist(nFeatureID),false);
        SC_RETURN_IF(!strIAP.isEmpty() && this->isIAPExist(strIAP),false);
        SC_RETURN_IF(nPointID>0 && this->isPointExist(nPointID),false);
        
        SCMapInsert(_feature2InfoMap, nFeatureID, info);
        
        if(nPointID>0)
        {
            SCWatchInt::Ptr ptr = SCWatchInt::create();
            SCMapInsert(_pointID2WatchIntMap,nPointID,ptr);
        }
        
        return true;
    }
    
    bool SCStore::setPointIncByFeature(const int nFeatureID,const int nPointInc)
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,false);
        auto it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
        (*it).second.nPointInc = nPointInc;
        return true;
    }
    
    bool SCStore::purchaseFeature(const int nFeatureID)
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,false);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
        auto type = this->getBuyTypeByInfo((*it).second);
        SC_RETURN_IF(type!=kBUY_CONSUMABLE && type!=kBUY_NONCONSUMABLE, false);
        ::scPurchaseItem((*it).second.strIAP,type==kBUY_CONSUMABLE);
        return true;
    }
    
    bool SCStore::isFeatureEnable(const int nFeatureID) const
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,false);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
        return !(*it).second.bFeatureLocked;
    }
    
    bool SCStore::setFeatureEnable(const int nFeatureID,const bool bEnable)
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,false);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
        (*it).second.bFeatureLocked = !bEnable;
        return true;
    }
    
    bool SCStore::getIAPPriceInfo(const SCString& strIAP,SPriceInfo& info,const bool bRquest)
    {
        SCASSERT(!strIAP.isEmpty());
        SC_RETURN_IF(strIAP.isEmpty(), false);
        SC_RETURN_IF(!this->isIAPExist(strIAP), false);
        
        bool bRet = false;
        const auto& it = _iap2PriceInfoMap.find(strIAP);
        if(it==_iap2PriceInfoMap.end())
        {
            if(bRquest)
            {
                this->requestPriceInfo(strIAP);
            }
        }
        else
        {
            info = (*it).second;
            bRet = true;
        }
        
        return bRet;
    }
    
    bool SCStore::restorePurchased()
    {
        return ::scRestorePurchased();
    }
    
    bool SCStore::requestPriceInfo(const SCString& strIAP)
    {
        SCASSERT(!strIAP.isEmpty());
        SC_RETURN_IF(strIAP.isEmpty(), false);
        SC_RETURN_IF(!this->isIAPExist(strIAP), false);
        
        ::scRequestPurchasedItemInfo(strIAP);
        return false;
    }
    
    bool SCStore::bindPoint2Setting(const int nPointID,const SCString& strSettingKey)
    {
        SCASSERT(nPointID>0);
        SC_RETURN_IF(nPointID<=0, false);
        SC_RETURN_IF(strSettingKey.isEmpty(), false);
        
        auto it = _pointID2WatchIntMap.find(nPointID);
        
        SC_RETURN_IF(_pointID2WatchIntMap.end()==it, false);
        
        return false;
    }
    
    SCString SCStore::getIAPByFeature(const int nFeatureID)
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,0);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(_feature2InfoMap.end()==it, 0);
        return (*it).second.strIAP;
    }
    
    int SCStore::getPointIDByFeature(const int nFeatureID)
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,0);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(_feature2InfoMap.end()==it, 0);
        return (*it).second.nPointID;
    }
    
    bool SCStore::addPoint(const int nPointID,const int nPointInc)
    {
        SCASSERT(nPointID>0);
        auto it = _pointID2WatchIntMap.find(nPointID);
        SC_RETURN_IF(it==_pointID2WatchIntMap.end(), false);
        (*(*it).second) += nPointInc;
        return true;
    }
    
    
    bool SCStore::isFeatureExist(const int nFeatureID) const
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(_feature2InfoMap.empty() || nFeatureID<=0, false);
     
        return (_feature2InfoMap.find(nFeatureID)!=_feature2InfoMap.end());
    }
    
    bool SCStore::isPointExist(const int nPointID) const
    {
        SCASSERT(nPointID>0);
        SC_RETURN_IF(_pointID2WatchIntMap.empty() || nPointID<=0, false);
        
        return (_pointID2WatchIntMap.find(nPointID)!=_pointID2WatchIntMap.end());
    }
    
    bool SCStore::isIAPExist(const SCString& strIAP) const
    {
        SCASSERT(!strIAP.isEmpty());
        SC_RETURN_IF(_feature2InfoMap.empty() || strIAP.isEmpty(), false);
        
        for(const auto& it : _feature2InfoMap)
        {
            SC_RETURN_IF(it.second.strIAP==strIAP,true);
        }
        
        return false;
    }
    
    SCStore::EBuyType SCStore::getBuyTypeByFeature(const int nFeatureID)
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(_feature2InfoMap.empty() || nFeatureID<=0, kBUY_UNKNOWN);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(),kBUY_UNKNOWN);
        
        return this->getBuyTypeByInfo((*it).second);
    }
    
    SCStore::EBuyType SCStore::getBuyTypeByInfo(const SFeaturePointInfo& info)
    {
        SC_RETURN_IF(info.nFeatureID<=0, kBUY_UNKNOWN);
        
        if(info.strIAP.isEmpty())
        {
            return (info.nPointID>0) ? kBUY_CONSUME_POINT : kBUY_UNKNOWN;
        }
        else
        {
            return (info.nPointID>0) ? kBUY_CONSUMABLE : kBUY_NONCONSUMABLE;
        }
    }
}
