
#include "SCScene.h"
#include "SCSceneController.h"
#include "SCNodeUtils.h"

using namespace cocos2d;

namespace SpeedCC
{
    template<typename T>
    void sendTouchMessage(SCObject::Ptr controlPtr,const int nMsg,T touch)
    {
        SCDictionary::SPair pair = {MSG_KEY_TOUCH,touch};
        
        SCDictionary dic(pair);
        
        SCMessageInfo mi;
        mi.nMsgID = nMsg;
        mi.paramters = dic;
        controlPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    ///------------- SCSceneLayer
    
    bool SCSceneNode::init()
    {
        SC_RETURN_IF(!Node::init(),false);
        this->setContentSize(SCWinSize());
        _touchMode = kTouchModeNone;
        _touchListener = NULL;
        return true;
    }
    
    void SCSceneNode::setController(SCObject::Ptr controllerPtr)
    {
        _sceneControllerPtr = controllerPtr;
    }
    
//    void SCSceneNode::sendSingleTouchMessage(const int nMsg,cocos2d::Touch* pTouch)
//    {
//        SCDictionary::SPair pair = {MSG_KEY_TOUCH,pTouch};
//
//        SCDictionary dic(pair);
//
//        SCMessageInfo mi;
//        mi.nMsgID = nMsg;
//        mi.paramters = dic;
//        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
//    }
    
//    void SCSceneNode::sendMultipleTouchMessage(const int nMsg,const std::vector<cocos2d::Touch*>& touchVtr)
//    {
//        SCDictionary::SPair pair = {MSG_KEY_TOUCHES,touchVtr};
//
//        SCDictionary dic(pair);
//
//        SCMessageInfo mi;
//        mi.nMsgID = nMsg;
//        mi.paramters = dic;
//        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
//    }
    
    void SCSceneNode::setTouchMode(const ETouchMode touch)
    {
        SC_RETURN_IF_V(touch==_touchMode);
        
        if(_touchListener!=NULL)
        {
            SCCCDirector()->getEventDispatcher()->removeEventListener(_touchListener);
            _touchListener = NULL;
        }
        
        switch(touch)
        {
            case kTouchModeSingle:
            {
                auto pListener = EventListenerTouchOneByOne::create();
                pListener->onTouchBegan = CC_CALLBACK_2(SCSceneNode::onSingleTouchBegan, this);
                pListener->onTouchMoved = CC_CALLBACK_2(SCSceneNode::onSingleTouchMoved, this);
                pListener->onTouchEnded = CC_CALLBACK_2(SCSceneNode::onSingleTouchEnded, this);
                pListener->onTouchCancelled = CC_CALLBACK_2(SCSceneNode::onSingleTouchCancelled, this);
                
                _touchListener = pListener;
                SCCCDirector()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
            }
                break;
                
            case kTouchModeMultiple:
            {
                auto pListener = EventListenerTouchAllAtOnce::create();
                pListener->onTouchesBegan = CC_CALLBACK_2(SCSceneNode::onMultipleTouchBegan, this);
                pListener->onTouchesMoved = CC_CALLBACK_2(SCSceneNode::onMultipleTouchMoved, this);
                pListener->onTouchesEnded = CC_CALLBACK_2(SCSceneNode::onMultipleTouchEnded, this);
                pListener->onTouchesCancelled = CC_CALLBACK_2(SCSceneNode::onMultipleTouchCancelled, this);
                
                _touchListener = pListener;
                SCCCDirector()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
            }
                break;
                
            case kTouchModeNone: break;
        }
    }
    
    bool SCSceneNode::onSingleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
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
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
        
        return mi.paramters.getValue("result").getBool();
    }
    
