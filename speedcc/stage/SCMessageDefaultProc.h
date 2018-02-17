//
//  SCMessageDefaultProc.hpp
//  libspeedcc
//
//  Created by Kevin on 26/12/2017.
//  Copyright © 2017 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCMESSAGEDEFAULTPROC_H__
#define __SPEEDCC__SCMESSAGEDEFAULTPROC_H__

#include "SCMessage.h"

namespace SpeedCC
{
    class SCMessageDefaultProc final
    {
        friend class SCMessageDispatch;
        
    public:
        void addAlertBoxCallback(const std::function<void(int)>& func, const int nAlertBoxID);
        
    protected:
        void processMessage(SCMessage::Ptr ptrMsg);
        
    private:
        std::map<int,std::function<void(int)> >     _alertBoxID2CBMap;
    };
}

#endif // __SPEEDCC__SCMESSAGEDEFAULTPROC_H__
