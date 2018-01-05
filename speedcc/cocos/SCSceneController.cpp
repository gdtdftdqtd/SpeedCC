

#include "cocos2d.h"

#include "SCSceneController.h"
#include "SCCocosDef.h"


namespace SpeedCC
{
    ////-------------- member methods
    SCSceneController::SCSceneController():
    _pRootLayer(NULL),
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
    
//    void SCSceneController::onStageSetup()
//    {
//        this->setActive(true); // active stage
//    }
    
    void SCSceneController::pushModalController(SCSceneController::Ptr controllerPtr)
    {
        SCSceneController::WeakPtr controllerPtr2 = this->makeObjPtr<SCSceneController>();
        controllerPtr->setModalParentController(controllerPtr2);
        controllerPtr->setScene(_pScene);
        
        if(_bBlackMaskForModal)
        {
            this->showBlackMask(true);
        }
        
        _pScene->addChild(controllerPtr->getRootLayer());
        this->setDisableTouch(true);
        
        // generate modal mssage
        SCMessageInfo mi;
        
        mi.nMsgID = kSCMsgModalSceneLostFocus;
        mi.paramters.setValue(MSG_KEY_CONTROLLER,this);
        SCMessageDispatch::getInstance()->postMessage(mi);
        
        mi.nMsgID = kSCMsgModalSceneGotFocus;
        mi.paramters.setValue(MSG_KEY_CONTROLLER,controllerPtr.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(mi);
    }
    
    SCSceneController::Ptr SCSceneController::popModalFromParent()
    {
        SCASSERT(_parentModalControllerPtr!=NULL);
        auto ret = _parentModalControllerPtr->makeObjPtr<SCSceneController>();
        
        _parentModalControllerPtr->setDisableTouch(false);
        if(_parentModalControllerPtr->isBlackMaskForModal())
        {
            _parentModalControllerPtr->showBlackMask(false);
        }
        
        _parentModalControllerPtr = NULL;
        _pRootLayer->removeFromParent();
        
        // generate modal mssage
        SCMessageInfo mi;
        mi.nMsgID = kSCMsgModalSceneGotFocus;
        mi.paramters.setValue(MSG_KEY_CONTROLLER,ret.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(mi);
        
        return ret;
    }
    
    
    void SCSceneController::setDisableTouch(const bool bDisableTouch)
    {
        if(_pDisableTouchLayer==NULL && bDisableTouch)
        {// turn to no touch
            auto pLayer = SCLayerDisableTouch::create();
            _pRootLayer->addChild(pLayer);
            pLayer->setPosition(cocos2d::Vec2(0,0));
            
            _pDisableTouchLayer = pLayer;
        }
        else if(_pDisableTouchLayer!=NULL && !bDisableTouch)
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
                _pRootLayer->addChild(_pBlackMaskLayer);
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
        
        this->getRootLayer()->runAction(pSeqAction);
    }
    
    void SCSceneController::onSCMessageProcess(SCMessageInfo& mi)
    {
        SCStage::onSCMessageProcess(mi);
    }
}

