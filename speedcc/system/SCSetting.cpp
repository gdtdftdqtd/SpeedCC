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

#include "cocos2d.h"
#include "SCSetting.h"

#include "SCConfig.h"
#include "../cocos/SCCocosDef.h"
#include "../stage/SCStageMacros.h"
#include "../stage/SCMessageDispatch.h"


namespace SpeedCC
{
    SCSetting*       SCSetting::s_pInstance = nullptr;
    
    SCSetting* SCSetting::getInstance()
    {
        if(s_pInstance==nullptr)
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
        SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=nullptr);
            return (*it).second.cast<SCWatchInt::Ptr>();
        }
        
        SCWatchInt::Ptr ret = SCWatchInt::create();
        
        ret->addUpdateFunc([strKey](SCWatchInt::Ptr ptrWatch,const int nNew,const int nOld)
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
        SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=nullptr);
            return (*it).second.cast<SCWatchBool::Ptr>();
        }
        
        bool bValue = SCCCUserDefault()->getBoolForKey(strKey,bDefault);
        auto ret = SCWatchBool::create(bValue);
        
        ret->addUpdateFunc([strKey](SCWatchBool::Ptr ptrWatch,const bool bNew,const bool bOld)
                          {
                              SCCCUserDefault()->setBoolForKey(strKey, bNew);
                              if(strKey==kSCSettingKeySound)
                              {
                                  SCMsgDisp()->postMessage(SCID::Msg::kMsgSettingSoundChanged);
                              }
                              else if(strKey==kSCSettingKeyMusic)
                              {
                                  SCMsgDisp()->postMessage(SCID::Msg::kMsgSettingMusicChanged);
                              }
                          });
        
        SCMapInsert(_key2WatchNumMap, strKey, ret);
        return ret;
    }
    
    
    SCWatchFloat::Ptr SCSetting::getWatchFloat(const SCString& strKey,const float fDefault)
    {
        SCASSERT(!strKey.isEmpty());
        SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=nullptr);
            return (*it).second.cast<SCWatchFloat::Ptr>();
        }
        
        auto ret = SCWatchFloat::create();
        
        ret->addUpdateFunc([strKey](SCWatchFloat::Ptr ptrWatch,const float fNew,const float fOld)
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
        SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=nullptr);
            return (*it).second.cast<SCWatchDouble::Ptr>();
        }
        
        auto ret = SCWatchDouble::create();
        
        ret->addUpdateFunc([strKey](SCWatchDouble::Ptr ptrWatch,const double dNew,const double dOld)
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
        SC_RETURN_IF(strKey.isEmpty(), nullptr);
        
        auto it = _key2WatchNumMap.find(strKey);
        
        if(it!=_key2WatchNumMap.end())
        {
            SCASSERT((*it).second!=nullptr);
            return (*it).second.cast<SCWatchString::Ptr>();
        }
        
        auto ret = SCWatchString::create();
        
        ret->addUpdateFunc([strKey](SCWatchString::Ptr ptrWatch,const SCString& strNew,const SCString& strOld)
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
            if(v1!=nullptr)
            {
                ret.setValue(it.first,v1->getValue());
                continue;
            }
            
            auto v2 = it.second.cast<SCWatchString::Ptr>();
            if(v2!=nullptr)
            {
                ret.setValue(it.first,v2->getValue());
                continue;
            }
            
            auto v3 = it.second.cast<SCWatchBool::Ptr>();
            if(v3!=nullptr)
            {
                ret.setValue(it.first,v3->getValue());
                continue;
            }
            
            auto v4 = it.second.cast<SCWatchFloat::Ptr>();
            if(v4!=nullptr)
            {
                ret.setValue(it.first,v4->getValue());
                continue;
            }
            
            auto v5 = it.second.cast<SCWatchDouble::Ptr>();
            if(v5!=nullptr)
            {
                ret.setValue(it.first,v5->getValue());
                continue;
            }
            
            SCASSERT(false);
        }
        
        return ret;
        
    }
}