    void SCSceneNode::onSingleTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        sendTouchMessage(_sceneControllerPtr,kSCMsgTouchMoved,pTouch);
    }
    
    void SCSceneNode::onSingleTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        sendTouchMessage(_sceneControllerPtr,kSCMsgTouchEnded,pTouch);
    }
    
    void SCSceneNode::onSingleTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        sendTouchMessage(_sceneControllerPtr,kSCMsgTouchCancelled,pTouch);
    }
    
    void SCSceneNode::onMultipleTouchBegan(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        sendTouchMessage(_sceneControllerPtr,kSCMsgTouchBegan,touchVtr);
    }
    
    void SCSceneNode::onMultipleTouchMoved(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        sendTouchMessage(_sceneControllerPtr,kSCMsgTouchMoved,touchVtr);
    }
    
    void SCSceneNode::onMultipleTouchEnded(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        sendTouchMessage(_sceneControllerPtr,kSCMsgTouchEnded,touchVtr);
    }
    
    void SCSceneNode::onMultipleTouchCancelled(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent)
    {
        sendTouchMessage(_sceneControllerPtr,kSCMsgTouchCancelled,touchVtr);
    }
    
    void SCSceneNode::onEnter()
    {
        cocos2d::Node::onEnter();
        
//        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,_sceneControllerPtr.getRawPointer()};
//        SCDictionary dic(pair);
        
        SCMessageInfo mi;
        mi.nMsgID = kSCMsgSceneEnter;
//        mi.paramters = dic;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    void SCSceneNode::onEnterTransitionDidFinish()
    {
        cocos2d::Node::onEnterTransitionDidFinish();
        
//        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,_sceneControllerPtr.getRawPointer()};
//        SCDictionary dic(pair);

        SCMessageInfo mi;
        mi.nMsgID = kSCMsgSceneEnterTransitionDidFinish;
//        mi.paramters = dic;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    void SCSceneNode::onExit()
    {
        cocos2d::Node::onExit();
        
//        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,_sceneControllerPtr.getRawPointer()};
//        SCDictionary dic(pair);

        SCMessageInfo mi;
        mi.nMsgID = kSCMsgSceneExit;
//        mi.paramters = dic;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    void SCSceneNode::onExitTransitionDidStart()
    {
        cocos2d::Node::onExitTransitionDidStart();
        
//        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,_sceneControllerPtr.getRawPointer()};
//        SCDictionary dic(pair);
        
        SCMessageInfo mi;
        mi.nMsgID = kSCMsgSceneExitTransitionDidStart;
//        mi.paramters = dic;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }

    ///-------------- SCScene
    
    SCScene::SCScene():
    _pRootLayer(NULL),
    cocos2d::Scene()
    {
    }
    
    bool SCScene::init()
    {
        SC_RETURN_IF(!Scene::init(),false);
        
        _pRootLayer = SCSceneNode::create();
        _pRootLayer->setContentSize(SCWinSize());
        _pRootLayer->setPosition(SCNodeUtils::posR2A(Vec2(0,0),SCWinSize()));
        this->addChild(_pRootLayer);
        
        return true;
    }
    
	void SCScene::onEnter()
	{
        cocos2d::Scene::onEnter();
	}

	void SCScene::onEnterTransitionDidFinish()
	{
        cocos2d::Scene::onEnterTransitionDidFinish();
	}

	void SCScene::onExit()
	{
        cocos2d::Scene::onExit();
	}

	void SCScene::onExitTransitionDidStart()
	{
        cocos2d::Scene::onExitTransitionDidStart();
	}
    
    void SCScene::setSceneNode(SCSceneNode* pLayer)
    {
        _pRootLayer = pLayer;
    }
    
    SCSceneNode* SCScene::getSceneNode()
    {
        return _pRootLayer;
    }
    
    ///-------------- SCDisableTouchLayer
    
    void SCLayerDisableTouch::onEnter()
    {
        EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
        pEventListener->setSwallowTouches(true);
        
        pEventListener->onTouchBegan = CC_CALLBACK_2(SCLayerDisableTouch::onSCTouchBegan, this);
        
        SCCCTouchDispatch()->removeEventListenersForTarget(this);
        SCCCTouchDispatch()->addEventListenerWithSceneGraphPriority(pEventListener,this);
        
        this->setTag(kTAG);
        
        Layer::onEnter();
    }
    
    void SCLayerDisableTouch::onExit()
    {
        SCCCTouchDispatch()->removeEventListenersForTarget(this);
        Layer::onExit();
    }
    
    bool SCLayerDisableTouch::onSCTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        return true;
    }
}


