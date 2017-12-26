//

#include "SCMessageDispatch.h"
#include "../base/SCTemplateDef.h"

using namespace std ;

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
        
        return _pInstance ;
    }
    
    SCMessageDispatch::SCMessageDispatch():
    _nPostMsgCallStackCounter(0),
    _nSendMsgCallStackCounter(0),
    _bMessageQueFlag(true)
    {
    }
    
    void SCMessageDispatch::addListener(SCMessageListener* pListener,const int nPriority)
    {
        SCASSERT(pListener!=NULL) ;
        
        SMutabelListenerInfo info ;
        
        info.bAdd = true;
        info.pListener = pListener;
        info.nPriority = nPriority;
        
        auto it = std::find(_mutableListenerList.begin(),_mutableListenerList.end(),info) ;
        
        if(it!=_mutableListenerList.end())
        {
            _mutableListenerList.erase(it);
        }
        
        _mutableListenerList.push_back(info) ;
        
        if(_nPostMsgCallStackCounter==0 && _nSendMsgCallStackCounter==0)
        {
            this->updateMutableListener();
        }
    }
    
    void SCMessageDispatch::removeListener(SCMessageListener* pListener)
    {
        SCASSERT(pListener!=NULL) ;
        
        SMutabelListenerInfo info ;
        
        info.bAdd = false ;
        info.pListener = pListener ;
        
        auto it = std::find(_mutableListenerList.begin(),_mutableListenerList.end(),info) ;
        
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
    
    void SCMessageDispatch::sendMessage(SSCMessageInfo mi)
    {
        if(_nPostMsgCallStackCounter==0 && _nSendMsgCallStackCounter==0)
        {
            this->updateMutableListener();
        }
        
        ++_nSendMsgCallStackCounter;
        
        auto it = _listenerList.begin();
        for(;it!=_listenerList.end() && mi.bContinue;++it)
        {
            SCASSERT((*it).pListener!=NULL);
            
            if((*it).pListener!=NULL)
            {
                (*it).pListener->onSCMessageProcess(mi);
            }
            
            _defaultProc.processMessage(mi);
        }
        
        --_nSendMsgCallStackCounter;
    }
    
    void SCMessageDispatch::sendMessage(const int nMsgID)
    {
        SSCMessageInfo mi;
        mi.nMsgID = nMsgID;
        this->sendMessage(mi);
    }
    
    void SCMessageDispatch::postMessage(const SSCMessageInfo& mi)
    {
        this->getMsgQueRecive().push_back(mi);
    }
    
    void SCMessageDispatch::postMessage(const int nMsgID)
    {
        SSCMessageInfo mi;
        mi.nMsgID = nMsgID;
        this->postMessage(mi);
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
                          }) ;
            
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
        
        _mutableListenerList.clear() ;
    }
    
    
    void SCMessageDispatch::onTimerMessagePump(float fDelta)
    {
        stl_list<SSCMessageInfo>& workingQue = this->getMsgQueRecive();
        this->swapMsgQue();
        
        // update mutable listener first before message loop
        this->updateMutableListener() ;
        
        ++_nPostMsgCallStackCounter;
        
        while(!workingQue.empty())
        {
            auto& msg = workingQue.front() ;
            
            auto it = _listenerList.begin();
            for(;it!=_listenerList.end() && msg.bContinue;++it)
            {
                SCASSERT((*it).pListener!=NULL);
                if((*it).pListener!=NULL)
                {
                    (*it).pListener->onSCMessageProcess(msg) ;
                }
            }
         
            _defaultProc.processMessage(msg);
            workingQue.pop_front() ;
        }
        
        --_nPostMsgCallStackCounter;
        
        workingQue.clear();
    }
}





