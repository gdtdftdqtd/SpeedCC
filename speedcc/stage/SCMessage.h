//

#ifndef __SPEEDCC__SCMESSAGEDEF_H__
#define __SPEEDCC__SCMESSAGEDEF_H__

#include "../base/SCDictionary.h"
#include "../base/SCObject.h"
#include "SCPerformIDDef.h"

namespace SpeedCC
{
    ///------------ SCMessage
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
        
        SCMessage(const SCString& strCmd):
        nMsgID(SCID::Msg::kSCMsgCommand),
        bContinue(true)
        {
            paramters.setValue(SC_KEY_COMMAND,strCmd);
        }
        
        SCMessage(const SCString& strCmd,const SCDictionary& par):
        nMsgID(SCID::Msg::kSCMsgCommand),
        bContinue(true)
        {
            paramters = par;
            paramters.setValue(SC_KEY_COMMAND,strCmd);
        }
        
    public:
        SC_AVOID_CLASS_COPY(SCMessage)
        SC_DEFINE_CLASS_PTR(SCMessage)
        
        SC_DEFINE_CREATE_FUNC_0(SCMessage)
        SC_DEFINE_CREATE_FUNC_1(SCMessage,const int)
        SC_DEFINE_CREATE_FUNC_2(SCMessage,const int,const SCDictionary&)
        SC_DEFINE_CREATE_FUNC_1(SCMessage,const SCString&)
        SC_DEFINE_CREATE_FUNC_2(SCMessage,const SCString&,const SCDictionary&)
        
        Ptr clone();
        
        int                 nMsgID;
        SCDictionary        paramters;
        bool                bContinue;
    };
    
    ///-------------- SCMessageGroup
    class SCMessageGroup : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCMessageGroup)
        SC_DEFINE_CLASS_PTR(SCMessageGroup)
        
        SC_DEFINE_CREATE_FUNC_1(SCMessageGroup,const int)
        SC_DEFINE_CREATE_FUNC_2(SCMessageGroup,const int,const SCDictionary&)
        SC_DEFINE_CREATE_FUNC_1(SCMessageGroup,const SCString&)
        SC_DEFINE_CREATE_FUNC_2(SCMessageGroup,const SCString&,const SCDictionary&)
        
        template<typename T1, typename T2, typename ...Ts>
        static Ptr create(T1 t1, T2 t2, Ts... ts)
        {
            auto ptrGroup1 = SCMessageGroup::create(t1);
            auto ptrGroup2 = SCMessageGroup::create(t2,ts...);
            return SCMessageGroup::create(ptrGroup1,ptrGroup2);
        }
        
        inline std::list<SCMessage::Ptr> getMessageList() const { return _msgList; }
        
    protected:
        SC_DEFINE_CREATE_FUNC_2(SCMessageGroup,Ptr,Ptr)
        
        SCMessageGroup(const int nMsgID);
        SCMessageGroup(const int nMsgID,const SCDictionary& dic);
        SCMessageGroup(const SCString& strCmd);
        SCMessageGroup(const SCString& strCmd,const SCDictionary& dic);
        SCMessageGroup(Ptr ptr1, Ptr ptr2);
        
    private:
        std::list<SCMessage::Ptr>       _msgList;
    };
    
    ///------------ SCMessageMatcher
    class SCMessageMatcher : public SCObject
    {
    public:
        using MatchFunc_t = std::function<bool (const SCMessage::Ptr ptrMsg)>;
        
    public:
        SC_AVOID_CLASS_COPY(SCMessageMatcher)
        SC_DEFINE_CLASS_PTR(SCMessageMatcher)
        
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcher,const int,const MatchFunc_t&)
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcher,const int,const SCDictionary&)
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcher,const SCString&,const MatchFunc_t&)
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcher,const SCString&,const SCDictionary&)
        
        bool isMatch(const SCMessage::Ptr ptrMsg) const;
        
        inline SCString getCommand() const { return _strCommand; }
        inline int getMessageID() const { return _nMsgID; }
        inline SCDictionary getParameter() const { return _paraDic; }
        inline MatchFunc_t getFunc() const { return _func; }
        inline bool isCommand() const { return (_nMsgID==SCID::Msg::kSCMsgCommand);}
        
    protected:
        SCMessageMatcher(const int nMsgID,const MatchFunc_t& func);
        SCMessageMatcher(const SCString& strCommand,const MatchFunc_t& func);
        SCMessageMatcher(const int nMsgID,const SCDictionary& dic);
        SCMessageMatcher(const SCString& strCommand,const SCDictionary& dic);
        
    private:
        SCString            _strCommand;
        int                 _nMsgID;
        SCDictionary        _paraDic;
        MatchFunc_t         _func;
    };

    ///-------------- SCMessageMatcherGroup
    class SCMessageMatcherGroup : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCMessageMatcherGroup)
        SC_DEFINE_CLASS_PTR(SCMessageMatcherGroup)
        
        SC_DEFINE_CREATE_FUNC_1(SCMessageMatcherGroup,const int)
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcherGroup,const int,const SCDictionary&)
        SC_DEFINE_CREATE_FUNC_1(SCMessageMatcherGroup,const SCString&)
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcherGroup,const SCString&,const SCDictionary&)
        SC_DEFINE_CREATE_FUNC_2(SCMessageMatcherGroup,Ptr,Ptr)
        SC_DEFINE_CREATE_FUNC_1(SCMessageMatcherGroup,SCMessageMatcher::Ptr)
        
        template<typename T1, typename T2, typename ...Ts>
        static Ptr create(T1 t1, T2 t2, Ts... ts)
        {
            auto ptrGroup1 = SCMessageMatcherGroup::create(t1);
            auto ptrGroup2 = SCMessageMatcherGroup::create(t2,ts...);
            return SCMessageMatcherGroup::create(ptrGroup1,ptrGroup2);
        }
        
        inline std::list<SCMessageMatcher::Ptr> getMsgMatcherList() const { return _msgMatcherList; }
        
    protected:
        SCMessageMatcherGroup(const int nMsgID);
        SCMessageMatcherGroup(const int nMsgID,const SCDictionary& dic);
        SCMessageMatcherGroup(const SCString& strCmd);
        SCMessageMatcherGroup(const SCString& strCmd,const SCDictionary& dic);
        SCMessageMatcherGroup(SCMessageMatcher::Ptr ptrMatcher);
        SCMessageMatcherGroup(Ptr ptr1, Ptr ptr2);
        
    private:
        std::list<SCMessageMatcher::Ptr>       _msgMatcherList;
    };
}

#endif // __SPEEDCC__SCMESSAGEDEF_H__