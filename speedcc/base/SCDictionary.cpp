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

#include "SCDictionary.h"
#include "SCSystem.h"

#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"

namespace SpeedCC
{
    ///------------- SCDictionary
    SCDictionary::SCDictionary()
    {
        this->createInstance();
    }
    
    SCDictionary::SCDictionary(const SCString& strKey,const SCValue& value)
    {
        this->createInstance();
        this->setValue(strKey, value);
    }
    
    SCDictionary::SCDictionary(const SPair& pair)
    {
        this->createInstance();
        this->setValue(pair);
    }
    
    SCDictionary::SCDictionary(const SPair* pPairArray,const int nCount)
    {
        this->createInstance();
        this->setValue(pPairArray,nCount);
    }
    
    SCDictionary::SCDictionary(const std::vector<SPair>& pairVct)
    {
        this->createInstance();
        this->setValue(pairVct);
    }
    
    SCDictionary::SCDictionary(const SCString& strJson)
    {
        this->createInstance();
        this->loadFromJsonString(strJson);
    }
    
    SCValue& SCDictionary::operator[](const SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        this->clone4Write();
        return (*this->getStub())[strKey];
    }
    
    SCValue SCDictionary::operator[](const SCString& strKey) const
    {
        SCASSERT(!strKey.isEmpty());
        return (*this->getStub())[strKey];
    }
    
    void SCDictionary::setValue(const SCString& strKey,const SCValue& value)
    {
        SCASSERT(!strKey.isEmpty());
        this->clone4Write();
        auto& map = (*this->getStub());
        map[strKey] = value;
    }
    
    void SCDictionary::setValue(const SPair& pair)
    {
        SCASSERT(!pair.strKey.isEmpty());
        this->clone4Write();
        auto& map = (*this->getStub());
        map[pair.strKey] = pair.value;
    }
    
    void SCDictionary::setValue(const SPair* pPairArray,const int nCount)
    {
        SC_RETURN_V_IF(pPairArray==nullptr || nCount<=0);
        this->clone4Write();
        auto& map = (*this->getStub());
        
        for(int i=0;i<nCount;++i)
        {
            auto pair = pPairArray[i];
            SCASSERT(!pair.strKey.isEmpty());
            map[pair.strKey] = pair.value;
        }
    }
    
    void SCDictionary::setValue(const std::vector<SPair>& pairVct)
    {
        SC_RETURN_V_IF(pairVct.empty());
        this->clone4Write();
        auto& map = (*this->getStub());

        for(const auto& pair : pairVct)
        {
            SCASSERT(!pair.strKey.isEmpty());
            map[pair.strKey] = pair.value;
        }
    }
    
    void SCDictionary::setDictionary(const SCString& strKey,const SCDictionary& dic)
    {
        this->setValue(strKey,SCValue::create(dic));
    }
    
    SCValue SCDictionary::getValue(const SCString& strKey) const
    {
        SCASSERT(!strKey.isEmpty());
        return (*this->getStub())[strKey];
    }
    
    SCDictionary SCDictionary::getDictionary(const SCString& strKey) const
    {
        SCDictionary retDic;
        auto value = this->getValue(strKey);
        if(value.isValidObject<SCDictionary>())
        {
            retDic = value.getObject<SCDictionary>();
        }
        
        return retDic;
    }
    
    bool SCDictionary::hasKey(const SCString& strKey) const
    {
        SCASSERT(!strKey.isEmpty());
        const auto& it = this->getStub()->find(strKey);
        return (this->getStub()->end()!=it);
    }
    
    int SCDictionary::getCount() const
    {
        return (int)this->getStub()->size();
    }
    
    void SCDictionary::removeKey(const SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        this->clone4Write();
        this->getStub()->erase(strKey);
    }
    
    void SCDictionary::removeAllKeys()
    {
        this->clone4Write();
        this->getStub()->clear();
    }
    
