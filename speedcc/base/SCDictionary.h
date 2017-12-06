

#ifndef __SPEEDCC__SCDICTIONARY_H__
#define __SPEEDCC__SCDICTIONARY_H__

#include "SCObjRefT.h"
#include "SCValue.h"

namespace SpeedCC
{
    class SCDictionary : public SCObjRefT<std::map<SCString,SCValue> >
    {
    public:
        SCDictionary();
        SCDictionary(const SCString& strJson);
        bool loadFromJsonString(const SCString& strJson);
        SCString exportJsonString();
        SCValue& operator[](const SCString& strKey);
        SCValue operator[](const SCString& strKey) const;
        
        void setValue(const SCString& strKey,const SCValue& value);
        void setDictionary(const SCString& strKey,const SCDictionary& dic);
        
        SCValue getValue(const SCString& strKey) const;
        SCDictionary getDictionary(const SCString& strKey) const;
        
        bool hasKey(const SCString& strKey) const;
        void removeKey(const SCString& strKey);
        void removeAllKeys();
        bool isEmpty();
        void forEach(const std::function<bool(const SCString& strKey,const SCValue& value)>& func) const;
        void forEach(const std::function<bool(const SCString& strKey,SCValue& value)>& func);
    };
}

#endif //__SPEEDCC__SCDICTIONARY_H__
