//



#ifndef __SC__BASECOMMON_H__
#define __SC__BASECOMMON_H__

#include "SCString.h"

namespace SPEEDCC
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
    
}

#endif // __SC__BASECOMMON_H__
