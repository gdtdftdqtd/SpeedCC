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
        SCVersion();
        SCVersion(const SCVersion& info);
        SCVersion(const char* pszVersion);
        SCVersion(const SCString& str);
        SCVersion(unsigned uVersion);
        
        SCString getString(int nBit=2) const;
        unsigned getHexValue(int nBit=2) const;
        
        inline int getMajor() const {return _nMajor;}
        inline int getMinor() const {return _nMinor;}
        inline int getFix() const {return _nFix;}
        
        int compare(const SCVersion& info) const;
        bool operator<(const SCVersion& info) const;
        bool operator<=(const SCVersion& info) const;
        bool operator>(const SCVersion& info) const;
        bool operator>=(const SCVersion& info) const;
        bool operator==(const SCVersion& info) const;
        
    private:
        void setString(const SCString& strVersion);
        
    private:
        int _nMajor;
        int _nMinor;
        int _nFix;
    };
}

#endif //__SPEEDCC__SCVERSION_H__
