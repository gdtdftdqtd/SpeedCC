/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/



#ifndef __SPEEDCC__SCMESSAGEDISPATCH_H__
#define __SPEEDCC__SCMESSAGEDISPATCH_H__


#include "SCMessage.h"
#include "SCMessageDefaultProc.h"
#include "cocos2d.h"
#include <list>

namespace SpeedCC
{
    struct SCMessageListener
    {
        virtual ~SCMessageListener() {}
        virtual void onSCMessageProcess(SCMessage::Ptr ptrMsg) {}
    };
    
    
    ///------------- SCMessageDispatch
    class SCMessageDispatch : public cocos2d::Ref
    {
    public:
        enum EPriority
        {
            kPriorityHighest = 0,
            kPriorityDefault = 128,
            kPriorityLowest = 255,
        };
        
        static SCMessageDispatch* getInstance();
        
        void addListener(SCMessageListener* pListener,const unsigned char nPriority=kPriorityDefault);
        void removeListener(SCMessageListener* pListener);
        
        void sendMessage(SCMessage::Ptr ptrMsg);
        void sendMessage(const int nMsgID);
        void sendMessage(const int nMsgID,const SCDictionary& dic);
        void postMessage(SCMessage::Ptr ptrMsg);
        void postMessage(const int nMsgID);
        void postMessage(const int nMsgID,const SCDictionary& dic);
        
        inline void setFrameMessageEnabled(const bool bEnable) { _bFrameMessageEnabled = bEnable; }
        inline bool getFrameMessageEnabled() const { return _bFrameMessageEnabled; }
        
        SCMessageDefaultProc* getDefaultProc() { return &_defaultProc; }
        
    protected:
        SCMessageDispatch();
        void onFrameMessagePump(float);
        
    private:
        void updateMutableListener();
        
        inline std::list<SCMessage::Ptr>& getMsgQueRecive() {return _messageQueArray[_bMessageQueFlag?0:1];}
        inline std::list<SCMessage::Ptr>& getMsgQueDispatch() {return _messageQueArray[_bMessageQueFlag?1:0];}
        inline void swapMsgQue() {_bMessageQueFlag=!_bMessageQueFlag;}
        
        struct SListenerInfo
        {
            unsigned char                   byPriority; // 0: highest; 255: lowest
            SCMessageListener*              pListener;
            
            SListenerInfo():
            byPriority(0),
            pListener(nullptr)
            {}
            
            inline bool operator<(const SListenerInfo& info) const { return byPriority<info.byPriority; }
            inline bool operator>(const SListenerInfo& info) const { return byPriority>info.byPriority; }
        };
        
        struct SMutabelListenerInfo
        {
            bool                    bAdd;
            SListenerInfo           listener;
            
            bool operator==(const SMutabelListenerInfo& info) const
            {
                return (info.listener.pListener!=nullptr && info.listener.pListener==listener.pListener);
            }
            
            SMutabelListenerInfo():
            bAdd(true)
            {}
        };
        
        
    private:
        static SCMessageDispatch*                   _pInstance;
        
        bool                                        _bFrameMessageEnabled;
        std::list<SMutabelListenerInfo>             _mutableListenerList;
        std::list<SListenerInfo>                    _listenerList;
        std::list<SCMessage::Ptr>                   _messageQueArray[2];
        bool                                        _bMessageQueFlag;
        int                                         _nPostMsgCallStackCounter;
        int                                         _nSendMsgCallStackCounter;
        SCMessageDefaultProc                        _defaultProc;
    };
}


#endif // __SPEEDCC__SCMESSAGEDISPATCH_H__


