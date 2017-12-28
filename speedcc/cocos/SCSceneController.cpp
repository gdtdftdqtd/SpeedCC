

#include "cocos2d.h"

#include "SCSceneController.h"


namespace SpeedCC
{
    ////-------------- member methods
    SCSceneController::SCSceneController():
    _pRootLayer(NULL),
    _pScene(NULL),
    _pNoTouchLayer(NULL),
    _pBlackMaskLayer(NULL),
    _bBlackMaskForModal(true)
    {}
    
    void SCSceneController::ownLifecycle(cocos2d::Ref* pObject)
    {
        SC_RETURN_IF_V(pObject==NULL);
        
        auto ptr = SCRefHolder::create(pObject);
        this->ownLifecycle(ptr);
    }
    
    
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
        this->setNoTouch(true);
        
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
        
        _parentModalControllerPtr->setNoTouch(false);
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
    
    
    void SCSceneController::setNoTouch(const bool bNoTouch)
    {
        if(_pNoTouchLayer==NULL && bNoTouch)
        {// turn to no touch
            auto pLayer = SCLayerNoTouch::create();
            _pRootLayer->addChild(pLayer);
            pLayer->setPosition(cocos2d::Vec2(0,0));
            
            _pNoTouchLayer = pLayer;
        }
        else if(_pNoTouchLayer!=NULL && !bNoTouch)
        {// turn to touchable
            _pNoTouchLayer->removeFromParentAndCleanup(true);
            _pNoTouchLayer = NULL;
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
                (*it).second->start();
            }
        }
    }
}

