
#include "SCScene.h"
#include "SCSceneController.h"
#include "SCNodeUtils.h"

using namespace cocos2d;

namespace SpeedCC
{
    ///------------- SCSceneLayer
    
    bool SCBedNode::init()
    {
        SC_RETURN_IF(!Node::init(),false);
        this->setContentSize(SCWinSize());
        return true;
    }
    
    void SCBedNode::setController(SCObject::Ptr controllerPtr)
    {
        _ptrController = controllerPtr;
    }
    
    
    void SCBedNode::onEnter()
    {
        cocos2d::Node::onEnter();
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgSceneEnter;
        _ptrController.cast<SCSceneController::Ptr>()->onSCMessageProcess(ptrMsg);
    }
    
    void SCBedNode::onEnterTransitionDidFinish()
    {
        cocos2d::Node::onEnterTransitionDidFinish();
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgSceneEnterTransitionDidFinish;
        _ptrController.cast<SCSceneController::Ptr>()->onSCMessageProcess(ptrMsg);
    }
    
    void SCBedNode::onExit()
    {
        cocos2d::Node::onExit();
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgSceneExit;
        _ptrController.cast<SCSceneController::Ptr>()->onSCMessageProcess(ptrMsg);
    }
    
    void SCBedNode::onExitTransitionDidStart()
    {
        cocos2d::Node::onExitTransitionDidStart();
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgSceneExitTransitionDidStart;
        _ptrController.cast<SCSceneController::Ptr>()->onSCMessageProcess(ptrMsg);
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
        
        _pSceneNode = SCBedNode::create();
        _pSceneNode->setContentSize(SCWinSize());
        _pSceneNode->setPosition(SCNodeUtils::posP2A(Vec2(0,0),SCWinSize()));
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
    
    void SCScene::setSceneNode(SCBedNode* pLayer)
    {
        _pSceneNode = pLayer;
    }
    
    SCBedNode* SCScene::getBedNode()
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


