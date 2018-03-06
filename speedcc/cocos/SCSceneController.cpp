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


#include "cocos2d.h"

#include "SCSceneController.h"
#include "SCSceneNavigator.h"
#include "../base/SCTemplateUtils.h"
#include "../stage/SCStageMacros.h"
#include "../stage/SCBehaviorCocos.h"

namespace SpeedCC
{
    ////-------------- member methods
    SCSceneController::SCSceneController():
    _pBedNode(nullptr),
    _pScene(nullptr),
    _pDisableTouchLayer(nullptr),
    _pBlackMaskLayer(nullptr),
    _bBlackMaskForModal(true)
    {
    }
    
    SCSceneController::~SCSceneController()
    {
        SCCCScheduler()->unscheduleAllForTarget(static_cast<cocos2d::Ref*>(this));
    }
    
    void SCSceneController::onCreate(SCDictionary parameters)
    {
        bool bResult = false;
        auto finishFunc = parameters.getValue(SC_KEY_FINISHFUNC).getObject<FinishFunc_t>(&bResult);
        
        if(bResult && finishFunc!=nullptr)
        {
            _finishFunc = finishFunc;
        }
    }
    
    void SCSceneController::setBedNode(SCBedNode* pLayer)
    {
        _pBedNode = pLayer;
    }
    
    void SCSceneController::ownLifecycle(cocos2d::Ref* pObject)
    {
        SC_RETURN_V_IF(pObject==nullptr);
        
        auto ptr = SCRef2Ptr::create(pObject);
        this->ownLifecycle(ptr);
    }
    
    void SCSceneController::pushModalController(SCSceneController::Ptr ptrController)
    {
        ptrController->setModalParentController(this);
        ptrController->setScene(_pScene);
        
        if(_bBlackMaskForModal)
        {
            this->showBlackMask(true);
        }
        
        _pScene->addChild(ptrController->getBedNode());
        this->setAllTouchEnabled(false);
        
        // generate modal mssage
        SCMessage::Ptr ptrMsg = SCMessage::create();
        
        ptrMsg->nMsgID = SCID::Msg::kMsgModalSceneLostFocus;
        ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,this);
        SCMessageDispatch::getInstance()->postMessage(ptrMsg);
        
