//



#ifndef __SPEEDCC__SCMESSAGEDISPATCH_H__
#define __SPEEDCC__SCMESSAGEDISPATCH_H__


#include "SCMessageDef.h"
#include "SCMessageDefaultProc.h"
#include "cocos2d.h"
#include <list>

namespace SpeedCC
{
    struct SCMessageListener
    {
        virtual ~SCMessageListener() {}
        virtual void onSCMessageProcess(SCMessageInfo& mi) {}
    };
    
    
    ///------------- SCMessageDispatch
    class SCMessageDispatch : public cocos2d::Ref
    {
    public:
        static SCMessageDispatch* getInstance();
        
        void addListener(SCMessageListener* pListener,const int nPriority=0);
        void removeListener(SCMessageListener* pListener);
        
        void sendMessage(SCMessageInfo& mi);
        void sendMessage(const int nMsgID);
        void postMessage(const SCMessageInfo& mi);
        void postMessage(const int nMsgID);
        
    protected:
        SCMessageDispatch();
        void onTimerMessagePump(float);
        
    private:
        int dispatchMessage(SCMessageInfo& mi);
        void updateMutableListener();
        
        inline std::list<SCMessageInfo>& getMsgQueRecive() {return _messageQueArray[_bMessageQueFlag?0:1];}
        inline std::list<SCMessageInfo>& getMsgQueDispatch() {return _messageQueArray[_bMessageQueFlag?1:0];}
        inline void swapMsgQue() {_bMessageQueFlag=!_bMessageQueFlag;}
        
        struct SMutabelListenerInfo
        {
            SCMessageListener*        pListener;
            bool                    bAdd;
            int                     nPriority;
            
            bool operator==(const SMutabelListenerInfo& info) const
            {
                return (info.pListener!=NULL && info.pListener==this->pListener)  ;
            }
            
            SMutabelListenerInfo():
            pListener(NULL),
            bAdd(true),
            nPriority(0)
            {}
        };
        
        struct SListenerInfo
        {
            int                 nPriority;
            SCMessageListener*    pListener;
            
            SListenerInfo():
            nPriority(0),
            pListener(NULL)
            {}
            
            inline bool operator<(const SListenerInfo& info) const { return nPriority<info.nPriority; }
            inline bool operator>(const SListenerInfo& info) const { return nPriority>info.nPriority; }
        };
    private:
        static SCMessageDispatch*                     _pInstance;
        
        std::list<SMutabelListenerInfo>             _mutableListenerList;
        std::list<SListenerInfo>                    _listenerList;
        std::list<SCMessageInfo>                   _messageQueArray[2];
        bool                                        _bMessageQueFlag;
        int                                         _nPostMsgCallStackCounter;
        int                                         _nSendMsgCallStackCounter;
        SCMessageDefaultProc                        _defaultProc;
    };
}


#endif // __SPEEDCC__SCMESSAGEDISPATCH_H__