    bool SCDictionary::isEmpty() const
    {
        return this->getStub()->empty();
    }
    
    void SCDictionary::forEach(const std::function<bool(const SCString& strKey,const SCValue& value)>& func) const
    {
        const auto& map = *(this->getStub());
        for(auto& it : map)
        {
            SC_RETURN_V_IF(!func(it.first,it.second));
        }
    }
    
    void SCDictionary::forEach(const std::function<bool(const SCString& strKey,SCValue& value)>& func)
    {
        this->clone4Write();
        auto& map = *(this->getStub());
        for(auto& it : map)
        {
            SC_RETURN_V_IF(!func(it.first,it.second));
        }
    }
    
    ///------------- json relate
    SCValue parseJsonObject(const rapidjson::Value& val);
    SCValue parseJsonArray(const rapidjson::Value& val);
    rapidjson::Value exportJsonObject(const SCDictionary& dic,rapidjson::Document::AllocatorType& allocator);
    rapidjson::Value exportJsonArray(const std::vector<SCValue>& array,rapidjson::Document::AllocatorType& allocator);
    
    bool SCDictionary::loadFromJsonString(const SCString& strJson)
    {
        if(strJson.isEmpty())
        {
            this->removeAllKeys();
            return true;
        }
        
        rapidjson::Document jsonDoc;
        jsonDoc.Parse(strJson.c_str());
        
        if(jsonDoc.HasParseError())
        {
            SCLog("SCDictionary parse json error: %d",jsonDoc.GetParseError());
            return false;
        }
        
        for(auto it = jsonDoc.MemberBegin(); it!=jsonDoc.MemberEnd(); ++it)
        {
            auto key = (it->name).GetString();
            const rapidjson::Value& val = it->value;
            
            switch(val.GetType())
            {
                case rapidjson::kNullType: this->setValue(key, SCValue()); break;
                case rapidjson::kTrueType:
                case rapidjson::kFalseType: this->setValue(key, SCValue(val.GetBool())); break;
                case rapidjson::kStringType: this->setValue(key, SCValue(val.GetString()));break;
                case rapidjson::kNumberType: this->setValue(key, SCValue(val.GetInt()));break;
                case rapidjson::kObjectType: this->setValue(key,parseJsonObject(val));break;
                case rapidjson::kArrayType: this->setValue(key,parseJsonArray(val));break;
            }
        }
        
        return true;
    }
    
