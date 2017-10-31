//



#ifndef __SPEEDCC__SCMESSAGEDISPATCH_H__
#define __SPEEDCC__SCMESSAGEDISPATCH_H__


#include "SCMessageDef.h"
#include "cocos2d.h"
#include <list>

namespace SpeedCC
{
    struct SCMessageListener
    {
        virtual ~SCMessageListener() {}
        virtual void onSCMessageProcess(SSCMessageInfo& mi) {}
    };
    
    
    ///------------- SCMessageDispatch
    class SCMessageDispatch : public cocos2d::Ref
    {
    public:
        static SCMessageDispatch* getInstance();
        
        void addListener(SCMessageListener* pListener,const int nPriority=0);
        void removeListener(SCMessageListener* pListener);
        
        void sendMessage(SSCMessageInfo mi);
        void postMessage(const SSCMessageInfo& mi);
        
    protected:
        SCMessageDispatch();
        void onTimerMessagePump(float);
        
    private:
        int dispatchMessage(SSCMessageInfo& mi);
        void updateMutableListener();
        
        inline std::list<SSCMessageInfo>& getMsgQueRecive() {return _messageQueArray[_bMessageQueFlag?0:1];}
        inline std::list<SSCMessageInfo>& getMsgQueDispatch() {return _messageQueArray[_bMessageQueFlag?1:0];}
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
        std::list<SSCMessageInfo>                   _messageQueArray[2];
        bool                                        _bMessageQueFlag;
        int                                         _nPostMsgCallStackCounter;
        int                                         _nSendMsgCallStackCounter;
    };
}


#endif // __SPEEDCC__SCMESSAGEDISPATCH_H__


