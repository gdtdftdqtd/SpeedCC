//
//  SCSetting.hpp
//  libspeedcc
//
//  Created by Kevin on 21/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCSETTING_H__
#define __SPEEDCC__SCSETTING_H__

#include "../base/SCWatchNumberT.h"
#include "../base/SCWatchString.h"
#include "../base/SCDictionary.h"


namespace SpeedCC
{
    class SCSetting
    {
    public:
        SC_AVOID_CLASS_COPY(SCSetting)
        
        static SCSetting* getInstance();
        
        SCWatchInt::Ptr getWatchInt(const SCString& strKey,const int nDefault=0);
        SCWatchBool::Ptr getWatchBool(const SCString& strKey,const bool bDefault=false);
        SCWatchFloat::Ptr getWatchFloat(const SCString& strKey,const float fDefault=0.0f);
        SCWatchDouble::Ptr getWatchDouble(const SCString& strKey,const double dDefault=0.0);
        SCWatchString::Ptr getWatchString(const SCString& strKey);
        
        SCDictionary exportAsDictionary();
        
    private:
        SCSetting() {}
        
    private:
        std::map<SCString,SCObject::Ptr>        _key2WatchNumMap;
        static SCSetting*                       s_pInstance;
    };
}

#endif // __SPEEDCC__SCSETTING_H__
