//

#include "SCMessage.h"
#include "../base/SCMacroDef.h"

namespace SpeedCC
{
    SCMessageMatcher::SCMessageMatcher(const int nMsgID,const std::function<bool (SCMessage::Ptr ptrMsg)>& func):
    _nMsgID(nMsgID),
    _func(func)
    {
    }
    
    SCMessageMatcher::SCMessageMatcher(const SCString& strCommand,const std::function<bool (SCMessage::Ptr ptrMsg)>& func):
    _strCommand(strCommand),
    _nMsgID(SCID::Msg::kSCMsgCommand),
    _func(func)
    {
    }
    
    bool SCMessageMatcher::isMatch(const SCMessage::Ptr ptrMsg) const
    {
        SC_RETURN_IF((_func==NULL || ptrMsg==NULL || _nMsgID!=ptrMsg->nMsgID), false);
        
        if(_nMsgID==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_IF(_strCommand.isEmpty(),false);
            
            auto value = ptrMsg->paramters.getValue(MSG_KEY_COMMAND);
            SC_RETURN_IF(!value.isValidObject<SCString>(),false);
            
            auto command = value.getString();
            SC_RETURN_IF(command!=_strCommand,false);
        }
        
        return _func(ptrMsg);
    }
}

