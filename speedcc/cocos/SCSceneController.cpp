

#include "cocos2d.h"

#include "SCSceneController.h"
#include "../base/SCTemplateUtils.h"

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
    
    void SCSceneController::ownLifecycle(cocos2d::Ref* pObject)
    {
        SC_RETURN_IF_V(pObject==NULL);
        
        auto ptr = SCRefHolder::create(pObject);
        this->ownLifecycle(ptr);
    }
    
    void SCSceneController::pushModalController(SCSceneController::Ptr controllerPtr)
    {
        SCSceneController::WeakPtr controllerPtr2 = this->makeObjPtr<SCSceneController::WeakPtr>();
        controllerPtr->setModalParentController(controllerPtr2);
        controllerPtr->setScene(_pScene);
        
        if(_bBlackMaskForModal)
        {
            this->showBlackMask(true);
        }
        
        _pScene->addChild(controllerPtr->getBedNode());
        this->setAllTouchEnabled(false);
        
        // generate modal mssage
        SCMessage::Ptr ptrMsg = SCMessage::create();
        
        ptrMsg->nMsgID = SCID::Msg::kSCMsgModalSceneLostFocus;
        ptrMsg->paramters.setValue(MSG_KEY_CONTROLLER,this);
        SCMessageDispatch::getInstance()->postMessage(ptrMsg);
        
        ptrMsg->nMsgID = SCID::Msg::kSCMsgModalSceneGotFocus;
        ptrMsg->paramters.setValue(MSG_KEY_CONTROLLER,controllerPtr.getRawPointer());
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
    
    
    void SCSceneController::onSCMenuItemPressed(cocos2d::Ref* pSender)
    {
        auto it = _buttonItem2InfoMap.find(pSender);
        
        SCASSERT(it!=_buttonItem2InfoMap.end());
        if(it!=_buttonItem2InfoMap.end())
        {
            auto it2 = _toggleItem2WatchMap.find(pSender);
            if(it2!=_toggleItem2WatchMap.end())
            {
                if((*it2).second!=NULL)
                {
                    *((*it2).second) = !(*((*it2).second));
                }
            }
            
            if((*it).second!=NULL)
            {
                (*it).second->execute();
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
    
    void SCSceneController::delayExecute(float fDelay,const std::function<void(SCDictionary::Ptr ptrDic)>& func,SCDictionary::Ptr ptrDic)
    {
        this->delayExecute(fDelay,[func,ptrDic]()
                           {
                               func(ptrDic);
                           });
    }
    
    void SCSceneController::listenMessage(const int nMsg,FUN_SCMapMessage_t pfnFunc)
    {
        SC_RETURN_IF_V(nMsg<=0);
        
        if(pfnFunc==NULL)
        {// remove mapping
            _msg2FuncMap.erase(nMsg);
        }
        else
        {
            _msg2FuncMap[nMsg] = pfnFunc;
        }
    }
    
    cocos2d::Node* SCSceneController::getLayoutNode(const int nID)
    {
        SC_RETURN_IF(nID<=0, NULL);
        
        auto it = _id2NodeMap.find(nID);
        SC_RETURN_IF(it==_id2NodeMap.end(), NULL);
        
        return (*it).second;
    }
    
    void SCSceneController::storeLayoutNode(const int nID,cocos2d::Node* pNode)
    {
        SC_RETURN_IF_V(nID<=0 || pNode==NULL);
        
        _id2NodeMap[nID] = pNode;
    }
    
    void SCSceneController::onSCMessageProcess(SCMessage::Ptr ptrMsg)
    {
        auto it = _msg2FuncMap.find(ptrMsg->nMsgID);
        
        if(it!=_msg2FuncMap.end() && (*it).second!=NULL)
        {
            (this->*(*it).second)(ptrMsg);
        }
        
        SCStage::onSCMessageProcess(ptrMsg);
    }
    
}

