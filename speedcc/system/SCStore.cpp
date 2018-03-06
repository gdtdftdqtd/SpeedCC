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
#include "../system/SCSystem.h"

namespace SpeedCC
{
    SCStore*      SCStore::s_pInstance = nullptr;
    
    SCStore::SCStore()
    {
        SCMsgDisp()->addListener(this);
    }
    
    SCStore::~SCStore()
    {
        SCMsgDisp()->removeListener(this);
    }
    
    SCStore* SCStore::getInstance()
    {
        if(s_pInstance==nullptr)
        {
            s_pInstance = new SCStore();
        }
        
        return s_pInstance;
    }
    
    bool SCStore::setUpFeature(const int nFeatureID,const SCString& strProductID,const int nPointID,const int nPointInc)
    {
        SCASSERT(nFeatureID>0);
        SFeaturePointInfo info;
        info.nFeatureID = nFeatureID;
        info.strProductID = strProductID;
        info.nPointID = nPointID;
        info.nPointInc = nPointInc;
        
        const auto type = this->getBuyTypeByInfo(info);
        
        SC_RETURN_IF(type==kBUY_UNKNOWN,false);
        SC_RETURN_IF(this->isFeatureExist(nFeatureID),false);
        SC_RETURN_IF(!strProductID.isEmpty() && this->isProductExit(strProductID),false);
        SC_RETURN_IF(nPointID>0 && this->isPointExist(nPointID),false);
        
        SCMapInsert(_feature2InfoMap, nFeatureID, info);
        
        if(nPointID>0)
        {
            SCWatchInt::Ptr ptr = SCWatchInt::create();
            SCMapInsert(_pointID2WatchIntMap,nPointID,ptr);
        }
        
        if(!strProductID.isEmpty() && nPointID>0)
        {// consumable
            this->bindFeature2Setting(nFeatureID,SCString(0,kSCSettingKeyStoreFeaturePrefix "_%d__",nFeatureID),true);
            this->bindFeature2Setting(nFeatureID,SCString(0,kSCSettingKeyStorePointPrefix "_%d__",nPointID),true);
        }
        else if(!strProductID.isEmpty() && nPointID==0)
        {// non-consumable
            this->bindFeature2Setting(nFeatureID,SCString(0,kSCSettingKeyStoreFeaturePrefix "_%d__",nFeatureID),true);
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
    
    bool SCStore::purchaseFeature(const int nFeatureID,const ResultFunc_t& resultFunc)
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,false);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(it==_feature2InfoMap.end(), false);
        
        auto type = this->getBuyTypeByInfo((*it).second);
        SC_RETURN_IF(type!=kBUY_CONSUMABLE && type!=kBUY_NONCONSUMABLE, false);
        _purchaseResultFunc = resultFunc;
        _strCurrentProductID = (*it).second.strProductID;
        ::scStorePurchaseItem((*it).second.strProductID,type==kBUY_CONSUMABLE);
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
    
    bool SCStore::getPriceInfoByProduct(const SCString& strProductID,SIAPInfo& info)
    {
        SCASSERT(!strProductID.isEmpty());
        SC_RETURN_IF(strProductID.isEmpty(), false);
        SC_RETURN_IF(!this->isProductExit(strProductID), false);
        
        bool bRet = false;
        const auto& it = _iap2PriceInfoMap.find(strProductID);
        if(it==_iap2PriceInfoMap.end())
        {
//            if(bRquest)
//            {
//                this->requestPriceInfo(strProductID);
//            }
        }
        else
        {
            info = (*it).second;
            bRet = true;
        }
        
        return bRet;
    }
    
    bool SCStore::getPriceInfoByFeature(const int nFeatureID,SIAPInfo& info)
    {
        SC_RETURN_IF(nFeatureID<=0, false);
        auto strProductID = this->getProductIDByFeature(nFeatureID);
        SC_RETURN_IF(strProductID.isEmpty(), false);
        return this->getPriceInfoByProduct(strProductID,info);
    }
    
    bool SCStore::restorePurchased(const ResultFunc_t& resultFunc)
    {
        _restoreResultFunc = resultFunc;
        return ::scStoreRestorePurchased();
    }
    
    bool SCStore::requestIAPPriceInfo(const ResultFunc_t& resultFunc)
    {
        bool bRet = false;
        int nCount = 0;
        char** pIAPArray = new char*[_feature2InfoMap.size()];
        ::memset(pIAPArray,0,_feature2InfoMap.size());
        
        for(const auto& it : _feature2InfoMap)
        {
            if(!it.second.strProductID.isEmpty())
            {
                char* pszIAP = (char*)::malloc(it.second.strProductID.getLength()+2);
                ::strcpy(pszIAP,it.second.strProductID);
                pIAPArray[nCount] = pszIAP;
                ++nCount;
            }
        }
        if(nCount>0)
        {
            _requestIAPInfoResultFunc = resultFunc;
            bRet = ::scStoreRequestItemInfo(pIAPArray,nCount);
            for(int i=0; i<nCount; ++i)
            {
                ::free(pIAPArray[i]);
                pIAPArray[i] = nullptr;
            }
        }
        else
        {
            resultFunc("",EResultType::kFailed,nullptr);
        }
        
        delete [] pIAPArray;
        pIAPArray = nullptr;
        
        return bRet;
    }
    
    SCString SCStore::getProductIDByFeature(const int nFeatureID)
    {
        SCASSERT(nFeatureID>0);
        SC_RETURN_IF(nFeatureID<=0,0);
        const auto& it = _feature2InfoMap.find(nFeatureID);
        SC_RETURN_IF(_feature2InfoMap.end()==it, 0);
        return (*it).second.strProductID;
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
    
    bool SCStore::isProductExit(const SCString& strProductID) const
    {
        SCASSERT(!strProductID.isEmpty());
        SC_RETURN_IF(_feature2InfoMap.empty() || strProductID.isEmpty(), false);
        
        for(const auto& it : _feature2InfoMap)
        {
            SC_RETURN_IF(it.second.strProductID==strProductID,true);
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
        
        if(info.strProductID.isEmpty())
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
        
        auto ptr = SCSetting::getInstance()->getWatchInt(strSettingKey,0);
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
        
        auto ptr = SCSetting::getInstance()->getWatchBool(strSettingKey,false);
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
    
    void SCStore::setIAPPurchsed(const SCString& strProductID)
    {
        SC_RETURN_V_IF(strProductID.isEmpty());
        
        for(auto& it : _feature2InfoMap)
        {
            if(it.second.strProductID==strProductID)
            {
                *(it.second.ptrFeatureLocked) = true;
                break;
            }
        }
    }
    
    void SCStore::setIAPInfo(const SCString& strProductID,const float fPrice,const SCString& strCurrency)
    {
        SC_RETURN_V_IF(strProductID.isEmpty());
        
        if(this->isProductExit(strProductID))
        {
            SIAPInfo info;
            *(info.ptrPrice) = fPrice;
            info.strCurrency = strCurrency;
            _iap2PriceInfoMap[strProductID] = info;
        }
    }
    
    void SCStore::onSCMessageProcess(SCMessage::Ptr ptrMsg)
    {
        switch(ptrMsg->nMsgID)
        {
            // store relative
        case SCID::Msg::kMsgStoreUserCancelled:
            {
                SCLog("IAP operation cancelled by user.");
                if(_purchaseResultFunc!=nullptr)
                {
                    _purchaseResultFunc(_strCurrentProductID,EResultType::kUserCancelled,nullptr);
                }
                _purchaseResultFunc = nullptr;
                SCSystem::setGlobalDisableTouch(false);
                _strCurrentProductID = "";
            }
            break;
            
        case SCID::Msg::kMsgStorePurchaseSuccess:
            {
                SCLog("IAP Purchase success.");
                bool bResult = false;
                auto strProductID = ptrMsg->parameters.getValue(SC_KEY_IAP_PRODUCT).getString(&bResult);
                SCASSERT(bResult);
                SCASSERT(_strCurrentProductID==strProductID);
                
                if(bResult)
                {
                    this->setIAPPurchsed(strProductID);
                }
                
                if(_purchaseResultFunc!=nullptr)
                {
                    _purchaseResultFunc(_strCurrentProductID,EResultType::kSuccess,nullptr);
                }
                _purchaseResultFunc = nullptr;
                SCSystem::setGlobalDisableTouch(false);
                _strCurrentProductID = "";
            }
            break;
            
        case SCID::Msg::kMsgStorePurchaseFailed:
            {
                SCLog("IAP Purchase failed.");
                if(_purchaseResultFunc!=nullptr)
                {
                    _purchaseResultFunc(_strCurrentProductID,EResultType::kFailed,nullptr);
                }
                _purchaseResultFunc = nullptr;
                SCSystem::setGlobalDisableTouch(false);
                _strCurrentProductID = "";
            }
            break;
            
        case SCID::Msg::kMsgStoreRestoreSuccess:
            {
                SCLog("Restored IAP success.");
                bool bResult = false;
                auto strProductID = ptrMsg->parameters.getValue(SC_KEY_IAP_PRODUCT).getString(&bResult);
                SCASSERT(bResult);
                
                if(bResult)
                {
                    this->setIAPPurchsed(strProductID);
                }
                
                if(_restoreResultFunc!=nullptr)
                {
                    _restoreResultFunc(strProductID,EResultType::kSuccess,nullptr);
                }
                _restoreResultFunc = nullptr;
                
                SCSystem::setGlobalDisableTouch(false);
            }
            break;
            
        case SCID::Msg::kMsgStoreRestoreFailed:
            {
                SCLog("Restored IAP failed.");
                if(_restoreResultFunc!=nullptr)
                {
                    _restoreResultFunc("",EResultType::kFailed,nullptr);
                }
                _restoreResultFunc = nullptr;
                SCSystem::setGlobalDisableTouch(false);
            }
            break;
            
        case SCID::Msg::kMsgStoreIAPInfoSuccess:
            {
                SCLog("Request IAP info success.");
                bool bResult = false;
                auto strProductID = ptrMsg->parameters.getValue(SC_KEY_IAP_PRODUCT).getString(&bResult);
                SCASSERT(bResult);
                bResult = false;
                auto strCurrency = ptrMsg->parameters.getValue(SC_KEY_CURRENCY).getString(&bResult);
                SCASSERT(bResult);
                float fPrice = ptrMsg->parameters.getValue(SC_KEY_PRICE).getFloat();
                if(bResult)
                {
                    this->setIAPInfo(strProductID, fPrice, strCurrency);
                }
                
                if(_requestIAPInfoResultFunc!=nullptr)
                {
                    auto info = _iap2PriceInfoMap[strProductID];
                    _requestIAPInfoResultFunc(strProductID,EResultType::kSuccess,&info);
                }
                _requestIAPInfoResultFunc = nullptr;
            }
            break;
            
        case SCID::Msg::kMsgStoreIAPInfoFailed:
            {
                SCLog("Request IAP info failed.");
                if(_requestIAPInfoResultFunc!=nullptr)
                {
                    _requestIAPInfoResultFunc("",EResultType::kFailed,nullptr);
                }
                _requestIAPInfoResultFunc = nullptr;
            }
            break;
        }
    }
}
