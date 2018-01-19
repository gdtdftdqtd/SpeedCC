//
//  SCBehaviorComponent.cpp
//  libspeedcc
//
//  Created by Kevin on 19/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCBehaviorComponent.h"
#include "SCComponentMacroDef.h"
#include "SCMessageDispatch.h"

namespace SpeedCC
{
    SCBehaviorDeliverMessage::SCBehaviorDeliverMessage(const bool bSend,SCMessage::Ptr ptrMsg):
    _bSend(bSend)
    {
        SCASSERT(ptrMsg!=NULL);
        _ptrMsg = ptrMsg->clone();
    }
    
    SCBehaviorDeliverMessage::SCBehaviorDeliverMessage(const bool bSend,const int nMsgID):
    _bSend(bSend)
    {
        _ptrMsg = SCMessage::create(nMsgID);
    }
    
    SCBehaviorDeliverMessage::SCBehaviorDeliverMessage(const bool bSend,const SCString& strCmd):
    _bSend(bSend)
    {
        _ptrMsg = SCMessage::create(strCmd);
    }
    
    void SCBehaviorDeliverMessage::execute(const SCDictionary& par)
    {
        SCASSERT(_ptrMsg!=NULL);
        
        if(_bSend)
        {
            SCMsgDisp()->sendMessage(_ptrMsg);
        }
        else
        {
            SCMsgDisp()->postMessage(_ptrMsg);
        }
    }
}
