//
//  SCEventEmitter.cpp
//  libspeedcc
//
//  Created by Kevin on 9/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCEventEmitter.h"

namespace SpeedCC
{
    cocos2d::EventListener* SCEventEmitter::getEventListener(cocos2d::EventListener::Type type) const
    {
        SC_RETURN_IF((type!=cocos2d::EventListener::Type::TOUCH_ONE_BY_ONE && type!=cocos2d::EventListener::Type::TOUCH_ALL_AT_ONCE),NULL);
        
        if(type==cocos2d::EventListener::Type::TOUCH_ONE_BY_ONE)
        {
            return dynamic_cast<cocos2d::EventListenerTouchOneByOne*>(_pTouchListener);
        }
        else
        {
            return dynamic_cast<cocos2d::EventListenerTouchAllAtOnce*>(_pTouchListener);
        }
    }
    
    void SCEventEmitter::setTouchMode(const ETouchMode touch)
    {
        SC_RETURN_IF_V(touch==_touchMode);
        
        if(_pTouchListener!=NULL)
        {
            SCCCDirector()->getEventDispatcher()->removeEventListener(_pTouchListener);
            _pTouchListener = NULL;
        }
        
        switch(touch)
        {
            case ETouchMode::kSingle:
            {
                auto pListener = cocos2d::EventListenerTouchOneByOne::create();
                pListener->setSwallowTouches(true);
                pListener->onTouchBegan = SC_MAKE_FUNC(onSingleTouchBegan, this);
                pListener->onTouchMoved = SC_MAKE_FUNC(onSingleTouchMoved, this);
                pListener->onTouchEnded = SC_MAKE_FUNC(onSingleTouchEnded, this);
                pListener->onTouchCancelled = SC_MAKE_FUNC(onSingleTouchCancelled, this);
                
                _pTouchListener = pListener;
                SCCCDirector()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pTouchListener, _pReceiveNode);
            }
                break;
                
            case ETouchMode::kMultiple:
            {
                auto pListener = cocos2d::EventListenerTouchAllAtOnce::create();
                pListener->onTouchesBegan = SC_MAKE_FUNC(onMultipleTouchBegan, this);
                pListener->onTouchesMoved = SC_MAKE_FUNC(onMultipleTouchMoved, this);
                pListener->onTouchesEnded = SC_MAKE_FUNC(onMultipleTouchEnded, this);
                pListener->onTouchesCancelled = SC_MAKE_FUNC(onMultipleTouchCancelled, this);
                
                _pTouchListener = pListener;
                SCCCDirector()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pTouchListener, _pReceiveNode);
            }
                break;
                
            case ETouchMode::kNone: break;
        }
    }
    
    
    bool SCEventEmitter::onSingleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        SCDictionary::SPair pair[] =
        {
            {MSG_KEY_TOUCH,pTouch},
            {"result",true},
        };
        
        SCDictionary dic(pair,SC_ARRAY_LENGTH(pair));
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgTouchBegan;
        ptrMsg->paramters = dic;
        
        if(_pMsgListener==NULL)
        {
            SCMsgDisp()->sendMessage(ptrMsg);
        }
        else
        {
            _pMsgListener->onSCMessageProcess(ptrMsg);
        }
        
        return ptrMsg->paramters.getValue("result").getBool();
    }
    
    void SCEventEmitter::onSingleTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchMoved,pTouch);
    }
    
    void SCEventEmitter::onSingleTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchEnded,pTouch);
    }
    
    void SCEventEmitter::onSingleTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchCancelled,pTouch);
    }
    
    void SCEventEmitter::onMultipleTouchBegan(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchBegan,touchVtr);
    }
    
    void SCEventEmitter::onMultipleTouchMoved(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchMoved,touchVtr);
    }
    
    void SCEventEmitter::onMultipleTouchEnded(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchEnded,touchVtr);
    }
    
    void SCEventEmitter::onMultipleTouchCancelled(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchCancelled,touchVtr);
    }
    
}