        ptrMsg->nMsgID = SCID::Msg::kMsgModalSceneGotFocus;
        ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,ptrController.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(ptrMsg);
    }
    
    SCSceneController::Ptr SCSceneController::popModalFromParent()
    {
        SCASSERT(_pParentModalController!=nullptr);
        auto ret = _pParentModalController->makeObjPtr<SCSceneController::Ptr>();
        
        _pParentModalController->setAllTouchEnabled(true);
        if(_pParentModalController->isBlackMaskForModal())
        {
            _pParentModalController->showBlackMask(false);
        }
        
        _pParentModalController = nullptr;
        _pBedNode->removeFromParent();
        
        // generate modal mssage
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kMsgModalSceneGotFocus;
        ptrMsg->parameters.setValue(SC_KEY_CONTROLLER,ret.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(ptrMsg);
        
        return ret;
    }
    
    void SCSceneController::setAllTouchEnabled(const bool bEnable)
    {
        if(_pDisableTouchLayer==nullptr && !bEnable)
        {// turn to no touch
            auto pLayer = SCLayerDisableTouch::create();
            _pBedNode->addChild(pLayer);
            pLayer->setPosition(cocos2d::Vec2(0,0));
            
            _pDisableTouchLayer = pLayer;
        }
        else if(_pDisableTouchLayer!=nullptr && bEnable)
        {// turn to touchable
            _pDisableTouchLayer->removeFromParentAndCleanup(true);
            _pDisableTouchLayer = nullptr;
        }
    }
    
    
    void SCSceneController::showBlackMask(const bool bShow)
    {
        if(bShow)
        {
            if(_pBlackMaskLayer==nullptr)
            {
                _pBlackMaskLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 200));
                _pBedNode->addChild(_pBlackMaskLayer);
            }
        }
        else
        {
            if(_pBlackMaskLayer!=nullptr)
            {
                _pBlackMaskLayer->removeFromParentAndCleanup(true);
                _pBlackMaskLayer = nullptr;
            }
        }
    }
    
    void SCSceneController::schedule(cocos2d::SEL_SCHEDULE selector)
    {
        this->schedule(selector, 0.0f, CC_REPEAT_FOREVER, 0.0f);
    }
    
    void SCSceneController::schedule(cocos2d::SEL_SCHEDULE selector, float interval)
    {
        this->schedule(selector, interval, CC_REPEAT_FOREVER, 0.0f);
    }
    
    void SCSceneController::schedule(cocos2d::SEL_SCHEDULE selector, float interval, unsigned int repeat, float delay)
    {
        SCCCScheduler()->schedule(selector, this, interval , repeat, delay, !_pBedNode->isRunning());
    }
    
    void SCSceneController::scheduleOnce(cocos2d::SEL_SCHEDULE selector, float delay)
    {
        this->schedule(selector, 0.0f, 0, delay);
    }
    
    void SCSceneController::unschedule(cocos2d::SEL_SCHEDULE selector)
    {
        SCCCScheduler()->unschedule(selector, this);
    }
    
    void SCSceneController::finish(void* pResult)
    {
        if(_finishFunc!=nullptr)
        {
            _finishFunc(pResult);
        }
    }
    
    void SCSceneController::delayExecute(float fDelay,const std::function<void ()>& fun)
    {
        fDelay = (fDelay<0) ? 0 : fDelay;
        
        auto pSeqAction = ASequence(ADelayTime(fDelay),
                                    ACallFunc(fun),
                                    nullptr);
        
        this->getBedNode()->runAction(pSeqAction);
    }
    
    void SCSceneController::delayExecute(float fDelay,const std::function<void(SCDictionary dic)>& func,SCDictionary dic)
    {
        this->delayExecute(fDelay,[func,dic]()
                           {
                               func(dic);
                           });
    }
    
    void SCSceneController::setBackButtonSceneEnabled(const bool bEnabled)
    {
        if(bEnabled)
        {
            const auto call = [](SCMessage::Ptr ptrMsg)
            {
                SC_RETURN_V_IF(ptrMsg->nMsgID!=SCID::Msg::kMsgKeyboardKeyDown);
                
                auto value = ptrMsg->parameters.getValue(SC_KEY_KEYBOARDCODE);
                auto code = value.getObject<cocos2d::EventKeyboard::KeyCode>();
                SC_RETURN_V_IF(code!=cocos2d::EventKeyboard::KeyCode::KEY_BACK);
                SCBehaviorSceneBack::create()->execute();
            };
            
            _ptrKeyboardEventEmtr = SCEventEmitter::create(SCEventEmitter::EEventType::kKeyboard,
                                                           _pBedNode,
                                                           call);
        }
        else
        {
            _ptrKeyboardEventEmtr = nullptr;
        }
    }
    
    void SCSceneController::listenMessage(const int nMsg,MsgFunc_t func)
    {
        SC_RETURN_V_IF(nMsg<=0);
        
        if(func==nullptr)
        {// remove mapping
            _msg2FuncMap.erase(nMsg);
        }
        else
        {
            _msg2FuncMap[nMsg] = func;
        }
    }
    
    void SCSceneController::onSCMessageProcess(SCMessage::Ptr ptrMsg)
    {
        SCASSERT(ptrMsg!=nullptr);
        
        auto it = _msg2FuncMap.find(ptrMsg->nMsgID);
        
        if(it!=_msg2FuncMap.end() && (*it).second!=nullptr)
        {
            (*it).second(ptrMsg);
            SC_RETURN_V_IF(!ptrMsg->bContinue);
        }
        
        SCStage::onSCMessageProcess(ptrMsg);
    }
    
}

