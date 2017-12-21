//
//  SCFileUtils.hpp
//  libspeedcc
//
//  Created by Kevin on 8/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCFILEUTILS_H__
#define __SPEEDCC__SCFILEUTILS_H__

#include "../base/SCString.h"

namespace SpeedCC
{
    class SCFileUtils
    {
    public:
        static SCString getFullPathFile(const SCString& strFile);
    };
}

#endif // __SPEEDCC__SCFILEUTILS_H__
