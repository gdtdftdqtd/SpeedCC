//
//  SCMessageDefaultProc.hpp
//  libspeedcc
//
//  Created by Kevin on 26/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCMESSAGEDEFAULTPROC_H__
#define __SPEEDCC__SCMESSAGEDEFAULTPROC_H__

#include "SCMessageDef.h"

namespace SpeedCC
{
    class SCMessageDefaultProc
    {
        friend class SCMessageDispatch;
        
    protected:
        void processMessage(SSCMessageInfo& mi);
    };
}

#endif // __SPEEDCC__SCMESSAGEDEFAULTPROC_H__
