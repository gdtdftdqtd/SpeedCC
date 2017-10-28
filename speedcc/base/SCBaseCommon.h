//



#ifndef __SC__BASECOMMON_H__
#define __SC__BASECOMMON_H__

#include "SCString.h"
#include "SCValue.h"

namespace SpeedCC
{
    ///------------ SCError
    struct SCError
    {
    public:
        enum EErrorCode
        {
            Unkown = -1,
            Success = 0,
        };
        
        SCString        strMessage;
        EErrorCode      ecCode;
    };
    
    ///------------- SCVersionInfo
    struct SCVersionInfo
    {
        int nMajor;
        int nMinor;
        int nFix;
        
        SCVersionInfo();
        SCVersionInfo(const SCVersionInfo& info);
        SCVersionInfo(const char* pszVersion);
        SCVersionInfo(const SCString& str);
        SCVersionInfo(unsigned uVersion);
        SCString getString(int nBit=2) const;
        unsigned getHexValue(int nBit=2) const;
        int compare(const SCVersionInfo& info) const;
        bool operator<(const SCVersionInfo& info) const;
        bool operator<=(const SCVersionInfo& info) const;
        bool operator>(const SCVersionInfo& info) const;
        bool operator>=(const SCVersionInfo& info) const;
        bool operator==(const SCVersionInfo& info) const;
        
    private:
        void setString(const SCString& strVersion);
    };
    
    ///------------- SCParameters
    class SCParameters : public SCObjRefT<std::map<SCString,SCValue> >
    {
    public:
        SCValue& operator[](const SCString& strKey);
        SCValue operator[](SCString& strKey);
        
        void setValue(const SCString& strKey,const SCValue& value);
        SCValue getValue(const SCString& strKey);
        
        bool hasKey(const SCString& strKey) const;
        void removeKey(const SCString& strKey);
        void removeAllKey();
        bool isEmpty();
    };
}

#endif // __SC__BASECOMMON_H__
