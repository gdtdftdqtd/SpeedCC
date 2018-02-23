/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
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

#include "SCEventEmitter.h"

namespace SpeedCC
{
    SCEventEmitter::SCEventEmitter():
    _pMsgListener(nullptr),
    _pReceiveNode(nullptr),
    _bActive(true)
    {}
    
    SCEventEmitter::SCEventEmitter(EEventType type,cocos2d::Node* pNode,SCMessageListener* pMsgListener):
    _pMsgListener(pMsgListener),
    _pReceiveNode(pNode),
    _eventType(type),
    _bActive(true)
    {
        
    }
    
    SCEventEmitter::~SCEventEmitter()
    {
        if(_pTouchListener!=nullptr)
        {
            SCCCDirector()->getEventDispatcher()->removeEventListener(_pTouchListener);
            _pTouchListener = nullptr;
        }
    }
    
    void SCEventEmitter::setEventType(EEventType type)
    {
        if(_pTouchListener!=nullptr)
        {
            SCCCDirector()->getEventDispatcher()->removeEventListener(_pTouchListener);
            _pTouchListener = nullptr;
        }
        
        switch(type)
        {
            case EEventType::kSingleTouch:
            {
                auto pListener = cocos2d::EventListenerTouchOneByOne::create();
                pListener->setSwallowTouches(true);
                pListener->onTouchBegan = SC_MAKE_FUNC(onSingleTouchBegan, this);
                pListener->onTouchMoved = SC_MAKE_FUNC(onSingleTouchMoved, this);
                pListener->onTouchEnded = SC_MAKE_FUNC(onSingleTouchEnded, this);
                pListener->onTouchCancelled = SC_MAKE_FUNC(onSingleTouchCancelled, this);
                
                _pTouchListener = pListener;
            }
                break;
                
            case EEventType::kMultipleTouch:
            {
                auto pListener = cocos2d::EventListenerTouchAllAtOnce::create();
                pListener->onTouchesBegan = SC_MAKE_FUNC(onMultipleTouchBegan, this);
                pListener->onTouchesMoved = SC_MAKE_FUNC(onMultipleTouchMoved, this);
                pListener->onTouchesEnded = SC_MAKE_FUNC(onMultipleTouchEnded, this);
                pListener->onTouchesCancelled = SC_MAKE_FUNC(onMultipleTouchCancelled, this);
                
                _pTouchListener = pListener;
            }
                break;
                
            case EEventType::kAcceleration:
            {
                auto pListener = cocos2d::EventListenerAcceleration::create(SC_MAKE_FUNC(onAcceleration, this));
                _pTouchListener = pListener;
            }
                break;
                
            case EEventType::kKeyboard:
            {
                auto pListener = cocos2d::EventListenerKeyboard::create();
                pListener->onKeyPressed = SC_MAKE_FUNC(onKeyboardPressed, this);
                pListener->onKeyReleased = SC_MAKE_FUNC(onKeyboardPressed, this);
                _pTouchListener = pListener;
            }
                break;
                
            default:
                SCASSERT(false);
                break;
        }
        
        if(_pTouchListener!=nullptr)
        {
            SCCCDirector()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pTouchListener, _pReceiveNode);
        }
    }
    
    // by default, it will consume touch
    bool SCEventEmitter::onSingleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        SC_RETURN_IF(!this->getActive(), true);
        
        SCDictionary::SPair pair[] =
        {
            {SC_KEY_TOUCH,pTouch},
            {SC_KEY_RESULT,true},
        };
        
        SCDictionary dic(pair,SC_ARRAY_LENGTH(pair));
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgTouchBegan;
        ptrMsg->parameters = dic;
        
        if(_pMsgListener==nullptr)
        {
            SCMsgDisp()->sendMessage(ptrMsg);
        }
        else
        {
            _pMsgListener->onSCMessageProcess(ptrMsg);
        }
        
        return ptrMsg->parameters.getValue(SC_KEY_RESULT).getBool();
    }
    
    void SCEventEmitter::onSingleTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        SC_RETURN_V_IF(!this->getActive());
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchMoved,pTouch,pEvent);
    }
    
    void SCEventEmitter::onSingleTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        SC_RETURN_V_IF(!this->getActive());
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchEnded,pTouch,pEvent);
    }
    
    void SCEventEmitter::onSingleTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        SC_RETURN_V_IF(!this->getActive());
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchCancelled,pTouch,pEvent);
    }
    
    void SCEventEmitter::onMultipleTouchBegan(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        SC_RETURN_V_IF(!this->getActive());
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchBegan,touchVtr,pEvent);
    }
    
    void SCEventEmitter::onMultipleTouchMoved(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        SC_RETURN_V_IF(!this->getActive());
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchMoved,touchVtr,pEvent);
    }
    
    void SCEventEmitter::onMultipleTouchEnded(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        SC_RETURN_V_IF(!this->getActive());
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchEnded,touchVtr,pEvent);
    }
    
    void SCEventEmitter::onMultipleTouchCancelled(const std::vector<cocos2d::Touch*>& touchVtr,
                                                  cocos2d::Event* pEvent)
    {
        SC_RETURN_V_IF(!this->getActive());
        this->sendTouchMessage(SCID::Msg::kSCMsgTouchCancelled,touchVtr,pEvent);
    }
    
    void SCEventEmitter::onAcceleration(cocos2d::Acceleration* pAcc, cocos2d::Event* pEvent)
    {
        SC_RETURN_V_IF(!this->getActive());
        SCDictionary::SPair pairArray[] =
        {
            {SC_KEY_X,pAcc->x},
            {SC_KEY_Y,pAcc->y},
            {SC_KEY_Z,pAcc->z},
            {SC_KEY_TIMESTAMP,pAcc->timestamp},
            {SC_KEY_CCEVENT,pEvent}
        };
        
        SCDictionary dic(pairArray,SC_ARRAY_LENGTH(pairArray));
        
        this->sendEventMessage(SCID::Msg::kSCMsgAcceleration,dic);
    }
    
    void SCEventEmitter::onKeyboardPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* pEvent)
    {
        SC_RETURN_V_IF(!this->getActive());
        SCDictionary::SPair pairArray[] =
        {
            {SC_KEY_KEYBOARDCODE,code},
            {SC_KEY_CCEVENT,pEvent}
        };
        
        SCDictionary dic(pairArray,SC_ARRAY_LENGTH(pairArray));
        
        this->sendEventMessage(SCID::Msg::kSCMsgKeyboardKeyDown,dic);
    }
    
    void SCEventEmitter::sendEventMessage(const int nMsg,SCDictionary dic)
    {
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = nMsg;
        ptrMsg->parameters = dic;
        
        if(_pMsgListener==nullptr)
        {
            SCMsgDisp()->sendMessage(ptrMsg);
        }
        else
        {
            _pMsgListener->onSCMessageProcess(ptrMsg);
        }
    }
}
