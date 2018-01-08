

#include "cocos2d.h"

#include "SCSceneController.h"
#include "../base/SCTemplateUtils.h"

namespace SpeedCC
{
    ////-------------- member methods
    SCSceneController::SCSceneController():
    _pRootNode(NULL),
    _pScene(NULL),
    _pDisableTouchLayer(NULL),
    _pBlackMaskLayer(NULL),
    _bBlackMaskForModal(true),
    _touchMode(ETouchMode::kTouchNone),
    _pTouchListener(NULL)
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
        SCSceneController::WeakPtr controllerPtr2 = this->makeObjPtr<SCSceneController>();
        controllerPtr->setModalParentController(controllerPtr2);
        controllerPtr->setScene(_pScene);
        
        if(_bBlackMaskForModal)
        {
            this->showBlackMask(true);
        }
        
        _pScene->addChild(controllerPtr->getSceneNode());
        this->setAllTouchEnabled(false);
        
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
        
        _parentModalControllerPtr->setAllTouchEnabled(true);
        if(_parentModalControllerPtr->isBlackMaskForModal())
        {
            _parentModalControllerPtr->showBlackMask(false);
        }
        
        _parentModalControllerPtr = NULL;
        _pRootNode->removeFromParent();
        
        // generate modal mssage
        SCMessageInfo mi;
        mi.nMsgID = kSCMsgModalSceneGotFocus;
        mi.paramters.setValue(MSG_KEY_CONTROLLER,ret.getRawPointer());
        SCMessageDispatch::getInstance()->postMessage(mi);
        
        return ret;
    }
    
    void SCSceneController::setAllTouchEnabled(const bool bEnable)
    {
        if(_pDisableTouchLayer==NULL && !bEnable)
        {// turn to no touch
            auto pLayer = SCLayerDisableTouch::create();
            _pRootNode->addChild(pLayer);
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
                _pRootNode->addChild(_pBlackMaskLayer);
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
        
        this->getSceneNode()->runAction(pSeqAction);
    }
    
    void SCSceneController::delayExecute(float fDelay,FUN_SCDelayExecute_t pfnFunc,const SCDictionary& dic)
    {
        SC_RETURN_IF_V(pfnFunc==NULL);
        
        this->delayExecute(fDelay,[this,dic,pfnFunc]()
                           {
                               (this->*(pfnFunc))(dic);
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
    
    void SCSceneController::onSCMessageProcess(SCMessageInfo& mi)
    {
        auto it = _msg2FuncMap.find(mi.nMsgID);
        
        if(it!=_msg2FuncMap.end() && (*it).second!=NULL)
        {
            (this->*(*it).second)(mi);
        }
        
        SCStage::onSCMessageProcess(mi);
    }
    
    ///--------------- cocos2d Events
    
    cocos2d::EventListener* SCSceneController::getEventListener(cocos2d::EventListener::Type type) const
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
    
    void SCSceneController::setTouchMode(const ETouchMode touch)
    {
        SC_RETURN_IF_V(touch==_touchMode);
        
        if(_pTouchListener!=NULL)
        {
            SCCCDirector()->getEventDispatcher()->removeEventListener(_pTouchListener);
            _pTouchListener = NULL;
        }
        
        switch(touch)
        {
            case ETouchMode::kTouchSingle:
            {
                auto pListener = cocos2d::EventListenerTouchOneByOne::create();
                pListener->setSwallowTouches(true);
                pListener->onTouchBegan = SCBindFuncUtilsT<decltype(SCTemplateUtils::getFuncArgsCount(&SCSceneController::onSingleTouchBegan))::value>::makeFunc(&SCSceneController::onSingleTouchBegan, this);
                pListener->onTouchMoved = SCBindFuncUtilsT<2>::makeFunc(&SCSceneController::onSingleTouchMoved, this);
                
                pListener->onTouchBegan = SC_MAKE_FUNC(onSingleTouchBegan, this);
                pListener->onTouchMoved = SC_MAKE_FUNC(onSingleTouchMoved, this);
                pListener->onTouchEnded = SC_MAKE_FUNC(onSingleTouchEnded, this);
                pListener->onTouchCancelled = SC_MAKE_FUNC(onSingleTouchCancelled, this);
                
                _pTouchListener = pListener;
                SCCCDirector()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pTouchListener, _pRootNode);
            }
                break;
                
            case ETouchMode::kTouchMultiple:
            {
                auto pListener = cocos2d::EventListenerTouchAllAtOnce::create();
                pListener->onTouchesBegan = SC_MAKE_FUNC(onMultipleTouchBegan, this);
                pListener->onTouchesMoved = SC_MAKE_FUNC(onMultipleTouchMoved, this);
                pListener->onTouchesEnded = SC_MAKE_FUNC(onMultipleTouchEnded, this);
                pListener->onTouchesCancelled = SC_MAKE_FUNC(onMultipleTouchCancelled, this);
                
                _pTouchListener = pListener;
                SCCCDirector()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_pTouchListener, _pRootNode);
            }
                break;
                
            case ETouchMode::kTouchNone: break;
        }
    }
    
    bool SCSceneController::onSingleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        SCDictionary::SPair pair[] =
        {
            {MSG_KEY_TOUCH,pTouch},
            {"result",true},
        };
        
        SCDictionary dic(pair,SC_ARRAY_LENGTH(pair));
        
        SCMessageInfo mi;
        mi.nMsgID = kSCMsgTouchBegan;
        mi.paramters = dic;
        this->onSCMessageProcess(mi);
        
        return mi.paramters.getValue("result").getBool();
    }
    
    void SCSceneController::onSingleTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(kSCMsgTouchMoved,pTouch);
    }
    
    void SCSceneController::onSingleTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(kSCMsgTouchEnded,pTouch);
    }
    
    void SCSceneController::onSingleTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(kSCMsgTouchCancelled,pTouch);
    }
    
    void SCSceneController::onMultipleTouchBegan(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(kSCMsgTouchBegan,touchVtr);
    }
    
    void SCSceneController::onMultipleTouchMoved(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(kSCMsgTouchMoved,touchVtr);
    }
    
    void SCSceneController::onMultipleTouchEnded(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(kSCMsgTouchEnded,touchVtr);
    }
    
    void SCSceneController::onMultipleTouchCancelled(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        this->sendTouchMessage(kSCMsgTouchCancelled,touchVtr);
    }
}

