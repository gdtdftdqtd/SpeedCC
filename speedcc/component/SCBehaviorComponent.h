//
//  SCBehaviorComponent.hpp
//  libspeedcc
//
//  Created by Kevin on 19/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCBEHAVIORCOMPONENT_H__
#define __SPEEDCC__SCBEHAVIORCOMPONENT_H__

#include "SCPerformObject.h"
#include "SCMessage.h"

namespace SpeedCC
{
    ///------------- SCBehaviorDeliverMessage
    class SCBehaviorDeliverMessage : public SCBehavior
    {
    public:
        SC_AVOID_CLASS_COPY(SCBehaviorDeliverMessage)
        SC_DEFINE_CLASS_PTR(SCBehaviorDeliverMessage)
        
        SC_DEFINE_CREATE_FUNC_2(SCBehaviorDeliverMessage,const bool,SCMessage::Ptr)
        SC_DEFINE_CREATE_FUNC_2(SCBehaviorDeliverMessage,const bool,const int)
        SC_DEFINE_CREATE_FUNC_2(SCBehaviorDeliverMessage,const bool,const SCString&)
        
        virtual void execute(const SCDictionary& par) override;
        
    protected:
        SCBehaviorDeliverMessage(const bool bSend,SCMessage::Ptr ptrMsg);
        SCBehaviorDeliverMessage(const bool bSend,const int nMsgID);
        SCBehaviorDeliverMessage(const bool bSend,const SCString& strCmd);
        
    private:
        SCMessage::Ptr      _ptrMsg;
        bool                _bSend;
    };
    
}

#endif // __SPEEDCC__SCBEHAVIORCOMPONENT_H__
