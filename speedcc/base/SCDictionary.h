

#ifndef __SPEEDCC__SCDICTIONARY_H__
#define __SPEEDCC__SCDICTIONARY_H__

#include "SCObjRefT.h"
#include "SCString.h"
#include "SCValue.h"

namespace SpeedCC
{
    class SCDictionary : public SCObjRefT<std::map<SCString,SCValue> >
    {
    public:
        SCDictionary();
        SCValue& operator[](const SCString& strKey);
        SCValue operator[](SCString& strKey);
        
        void setValue(const SCString& strKey,const SCValue& value);
        SCValue getValue(const SCString& strKey);
        
        bool hasKey(const SCString& strKey) const;
        void removeKey(const SCString& strKey);
        void removeAllKeys();
        bool isEmpty();
        void forEach(const std::function<bool(const SCString& strKey,const SCValue& value)>& func) const;
        void forEach(const std::function<bool(const SCString& strKey,SCValue& value)>& func);
    };
}

#endif //__SPEEDCC__SCDICTIONARY_H__