    SCString SCDictionary::exportJsonString()
    {
        SC_RETURN_IF(this->isEmpty(), "{}");
        
        rapidjson::Document jsonDoc;
        this->forEach([&jsonDoc](const SCString& strKey,const SCValue& value) -> bool
                      {
                          rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                          
                          switch(value.getType())
                          {
                              default:
                              case SCValue::DATABLOCK_TYPE:
                              case SCValue::POINTER_TYPE:
                              case SCValue::UNKNOWN_TYPE:       jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(rapidjson::kNullType),allocator);
                                  break;
                              case SCValue::BYTE_TYPE:
                              case SCValue::INT_TYPE:
                              case SCValue::LONG_TYPE:
                                  jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getInt()),allocator);
                                  break;
                                  
                              case SCValue::UINT_TYPE:
                                  jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getUnsignedInt()),allocator);
                                  break;
                              case SCValue::INT64_TYPE:
                                  jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getInt64()),allocator);
                                  break;
                                  
                              case SCValue::BOOL_TYPE:
                                  jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getBool()),allocator);
                                  break;
                                  
                              case SCValue::FLOAT_TYPE:
                                  jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getFloat()),allocator);
                                  break;
                                  
                              case SCValue::DOUBLE_TYPE:
                                  jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getDouble()),allocator);
                                  break;
                                  
                              case SCValue::DATETIME_TYPE:
                              case SCValue::CHAR_TYPE:
                              case SCValue::STRING_TYPE:
                                  jsonDoc.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getString(),allocator),allocator);
                                  break;
                                  
                              case SCValue::ARRAY_TYPE:
                              {
                                  auto array = value.getArray();
                                  auto val = exportJsonArray(array,allocator);
                                  jsonDoc.AddMember(rapidjson::Value(strKey,allocator),val,allocator);
                              }
                                  break;
                                  
                              case SCValue::OBJECT_TYPE:
                              {
                                  if(value.isValidObject<SCDictionary>())
                                  {
                                      auto dic = value.getObject<SCDictionary>();
                                      auto val = exportJsonObject(dic,allocator);
                                      jsonDoc.AddMember(rapidjson::Value(strKey,allocator),val,allocator);
                                  }
                              }
                                  break;
                          }
                          return true;
                      });
        
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        jsonDoc.Accept(writer);
        
        return buffer.GetString();
    }
    
    rapidjson::Value exportJsonObject(const SCDictionary& dic,rapidjson::Document::AllocatorType& allocator)
    {
        rapidjson::Value retVal;
        retVal.SetObject();
        
        dic.forEach([&retVal,&allocator](const SCString& strKey,const SCValue& value) -> bool
                      {
                          switch(value.getType())
                          {
                              default:
                              case SCValue::DATABLOCK_TYPE:
                              case SCValue::POINTER_TYPE:
                              case SCValue::UNKNOWN_TYPE:       retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(rapidjson::kNullType),allocator);
                                  break;
                              case SCValue::BYTE_TYPE:
                              case SCValue::INT_TYPE:
                              case SCValue::LONG_TYPE:
                                  retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getInt()),allocator);
                                  break;
                                  
                              case SCValue::UINT_TYPE:
                                  retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getUnsignedInt()),allocator);
                                  break;
                              case SCValue::INT64_TYPE:
                                  retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getInt64()),allocator);
                                  break;
                                  
                              case SCValue::BOOL_TYPE:
                                  retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getBool()),allocator);
                                  break;
                                  
                              case SCValue::FLOAT_TYPE:
                                  retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getFloat()),allocator);
                                  break;
                                  
                              case SCValue::DOUBLE_TYPE:
                                  retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getDouble()),allocator);
                                  break;
                                  
                              case SCValue::DATETIME_TYPE:
                              case SCValue::CHAR_TYPE:
                              case SCValue::STRING_TYPE:
                                  retVal.AddMember(rapidjson::Value(strKey,allocator),rapidjson::Value(value.getString(),allocator),allocator);
                                  break;
                                  
                              case SCValue::ARRAY_TYPE:
                              {
                                  auto array = value.getArray();
                                  auto val = exportJsonArray(array,allocator);
                                  retVal.AddMember(rapidjson::Value(strKey,allocator),val,allocator);
                              }
                                  break;
                                  
                              case SCValue::OBJECT_TYPE:
                              {
                                  if(value.isValidObject<SCDictionary>())
                                  {
                                      auto dic = value.getObject<SCDictionary>();
                                      auto val = exportJsonObject(dic,allocator);
                                      retVal.AddMember(rapidjson::Value(strKey,allocator),val,allocator);
                                  }
                              }
                                  break;
                          }
                          return true;
                      });
        
        return retVal;
    }
    
    rapidjson::Value exportJsonArray(const std::vector<SCValue>& array,rapidjson::Document::AllocatorType& allocator)
    {
        rapidjson::Value retVal;
        retVal.SetArray();
        
        for(const auto& value : array)
        {
            switch(value.getType())
            {
                default:
                case SCValue::DATABLOCK_TYPE:
                case SCValue::POINTER_TYPE:
                case SCValue::UNKNOWN_TYPE:
                    retVal.PushBack(rapidjson::Value(rapidjson::kNullType),allocator);
                    break;
                    
                case SCValue::BYTE_TYPE:
                case SCValue::INT_TYPE:
                case SCValue::LONG_TYPE:
                    retVal.PushBack(rapidjson::Value(value.getInt()),allocator);
                    break;
                    
                case SCValue::UINT_TYPE:
                    retVal.PushBack(rapidjson::Value(value.getUnsignedInt()),allocator);
                    break;
                    
                case SCValue::INT64_TYPE:
                    retVal.PushBack(rapidjson::Value(value.getInt64()),allocator);
                    break;
                    
                case SCValue::BOOL_TYPE:
                    retVal.PushBack(rapidjson::Value(value.getBool()),allocator);
                    break;
                    
                case SCValue::FLOAT_TYPE:
                    retVal.PushBack(rapidjson::Value(value.getFloat()),allocator);
                    break;
                    
                case SCValue::DOUBLE_TYPE:
                    retVal.PushBack(rapidjson::Value(value.getDouble()),allocator);
                    break;
                    
                case SCValue::DATETIME_TYPE:
                case SCValue::CHAR_TYPE:
                case SCValue::STRING_TYPE:
                    retVal.PushBack(rapidjson::Value(value.getString(),allocator),allocator);
                    break;
                    
                case SCValue::ARRAY_TYPE:
                {
                    auto array = value.getArray();
                    auto val = exportJsonArray(array,allocator);
                    retVal.PushBack(val,allocator);
                }
                    break;
                    
                case SCValue::OBJECT_TYPE:
                {
                    if(value.isValidObject<SCDictionary>())
                    {
                        auto dic = value.getObject<SCDictionary>();
                        auto val = exportJsonObject(dic,allocator);
                        retVal.PushBack(val,allocator);
                    }
                }
                    break;
            }
        }
        
        return retVal;
    }
    
    SCValue parseJsonArray(const rapidjson::Value& val)
    {
        SCValue retVal;
        
        SC_RETURN_IF(!val.IsArray(), retVal);
        
        std::vector<SCValue> array;
        array.resize(val.Capacity());
        
        const auto jsonArray = val.GetArray();
        
        for (int i = 0; i<jsonArray.Capacity(); ++i)
        {
            const rapidjson::Value& val2 = jsonArray[i];
            switch(val2.GetType())
            {
                case rapidjson::kNullType: array[i] = SCValue(); break;
                case rapidjson::kTrueType:
                case rapidjson::kFalseType: array[i] = SCValue(val.GetBool()); break;
                case rapidjson::kStringType: array[i] = SCValue(val.GetString());break;
                case rapidjson::kNumberType: array[i] = SCValue(val.GetInt());break;
                case rapidjson::kObjectType: array[i] = parseJsonObject(val);break;
                case rapidjson::kArrayType: array[i] = parseJsonArray(val);break;
            }
        }
        
        retVal.setArray(array);
        
        return retVal;
    }
    
    SCValue parseJsonObject(const rapidjson::Value& val)
    {
        SC_RETURN_IF(!val.IsObject(), SCValue());
        
        const auto jsonObj = val.GetObject();
        SCDictionary dic;
        
        for(auto it = jsonObj.MemberBegin(); it!=jsonObj.MemberEnd(); ++it)
        {
            auto key = (it->name).GetString();
            const rapidjson::Value& val2 = it->value;
            
            switch(val2.GetType())
            {
                case rapidjson::kNullType: dic.setValue(key, SCValue()); break;
                case rapidjson::kTrueType:
                case rapidjson::kFalseType: dic.setValue(key, SCValue(val.GetBool())); break;
                case rapidjson::kStringType: dic.setValue(key, SCValue(val.GetString()));break;
                case rapidjson::kNumberType: dic.setValue(key, SCValue(val.GetInt()));break;
                case rapidjson::kObjectType: dic.setValue(key,parseJsonObject(val));break;
                case rapidjson::kArrayType: dic.setValue(key,parseJsonArray(val));break;
            }
        }
        
        return SCValue::create(dic);
    }
}
