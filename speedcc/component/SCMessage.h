//

#ifndef __SPEEDCC__SCMESSAGEDEF_H__
#define __SPEEDCC__SCMESSAGEDEF_H__

#include "../base/SCDictionary.h"
#include "../base/SCObject.h"
#include "SCPerformIDDef.h"

namespace SpeedCC
{
    struct SCMessage : public SCObject
    {
    protected:
        SCMessage():
        nMsgID(SCID::Msg::kSCMsgNULL),
        bContinue(true)
        {}
        
        SCMessage(const int nMsgID1):
        nMsgID(nMsgID1),
        bContinue(true)
        {}
        
        SCMessage(const int nMsgID1,const SCDictionary& par):
        nMsgID(nMsgID1),
        paramters(par),
        bContinue(true)
        {}
        
    public:
        SC_AVOID_CLASS_COPY(SCMessage)
        SC_DEFINE_CLASS_PTR(SCMessage)
        
        SC_DEFINE_CREATE_FUNC_0(SCMessage)
        SC_DEFINE_CREATE_FUNC_1(SCMessage,const int)
        SC_DEFINE_CREATE_FUNC_2(SCMessage,const int,const SCDictionary&)
        
        int                 nMsgID;
        SCDictionary        paramters;
        bool                bContinue;
    };
    
    class SCMessageMatcher : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCMessageMatcher)
        SC_DEFINE_CLASS_PTR(SCMessageMatcher)
        
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcher,const int,const std::function<bool (const SCMessage::Ptr ptrMsg)>&)
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcher,const SCString&,const std::function<bool (const SCMessage::Ptr ptrMsg)>&)
        
        bool isMatch(const SCMessage::Ptr ptrMsg) const;
        
        inline SCString getCommand() const { return _strCommand; }
        inline int getMessageID() const { return _nMsgID; }
        
    protected:
        SCMessageMatcher(const int nMsgID,const std::function<bool (SCMessage::Ptr ptrMsg)>& func);
        SCMessageMatcher(const SCString& strCommand,const std::function<bool (SCMessage::Ptr ptrMsg)>& func);
        
    private:
        SCString                                        _strCommand;
        int                                             _nMsgID;
        std::function<bool (SCMessage::Ptr ptrMsg)>         _func;
    };

}

#endif // __SPEEDCC__SCMESSAGEDEF_H__
