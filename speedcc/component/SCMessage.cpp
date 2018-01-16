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
    
    ///----------------- SCMessageGroup
    SCMessageGroup::SCMessageGroup(const int nMsgID)
    {
        auto ptrMsg = SCMessage::create(nMsgID);
        _msgList.push_back(ptrMsg);
    }
    
    SCMessageGroup::SCMessageGroup(const SCString& strCmd)
    {
        auto ptrMsg = SCMessage::create(strCmd);
        _msgList.push_back(ptrMsg);
    }
    
    SCMessageGroup::SCMessageGroup(const int nMsgID,const SCDictionary& dic)
    {
        auto ptrMsg = SCMessage::create(nMsgID,dic);
        _msgList.push_back(ptrMsg);
    }
    
    SCMessageGroup::SCMessageGroup(const SCString& strCmd,const SCDictionary& dic)
    {
        auto ptrMsg = SCMessage::create(strCmd,dic);
        _msgList.push_back(ptrMsg);
    }
    
    SCMessageGroup::SCMessageGroup(SCMessageGroup::Ptr ptr1, SCMessageGroup::Ptr ptr2)
    {
        SCASSERT(ptr1!=NULL);
        SCASSERT(ptr2!=NULL);
        
        auto list1 = ptr1->getMessageList();
        auto list2 = ptr2->getMessageList();
        
        _msgList.assign(list1.begin(), list1.end());
        _msgList.insert(_msgList.end(), list2.begin(),list2.end());
    }
    
}

