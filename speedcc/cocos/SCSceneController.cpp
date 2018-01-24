

#include "cocos2d.h"

#include "SCSceneController.h"
#include "../base/SCTemplateUtils.h"
#include "../component/SCComponentMacroDef.h"

namespace SpeedCC
{
    ////-------------- member methods
    SCSceneController::SCSceneController():
    _pBedNode(NULL),
    _pScene(NULL),
    _pDisableTouchLayer(NULL),
    _pBlackMaskLayer(NULL),
    _bBlackMaskForModal(true)
    {
    }
    
    SCSceneController::~SCSceneController()
    {
    }
    
    void SCSceneController::setBedNode(SCBedNode* pLayer)
    {
        _pBedNode = pLayer;
        _ptrUI = SCUIBuilder::create(_pBedNode,this);
    }
    
    void SCSceneController::ownLifecycle(cocos2d::Ref* pObject)
    {
        SC_RETURN_V_IF(pObject==NULL);
        
        auto ptr = SCRefHolder::create(pObject);
        this->ownLifecycle(ptr);
    }
    
    void SCSceneController::pushModalController(SCSceneController::Ptr ptrController)
    {
        SCSceneController::WeakPtr controllerPtr2 = this->makeObjPtr<SCSceneController::WeakPtr>();
        ptrController->setModalParentController(controllerPtr2);
        ptrController->setScene(_pScene);
        
        if(_bBlackMaskForModal)
        {
            this->showBlackMask(true);
        }
        
        _pScene->addChild(ptrController->getBedNode());
        this->setAllTouchEnabled(false);
        
        // generate modal mssage
        SCMessage::Ptr ptrMsg = SCMessage::create();
        
        ptrMsg->nMsgID = SCID::Msg::kSCMsgModalSceneLostFocus;
        ptrMsg->paramters.setValue(MSG_KEY_CONTROLLER,this);
        SCMessageDispatch::getInstance()->postMessage(ptrMsg);
        
        ptrMsg->nMsgID = SCID::Msg::kSCMsgModalSceneGotFocus;
        ptrMsg->paramters.setValue(MSG_KEY_CONTROLLER,ptrController.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(ptrMsg);
    }
    
    SCSceneController::Ptr SCSceneController::popModalFromParent()
    {
        SCASSERT(_ptrParentModalController!=NULL);
        auto ret = _ptrParentModalController->makeObjPtr<SCSceneController::Ptr>();
        
        _ptrParentModalController->setAllTouchEnabled(true);
        if(_ptrParentModalController->isBlackMaskForModal())
        {
            _ptrParentModalController->showBlackMask(false);
        }
        
        _ptrParentModalController = NULL;
        _pBedNode->removeFromParent();
        
        // generate modal mssage
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgModalSceneGotFocus;
        ptrMsg->paramters.setValue(MSG_KEY_CONTROLLER,ret.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(ptrMsg);
        
        return ret;
    }
    
    void SCSceneController::setAllTouchEnabled(const bool bEnable)
    {
        if(_pDisableTouchLayer==NULL && !bEnable)
        {// turn to no touch
            auto pLayer = SCLayerDisableTouch::create();
            _pBedNode->addChild(pLayer);
            pLayer->setPosition(cocos2d::Vec2(0,0));
            
            _pDisableTouchLayer = pLayer;
        }
        else if(_pDisableTouchLayer!=NULL && bEnable)
        {// turn to touchable
            _pDisableTouchLayer->removeFromParentAndCleanup(true);
            _pDisableTouchLayer = NULL;
        }
    }
    
    
    void SCSceneController::showBlackMask(const bool bShow)
    {
        if(bShow)
        {
            if(_pBlackMaskLayer==NULL)
            {
                _pBlackMaskLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 200));
                _pBedNode->addChild(_pBlackMaskLayer);
            }
        }
        else
        {
            if(_pBlackMaskLayer!=NULL)
            {
                _pBlackMaskLayer->removeFromParentAndCleanup(true);
                _pBlackMaskLayer = NULL;
            }
        }
    }
    
    void SCSceneController::delayExecute(float fDelay,const std::function<void ()>& fun)
    {
        fDelay = (fDelay<0) ? 0 : fDelay;
        
        auto pSeqAction = ASequence(ADelayTime(fDelay),
                                    ACallFunc(fun),
                                    NULL);
        
        this->getBedNode()->runAction(pSeqAction);
    }
    
    void SCSceneController::delayExecute(float fDelay,const std::function<void(SCDictionary dic)>& func,SCDictionary dic)
    {
        this->delayExecute(fDelay,[func,dic]()
                           {
                               func(dic);
                           });
    }
    
    void SCSceneController::listenMessage(const int nMsg,FUN_SCMapMessage_t pfnFunc)
    {
        SC_RETURN_V_IF(nMsg<=0);
        
        if(pfnFunc==NULL)
        {// remove mapping
            _msg2FuncMap.erase(nMsg);
        }
        else
        {
            _msg2FuncMap[nMsg] = pfnFunc;
        }
    }
    
    void SCSceneController::onSCMessageProcess(SCMessage::Ptr ptrMsg)
    {
        SCASSERT(ptrMsg!=NULL);
        
        auto it = _msg2FuncMap.find(ptrMsg->nMsgID);
        
        if(it!=_msg2FuncMap.end() && (*it).second!=NULL)
        {
            (this->*(*it).second)(ptrMsg);
        }
        
        SCStage::onSCMessageProcess(ptrMsg);
    }
    
}

