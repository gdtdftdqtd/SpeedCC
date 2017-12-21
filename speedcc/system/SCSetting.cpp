//
//  SCSetting.cpp
//  libspeedcc
//
//  Created by Kevin on 21/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#include "cocos2d.h"
#include "SCSetting.h"

namespace SpeedCC
{
    SCSetting*       SCSetting::s_pInstance = NULL;
    
    SCSetting* SCSetting::getInstance()
    {
        if(s_pInstance!=NULL)
        {
            s_pInstance = new SCSetting();
        }
        
        return s_pInstance;
    }
    
    SCWatchInt::Ptr SCSetting::getWatchInt(const SCString& strKey,const int nDefault)
    {
        SCASSERT(!strKey.isEmpty());
        SC_RETURN_IF(strKey.isEmpty(), NULL);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=NULL);
            return (*it).second.cast<SCWatchInt>();
        }
        
        SCWatchInt::Ptr ret = SCWatchInt::create();
        
        ret->addUpdateFun([strKey](SCWatchInt::Ptr watchPtr,const int nNew,const int nOld)
                               {
                                   cocos2d::UserDefault::getInstance()->setIntegerForKey(strKey, nNew);
                               });
        
        (*ret) = cocos2d::UserDefault::getInstance()->getIntegerForKey(strKey,nDefault);
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
            return (*it).second.cast<SCWatchBool>();
        }
        
        auto ret = SCWatchBool::create();
        
        ret->addUpdateFun([strKey](SCWatchBool::Ptr watchPtr,const bool bNew,const bool bOld)
                          {
                              cocos2d::UserDefault::getInstance()->setBoolForKey(strKey, bNew);
                          });
        
        (*ret) = cocos2d::UserDefault::getInstance()->getBoolForKey(strKey,bDefault);
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
            return (*it).second.cast<SCWatchFloat>();
        }
        
        auto ret = SCWatchFloat::create();
        
        ret->addUpdateFun([strKey](SCWatchFloat::Ptr watchPtr,const float fNew,const float fOld)
                          {
                              cocos2d::UserDefault::getInstance()->setFloatForKey(strKey, fNew);
                          });
        
        (*ret) = cocos2d::UserDefault::getInstance()->getFloatForKey(strKey,fDefault);
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
            return (*it).second.cast<SCWatchDouble>();
        }
        
        auto ret = SCWatchDouble::create();
        
        ret->addUpdateFun([strKey](SCWatchDouble::Ptr watchPtr,const double dNew,const double dOld)
                          {
                              cocos2d::UserDefault::getInstance()->setDoubleForKey(strKey, dNew);
                          });
        
        (*ret) = cocos2d::UserDefault::getInstance()->getDoubleForKey(strKey,dDefault);
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
            return (*it).second.cast<SCWatchString>();
        }
        
        auto ret = SCWatchString::create();
        
        ret->addUpdateFun([strKey](SCWatchString::Ptr watchPtr,const SCString& strNew,const SCString& strOld)
                          {
                              cocos2d::UserDefault::getInstance()->setStringForKey(strKey, strNew.c_str());
                          });
        
        (*ret) = cocos2d::UserDefault::getInstance()->getStringForKey(strKey);
        SCMapInsert(_key2WatchNumMap, strKey, ret);
        return ret;
    }
    
    SCDictionary SCSetting::exportAsDictionary()
    {
        SCDictionary ret;
        
        for(auto it : _key2WatchNumMap)
        {
            auto v1 = it.second.cast<SCWatchInt>();
            if(v1!=NULL)
            {
                ret.setValue(it.first,v1->getValue());
                continue;
            }
            
            auto v2 = it.second.cast<SCWatchString>();
            if(v2!=NULL)
            {
                ret.setValue(it.first,v2->getValue());
                continue;
            }
            
            auto v3 = it.second.cast<SCWatchBool>();
            if(v3!=NULL)
            {
                ret.setValue(it.first,v3->getValue());
                continue;
            }
            
            auto v4 = it.second.cast<SCWatchFloat>();
            if(v4!=NULL)
            {
                ret.setValue(it.first,v4->getValue());
                continue;
            }
            
            auto v5 = it.second.cast<SCWatchDouble>();
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


