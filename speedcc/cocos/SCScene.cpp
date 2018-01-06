
#include "SCScene.h"
#include "SCSceneController.h"
#include "SCNodeUtils.h"
#include "SCCocosDef.h"

using namespace cocos2d;

namespace SpeedCC
{
    ///------------- SCSceneLayer
    
    bool SCSceneNode::init()
    {
        SC_RETURN_IF(!Node::init(),false);
        this->setContentSize(SCWinSize());
        return true;
    }
    
    void SCSceneNode::setController(SCObject::Ptr controllerPtr)
    {
        _sceneControllerPtr = controllerPtr;
    }
    
    void SCSceneNode::onEnter()
    {
        cocos2d::Node::onEnter();
        
        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,this};
        SCDictionary dic(pair);
        
        SCMessageInfo mi;
        mi.nMsgID = kSCMsgSceneEnter;
        mi.paramters = dic;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    void SCSceneNode::onEnterTransitionDidFinish()
    {
        cocos2d::Node::onEnterTransitionDidFinish();
        
        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,this};
        SCDictionary dic(pair);

        SCMessageInfo mi;
        mi.nMsgID = kSCMsgSceneEnterTransitionDidFinish;
        mi.paramters = dic;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    void SCSceneNode::onExit()
    {
        cocos2d::Node::onExit();
        
        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,this};
        SCDictionary dic(pair);

        SCMessageInfo mi;
        mi.nMsgID = kSCMsgSceneExit;
        mi.paramters = dic;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    void SCSceneNode::onExitTransitionDidStart()
    {
        cocos2d::Node::onExitTransitionDidStart();
        
        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,this};
        SCDictionary dic(pair);
        
        SCMessageInfo mi;
        mi.nMsgID = kSCMsgSceneExitTransitionDidStart;
        mi.paramters = dic;
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
    
    SCSceneNode* SCScene::getRootLayer()
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


