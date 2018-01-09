//

#include "SCMessage.h"
#include "../base/SCMacroDef.h"

namespace SpeedCC
{
    SCMessageMatcher::SCMessageMatcher(const int nMsgID,const std::function<bool (SCMessage::Ptr mi)>& func):
    _nMsgID(nMsgID),
    _func(func)
    {
    }
    
    SCMessageMatcher::SCMessageMatcher(const SCString& strCommand,const std::function<bool (SCMessage::Ptr mi)>& func):
    _strCommand(strCommand),
    _nMsgID(SCID::Msg::kSCMsgCommand),
    _func(func)
    {
    }
    
    bool SCMessageMatcher::isMatch(const SCMessage::Ptr mi) const
    {
        SC_RETURN_IF((_func==NULL || mi==NULL || _nMsgID!=mi->nMsgID), false);
        
        if(_nMsgID==SCID::Msg::kSCMsgCommand)
        {
            SC_RETURN_IF(_strCommand.isEmpty(),false);
            
            auto value = mi->paramters.getValue(MSG_KEY_COMMAND);
            SC_RETURN_IF(!value.isValidObject<SCString>(),false);
            
            auto command = value.getString();
            SC_RETURN_IF(command!=_strCommand,false);
        }
        
        return _func(mi);
    }
}

