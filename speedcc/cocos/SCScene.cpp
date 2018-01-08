
#include "SCScene.h"
#include "SCSceneController.h"
#include "SCNodeUtils.h"

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
        
        SCMessage::Ptr mi = SCMessage::create();
        mi->nMsgID = kSCMsgSceneEnter;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    void SCSceneNode::onEnterTransitionDidFinish()
    {
        cocos2d::Node::onEnterTransitionDidFinish();
        
        SCMessage::Ptr mi = SCMessage::create();
        mi->nMsgID = kSCMsgSceneEnterTransitionDidFinish;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    void SCSceneNode::onExit()
    {
        cocos2d::Node::onExit();
        
        SCMessage::Ptr mi = SCMessage::create();
        mi->nMsgID = kSCMsgSceneExit;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }
    
    void SCSceneNode::onExitTransitionDidStart()
    {
        cocos2d::Node::onExitTransitionDidStart();
        
        SCMessage::Ptr mi = SCMessage::create();
        mi->nMsgID = kSCMsgSceneExitTransitionDidStart;
        _sceneControllerPtr.cast<SCSceneController>()->onSCMessageProcess(mi);
    }

    ///-------------- SCScene
    
    SCScene::SCScene():
    _pSceneNode(NULL),
    cocos2d::Scene()
    {
    }
    
    bool SCScene::init()
    {
        SC_RETURN_IF(!Scene::init(),false);
        
        _pSceneNode = SCSceneNode::create();
        _pSceneNode->setContentSize(SCWinSize());
        _pSceneNode->setPosition(SCNodeUtils::posR2A(Vec2(0,0),SCWinSize()));
        this->addChild(_pSceneNode);
        
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
        _pSceneNode = pLayer;
    }
    
    SCSceneNode* SCScene::getSceneNode()
    {
        return _pSceneNode;
    }
    
    ///-------------- SCDisableTouchLayer
    
    void SCLayerDisableTouch::onEnter()
    {
        EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
        pEventListener->setSwallowTouches(true);
        
        pEventListener->onTouchBegan = SC_MAKE_FUNC(onSCTouchBegan, this);
        
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


