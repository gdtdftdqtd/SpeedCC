//

#include "SCMessageDispatch.h"
#include "../base/SCTemplateDef.h"
#include "../cocos/SCCocosDef.h"

using namespace std;

namespace SpeedCC
{
    ///----------- SCMessageListener
    
    SCMessageDispatch* SCMessageDispatch::_pInstance = NULL;
    
    SCMessageDispatch* SCMessageDispatch::getInstance()
    {
        if(_pInstance==NULL)
        {
            _pInstance = new SCMessageDispatch();
            SCSchedule(SC_FUNC(SCMessageDispatch::onFrameMessagePump),_pInstance,0,false);
        }
        
        return _pInstance;
    }
    
    SCMessageDispatch::SCMessageDispatch():
    _nPostMsgCallStackCounter(0),
    _nSendMsgCallStackCounter(0),
    _bMessageQueFlag(true),
    _bFrameMessageEnabled(false)
    {
    }
    
    void SCMessageDispatch::addListener(SCMessageListener* pListener,const unsigned char nPriority)
    {
        SCASSERT(pListener!=NULL);
        
        SMutabelListenerInfo info;
        
        info.bAdd = true;
        info.listener.pListener = pListener;
        info.listener.byPriority = nPriority;
        
        auto it = std::find(_mutableListenerList.begin(),_mutableListenerList.end(),info);
        
        if(it!=_mutableListenerList.end())
        {
            _mutableListenerList.erase(it);
        }
        
        _mutableListenerList.push_back(info);
        
        // if no message dispatch in call stack, then updating mutable listener immediately
        if(_nPostMsgCallStackCounter==0 && _nSendMsgCallStackCounter==0)
        {
            this->updateMutableListener();
        }
    }
    
    void SCMessageDispatch::removeListener(SCMessageListener* pListener)
    {
        SCASSERT(pListener!=NULL);
        
        SMutabelListenerInfo info;
        
        info.bAdd = false;
        info.listener.pListener = pListener;
        
        auto it = std::find(_mutableListenerList.begin(),_mutableListenerList.end(),info);
        
        if(it!=_mutableListenerList.end())
        {
            _mutableListenerList.erase(it);
        }
        
        _mutableListenerList.push_back(info);
        
        if(_nPostMsgCallStackCounter==0 && _nSendMsgCallStackCounter==0)
        {
            this->updateMutableListener();
        }
    }
    
    void SCMessageDispatch::sendMessage(SCMessage::Ptr ptrMsg)
    {
        if(_nPostMsgCallStackCounter==0 && _nSendMsgCallStackCounter==0)
        {
            this->updateMutableListener();
        }
        
        ++_nSendMsgCallStackCounter;
        
        auto it = _listenerList.begin();
        for(;it!=_listenerList.end() && ptrMsg->bContinue;++it)
        {
            SCASSERT((*it).pListener!=NULL);
            
            if((*it).pListener!=NULL)
            {
                (*it).pListener->onSCMessageProcess(ptrMsg);
            }
            
            _defaultProc.processMessage(ptrMsg);
        }
        
        --_nSendMsgCallStackCounter;
    }
    
    void SCMessageDispatch::sendMessage(const int nMsgID)
    {
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = nMsgID;
        this->sendMessage(ptrMsg);
    }
    
    void SCMessageDispatch::sendMessage(const int nMsgID,const SCDictionary& dic)
    {
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = nMsgID;
        ptrMsg->paramters = dic;
        this->sendMessage(ptrMsg);
    }
    
    void SCMessageDispatch::postMessage(SCMessage::Ptr ptrMsg)
    {
        this->getMsgQueRecive().push_back(ptrMsg);
    }
    
    void SCMessageDispatch::postMessage(const int nMsgID)
    {
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = nMsgID;
        this->postMessage(ptrMsg);
    }
    
    void SCMessageDispatch::postMessage(const int nMsgID,const SCDictionary& dic)
    {
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = nMsgID;
        ptrMsg->paramters = dic;
        this->postMessage(ptrMsg);
    }
    
    void SCMessageDispatch::updateMutableListener()
    {
        SCASSERT(_nSendMsgCallStackCounter==0);
        SCASSERT(_nPostMsgCallStackCounter==0);
        
        SC_RETURN_IF_V(_mutableListenerList.empty());
        
        std::for_each(_mutableListenerList.begin(),_mutableListenerList.end(),
                      [this](const SMutabelListenerInfo& info)-> void
                      {
                          SC_RETURN_IF_V(info.listener.pListener==NULL);
                          
                          if(info.bAdd)
                          {// add listener
                              auto it1 = std::remove_if(_listenerList.begin(),_listenerList.end(),
                                                        [&info](const SListenerInfo& it) -> bool
                                                        {
                                                            return (it.pListener==info.listener.pListener);
                                                        });
                              
                              _listenerList.erase(it1,_listenerList.end());
                              
                              SListenerInfo listenerInfo = info.listener;
                              _listenerList.push_back(listenerInfo);
                          }
                          else
                          {// remove listener
                              _listenerList.remove_if([&info](const SListenerInfo& it) -> bool
                                                      {
                                                          return (it.pListener==info.listener.pListener);
                                                      });
                          }
                      });
        
        _listenerList.sort(std::greater<SListenerInfo>());
        _mutableListenerList.clear();
    }
    
    
    void SCMessageDispatch::onFrameMessagePump(float fDelta)
    {
        std::list<SCMessage::Ptr>& workingQue = this->getMsgQueRecive();
        this->swapMsgQue();
        
        // update mutable listener first before message loop
        this->updateMutableListener();
        
        ++_nPostMsgCallStackCounter;
        
        // send frame message
        if(_bFrameMessageEnabled)
        {
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = SCID::Msg::kSCMsgFrame;
            ptrMsg->paramters.setValue(MSG_KEY_DELTA, SCValue(fDelta));
            SCMsgDisp()->sendMessage(ptrMsg);
        }
        
        while(!workingQue.empty())
        {
            auto& msg = workingQue.front();
            
            auto it = _listenerList.begin();
            for(;it!=_listenerList.end() && msg->bContinue;++it)
            {
                SCASSERT((*it).pListener!=NULL);
                if((*it).pListener!=NULL)
                {
                    (*it).pListener->onSCMessageProcess(msg);
                }
            }
         
            _defaultProc.processMessage(msg);
            workingQue.pop_front();
        }
        
        --_nPostMsgCallStackCounter;
        
        workingQue.clear();
    }
}





