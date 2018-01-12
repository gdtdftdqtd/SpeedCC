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
            SCSchedule(SC_FUNC(SCMessageDispatch::onTimerMessagePump),_pInstance,0,false);
        }
        
        return _pInstance;
    }
    
    SCMessageDispatch::SCMessageDispatch():
    _nPostMsgCallStackCounter(0),
    _nSendMsgCallStackCounter(0),
    _bMessageQueFlag(true)
    {
    }
    
    void SCMessageDispatch::addListener(SCMessageListener* pListener,const unsigned char nPriority)
    {
        SCASSERT(pListener!=NULL);
        
        SMutabelListenerInfo info;
        
        info.bAdd = true;
        info.pListener = pListener;
        info.byPriority = nPriority;
        
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
    
    void SCMessageDispatch::removeListener(SCMessageListener* pListener)
    {
        SCASSERT(pListener!=NULL);
        
        SMutabelListenerInfo info;
        
        info.bAdd = false;
        info.pListener = pListener;
        
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
        
        if(!_mutableListenerList.empty())
        {
            // add listener first
            std::for_each(_mutableListenerList.begin(),_mutableListenerList.end(),
                          [this](const SMutabelListenerInfo& info)-> void
                          {
                              if(info.bAdd)
                              {
                                  auto it1 = std::remove_if(_listenerList.begin(),_listenerList.end(),
                                                            [&info](const SListenerInfo& it) -> bool
                                                            {
                                                                return (info.pListener!=NULL && it.pListener==info.pListener);
                                                            });
                                  
                                  _listenerList.erase(it1,_listenerList.end());
                                  
                                  SListenerInfo listenerInfo;
                                  listenerInfo.pListener = info.pListener;
                                  
                                  _listenerList.push_back(listenerInfo);
                              }
                          });
            
            // remove listener
            std::for_each(_mutableListenerList.begin(),_mutableListenerList.end(),
                          [this](const SMutabelListenerInfo& info) -> void
                          {
                              if(!info.bAdd)
                              {
                                  auto it1 = std::remove_if(_listenerList.begin(),_listenerList.end(),
                                                            [&info](const SListenerInfo& it) -> bool
                                                            {
                                                                return (info.pListener!=NULL && it.pListener==info.pListener);
                                                            });
                                  
                                  _listenerList.erase(it1,_listenerList.end());
                              }
                              
                          });
            
            _listenerList.sort(std::greater<SListenerInfo>());
        }
        
        _mutableListenerList.clear();
    }
    
    
    void SCMessageDispatch::onTimerMessagePump(float fDelta)
    {
        std::list<SCMessage::Ptr>& workingQue = this->getMsgQueRecive();
        this->swapMsgQue();
        
        // update mutable listener first before message loop
        this->updateMutableListener();
        
        ++_nPostMsgCallStackCounter;
        
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





