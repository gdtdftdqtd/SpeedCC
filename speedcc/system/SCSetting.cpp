//
//  SCSetting.cpp
//  libspeedcc
//
//  Created by Kevin on 21/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "cocos2d.h"
#include "SCSetting.h"

#include "SCConfig.h"
#include "../cocos/SCCocosDef.h"
#include "../component/SCMessageDispatch.h"


namespace SpeedCC
{
    SCSetting*       SCSetting::s_pInstance = NULL;
    
    SCSetting* SCSetting::getInstance()
    {
        if(s_pInstance==NULL)
        {
            s_pInstance = new SCSetting();
        }
        
        return s_pInstance;
    }
    
    SCSetting::SCSetting()
    {
    }
    
    SCWatchInt::Ptr SCSetting::getWatchInt(const SCString& strKey,const int nDefault)
    {
        SCASSERT(!strKey.isEmpty());
        SC_RETURN_IF(strKey.isEmpty(), NULL);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=NULL);
            return (*it).second.cast<SCWatchInt::Ptr>();
        }
        
        SCWatchInt::Ptr ret = SCWatchInt::create();
        
        ret->addUpdateFunc([strKey](SCWatchInt::Ptr watchPtr,const int nNew,const int nOld)
                               {
                                   SCCCUserDefault()->setIntegerForKey(strKey, nNew);
                               });
        
        (*ret) = SCCCUserDefault()->getIntegerForKey(strKey,nDefault);
        SCMapInsert(_key2WatchNumMap, strKey, ret);
        return ret;
    }
    
    
    SCWatchBool::Ptr SCSetting::getWatchBool(const SCString& strKey,const bool bDefault)
    {
        SCASSERT(!strKey.isEmpty());
        SC_RETURN_IF(strKey.isEmpty(), NULL);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=NULL);
            return (*it).second.cast<SCWatchBool::Ptr>();
        }
        
        bool bValue = SCCCUserDefault()->getBoolForKey(strKey,bDefault);
        auto ret = SCWatchBool::create(bValue);
        
        ret->addUpdateFunc([strKey](SCWatchBool::Ptr watchPtr,const bool bNew)
                          {
                              SCCCUserDefault()->setBoolForKey(strKey, bNew);
                              if(strKey==kSCSettingKeySound)
                              {
                                  SCMsgDisp()->postMessage(SCID::Msg::kSCMsgSettingSoundChanged);
                              }
                              else if(strKey==kSCSettingKeyMusic)
                              {
                                  SCMsgDisp()->postMessage(SCID::Msg::kSCMsgSettingMusicChanged);
                              }
                          });
        
        SCMapInsert(_key2WatchNumMap, strKey, ret);
        return ret;
    }
    
    
    SCWatchFloat::Ptr SCSetting::getWatchFloat(const SCString& strKey,const float fDefault)
    {
        SCASSERT(!strKey.isEmpty());
        SC_RETURN_IF(strKey.isEmpty(), NULL);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=NULL);
            return (*it).second.cast<SCWatchFloat::Ptr>();
        }
        
        auto ret = SCWatchFloat::create();
        
        ret->addUpdateFunc([strKey](SCWatchFloat::Ptr watchPtr,const float fNew,const float fOld)
                          {
                              SCCCUserDefault()->setFloatForKey(strKey, fNew);
                          });
        
        (*ret) = SCCCUserDefault()->getFloatForKey(strKey,fDefault);
        SCMapInsert(_key2WatchNumMap, strKey, ret);
        return ret;
    }
    
    SCWatchDouble::Ptr SCSetting::getWatchDouble(const SCString& strKey,const double dDefault)
    {
        SCASSERT(!strKey.isEmpty());
        SC_RETURN_IF(strKey.isEmpty(), NULL);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=NULL);
            return (*it).second.cast<SCWatchDouble::Ptr>();
        }
        
        auto ret = SCWatchDouble::create();
        
        ret->addUpdateFunc([strKey](SCWatchDouble::Ptr watchPtr,const double dNew,const double dOld)
                          {
                              SCCCUserDefault()->setDoubleForKey(strKey, dNew);
                          });
        
        (*ret) = SCCCUserDefault()->getDoubleForKey(strKey,dDefault);
        SCMapInsert(_key2WatchNumMap, strKey, ret);
        return ret;
    }
    
    SCWatchString::Ptr SCSetting::getWatchString(const SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        SC_RETURN_IF(strKey.isEmpty(), NULL);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=NULL);
            return (*it).second.cast<SCWatchString::Ptr>();
        }
        
        auto ret = SCWatchString::create();
        
        ret->addUpdateFunc([strKey](SCWatchString::Ptr watchPtr,const SCString& strNew,const SCString& strOld)
                          {
                              SCCCUserDefault()->setStringForKey(strKey, strNew.c_str());
                          });
        
        (*ret) = SCCCUserDefault()->getStringForKey(strKey);
        SCMapInsert(_key2WatchNumMap, strKey, ret);
        return ret;
    }
    
    SCWatchBool::Ptr SCSetting::getSoundWatch(const bool bDefault)
    {
        return this->getWatchBool(kSCSettingKeySound,bDefault);
    }
    
    SCWatchBool::Ptr SCSetting::getMusicWatch(const bool bDefault)
    {
        return this->getWatchBool(kSCSettingKeyMusic,bDefault);
    }
    
    void SCSetting::flush()
    {
        SCCCUserDefault()->flush();
    }
    
    SCDictionary SCSetting::asDictionary()
    {
        SCDictionary ret;
        
        for(auto it : _key2WatchNumMap)
        {
            auto v1 = it.second.cast<SCWatchInt::Ptr>();
            if(v1!=NULL)
            {
                ret.setValue(it.first,v1->getValue());
                continue;
            }
            
            auto v2 = it.second.cast<SCWatchString::Ptr>();
            if(v2!=NULL)
            {
                ret.setValue(it.first,v2->getValue());
                continue;
            }
            
            auto v3 = it.second.cast<SCWatchBool::Ptr>();
            if(v3!=NULL)
            {
                ret.setValue(it.first,v3->getValue());
                continue;
            }
            
            auto v4 = it.second.cast<SCWatchFloat::Ptr>();
            if(v4!=NULL)
            {
                ret.setValue(it.first,v4->getValue());
                continue;
            }
            
            auto v5 = it.second.cast<SCWatchDouble::Ptr>();
            if(v5!=NULL)
            {
                ret.setValue(it.first,v5->getValue());
                continue;
            }
            
            SCASSERT(false);
        }
        
        return ret;
        
    }
}


