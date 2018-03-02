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

#include "SCStore.h"
#include "SCSetting.h"
#include "../platform/SCOSSystem.h"

namespace SpeedCC
{
    SCStore*      SCStore::s_pInstance = nullptr;
    
    SCStore::SCStore()
    {
    }
    
    SCStore* SCStore::getInstance()
    {
        if(s_pInstance==nullptr)
        {
            s_pInstance = new SCStore();
        }
        
        return s_pInstance;
    }
    
    bool SCStore::setUpFeature(const int nFeatureID,const SCString& strIAP,const int nPointID,const int nPointInc)
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
        ::scStorePurchaseItem((*it).second.strIAP,type==kBUY_CONSUMABLE);
        return true;
    }
    
    bool SCStore::isFeatureEnabled(const int nFeatureID) const
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,false);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
        auto ptr = (*it).second.ptrFeatureLocked;
        return !(*ptr);
    }
    
    bool SCStore::setFeatureEnabled(const int nFeatureID,const bool bEnable)
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,false);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
        *((*it).second.ptrFeatureLocked) = !bEnable;
        return true;
    }
    
    bool SCStore::getIAPPriceInfo(const SCString& strIAP,SIAPInfo& info)
    {
        SCASSERT(!strIAP.isEmpty());
        SC_RETURN_IF(strIAP.isEmpty(), false);
        SC_RETURN_IF(!this->isIAPExist(strIAP), false);
        
        bool bRet = false;
        const auto& it = _iap2PriceInfoMap.find(strIAP);
        if(it==_iap2PriceInfoMap.end())
        {
//            if(bRquest)
//            {
//                this->requestPriceInfo(strIAP);
//            }
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
        return ::scStoreRestorePurchased();
    }
    
    bool SCStore::requestIAPPriceInfo()
    {
        bool bRet = false;
        int nCount = 0;
        char** pIAPArray = new char*[_feature2InfoMap.size()];
        ::memset(pIAPArray,0,_feature2InfoMap.size());
        
        for(const auto& it : _feature2InfoMap)
        {
            if(!it.second.strIAP.isEmpty())
            {
                char* pszIAP = (char*)::malloc(it.second.strIAP.getLength()+2);
                ::strcpy(pszIAP,it.second.strIAP);
                pIAPArray[nCount] = pszIAP;
                ++nCount;
            }
        }
        if(nCount>0)
        {
            bRet = ::scStoreRequestItemInfo(pIAPArray,nCount);
            for(int i=0; i<nCount; ++i)
            {
                ::free(pIAPArray[i]);
                pIAPArray[i] = nullptr;
            }
        }
        
        delete [] pIAPArray;
        pIAPArray = nullptr;
        
        return bRet;
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
    
    SCWatchInt::Ptr SCStore::getPointByID(const int nPointID) const
    {
        auto ret = SCWatchInt::create();
        auto it = _pointID2WatchIntMap.find(nPointID);
        
        if(it!=_pointID2WatchIntMap.end())
        {
            ret = (*it).second;
        }
        
        return ret;
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
    
    bool SCStore::bindPoint2Setting(const int nPointID,const SCString& strSettingKey,const bool bUseSetting)
    {
        SCASSERT(nPointID>0);
        SC_RETURN_IF(nPointID<=0, false);
        SC_RETURN_IF(strSettingKey.isEmpty(), false);
        
        auto it = _pointID2WatchIntMap.find(nPointID);
        SC_RETURN_IF(_pointID2WatchIntMap.end()==it, false);
        
        auto ptr = SCSetting::getInstance()->getWatchInt(strSettingKey);
        if(!bUseSetting)
        {
            *ptr = *(*it).second;
        }
        (*it).second = ptr;
        
        return true;
    }
    
    bool SCStore::unbindPoint2Setting(const int nPointID)
    {
        SCASSERT(nPointID>0);
        SC_RETURN_IF(nPointID<=0, false);
        
        auto it = _pointID2WatchIntMap.find(nPointID);
        SC_RETURN_IF(_pointID2WatchIntMap.end()==it, false);
        
        int n = (*(*it).second);
        (*it).second = SCWatchInt::create(n);
        return true;
    }
    
    bool SCStore::bindFeature2Setting(const int nFeatureID,const SCString& strSettingKey,const bool bUseSetting)
    {
        SC_RETURN_IF(nFeatureID<=0 || strSettingKey.isEmpty(), false);
        
        auto it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
        auto ptr = SCSetting::getInstance()->getWatchBool(strSettingKey);
        if(bUseSetting)
        {
            *ptr = *(*it).second.ptrFeatureLocked;
        }
        (*it).second.ptrFeatureLocked = ptr;
        
        return true;
    }
    
    bool SCStore::unbindFeature(const int nFeatureID)
    {
        SC_RETURN_IF(nFeatureID<=0, false);
        
        auto it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
        bool b = *((*it).second.ptrFeatureLocked);
        
        (*it).second.ptrFeatureLocked = SCWatchBool::create(b);
        
        return true;
    }
    
    void SCStore::setIAPPurchsed(const SCString& strIAP)
    {
        SC_RETURN_V_IF(strIAP.isEmpty());
        
        for(auto& it : _feature2InfoMap)
        {
            if(it.second.strIAP==strIAP)
            {
                *(it.second.ptrFeatureLocked) = true;
                break;
            }
        }
    }
    
    void SCStore::setIAPInfo(const SCString& strIAP,const float fPrice,const SCString& strCurrency)
    {
        SC_RETURN_V_IF(strIAP.isEmpty());
        
        if(this->isIAPExist(strIAP))
        {
            SIAPInfo info;
            *(info.fPricePtr) = fPrice;
            info.strCurrency = strCurrency;
            _iap2PriceInfoMap[strIAP] = info;
        }
    }
}
