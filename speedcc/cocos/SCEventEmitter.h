//
//  SCEventEmitter.hpp
//  libspeedcc
//
//  Created by Kevin on 9/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCEVENTEMITTER_H__
#define __SPEEDCC__SCEVENTEMITTER_H__

#include "cocos2d.h"
#include "../base/SCObject.h"
#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacroDef.h"
#include "SCCocosDef.h"

namespace SpeedCC
{
    class SCEventEmitter : public SCObject
    {
    public:
        enum class ETouchMode
        {
            kNone,
            kSingle,
            kMultiple,
        };
        
    public:
        SC_AVOID_CLASS_COPY(SCEventEmitter)
        SC_DEFINE_CLASS_PTR(SCEventEmitter)
        
        virtual ~SCEventEmitter();
        SC_DEFINE_CREATE_FUNC_2(SCEventEmitter,cocos2d::Node*,SCMessageListener*)
        
        inline void setActive(const bool bActive) {_bActive = bActive;}
        inline bool getActive() const {return _bActive;}
        
        cocos2d::EventListener* getEventListener(cocos2d::EventListener::Type type) const;
        void setTouchMode(const ETouchMode touch);
        inline ETouchMode getTouchMode() const { return _touchMode;}
        
        inline cocos2d::EventListener* getEventListener() const { return _pTouchListener; }
        
    protected:
        SCEventEmitter();
        SCEventEmitter(cocos2d::Node* pNode,SCMessageListener* pMsgListener);
        
    private:
        bool onSingleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        void onSingleTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        void onSingleTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        void onSingleTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        
        void onMultipleTouchBegan(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        void onMultipleTouchMoved(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        void onMultipleTouchEnded(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        void onMultipleTouchCancelled(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        
        void onAcceleration(cocos2d::Acceleration* pAcc, cocos2d::Event* pEvent);

        template<typename T>
        void sendTouchMessage(const int nMsg, T touch)
        {
            SCDictionary::SPair pair = {std::is_same<T,cocos2d::Touch*>::value ? SC_KEY_TOUCH : SC_KEY_TOUCHES,touch};
            
            SCDictionary dic(pair);
            
            SCMessage::Ptr ptrMsg = SCMessage::create();
            ptrMsg->nMsgID = nMsg;
            ptrMsg->parameters = dic;
            
            if(_pMsgListener==NULL)
            {
                SCMsgDisp()->sendMessage(ptrMsg);
            }
            else
            {
                _pMsgListener->onSCMessageProcess(ptrMsg);
            }
        }
        
    private:
        bool                                    _bActive;
        SCMessageListener*                      _pMsgListener;
        cocos2d::Node*                          _pReceiveNode;
        ETouchMode                              _touchMode;
        cocos2d::EventListener*                 _pTouchListener; // no need to remove from event dispatch
    };
}

#endif // __SPEEDCC__SCEVENTEMITTER_H__
