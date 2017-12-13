//
//  SCVersion.hpp
//  libspeedcc
//
//  Created by Kevin on 2/11/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCVERSION_H__
#define __SPEEDCC__SCVERSION_H__

#include "SCString.h"

namespace SpeedCC
{
    ///------------- SCVersion
    struct SCVersion
    {
    public:
        int nMajor;
        int nMinor;
        int nFix;
        
    public:
        SCVersion();
        SCVersion(const SCVersion& info);
        SCVersion(const char* pszVersion);
        SCVersion(const SCString& str);
        SCVersion(unsigned uVersion);
        
        SCString getString(int nBit=2) const;
        unsigned getHexValue(int nBit=2) const;
        
        int compare(const SCVersion& info) const;
        bool operator<(const SCVersion& info) const;
        bool operator<=(const SCVersion& info) const;
        bool operator>(const SCVersion& info) const;
        bool operator>=(const SCVersion& info) const;
        bool operator==(const SCVersion& info) const;
        
    private:
        void setString(const SCString& strVersion);
        
    };
}

#endif //__SPEEDCC__SCVERSION_H__
