

#include "SCDictionary.h"

namespace SpeedCC
{
    ///------------- SCDictionary
    SCDictionary::SCDictionary()
    {
        this->createInstance();
    }
    
    SCValue& SCDictionary::operator[](const SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        this->clone4Write();
        return (*this->getStub())[strKey];
    }
    
    SCValue SCDictionary::operator[](SCString& strKey)
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
    
    SCValue SCDictionary::getValue(const SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        return (*this->getStub())[strKey];
    }
    
    bool SCDictionary::hasKey(const SCString& strKey) const
    {
        SCASSERT(!strKey.isEmpty());
        const auto& it = this->getStub()->find(strKey);
        return (this->getStub()->end()!=it);
    }
    
    void SCDictionary::removeKey(const SCString& strKey)
    {
        SCASSERT(!strKey.isEmpty());
        this->clone4Write();
        this->getStub()->erase(strKey);
    }
    
    void SCDictionary::removeAllKey()
    {
        this->clone4Write();
        this->getStub()->clear();
    }
    
    bool SCDictionary::isEmpty()
    {
        return this->getStub()->empty();
    }
    
    void SCDictionary::forEach(const std::function<bool(const SCString& strKey,const SCValue& value)>& func) const
    {
        const auto& map = *(this->getStub());
        for(const auto& it : map)
        {
            SC_RETURN_IF_V(!func(it.first,it.second));
        }
    }
    
    void SCDictionary::forEach(const std::function<bool(const SCString& strKey,SCValue& value)>& func)
    {
        this->clone4Write();
        auto& map = *(this->getStub());
        for(auto& it : map)
        {
            SC_RETURN_IF_V(!func(it.first,it.second));
        }
    }
}
