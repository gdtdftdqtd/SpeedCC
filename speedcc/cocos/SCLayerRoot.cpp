
#include "SCLayerRoot.h"
#include "SCSceneController.h"
#include "SCNodeUtils.h"
#include "SCCocosDef.h"

using namespace cocos2d;

namespace SpeedCC
{
    ///------------- SCSceneLayer
    
    bool SCLayerRoot::init()
    {
        SC_RETURN_IF(!Layer::init(),false);
        this->setContentSize(SCWinSize());
        return true;
    }
    
    void SCLayerRoot::setController(SCObject::Ptr controllerPtr)
    {
        _sceneControllerPtr = controllerPtr;
    }
    
    void SCLayerRoot::onEnter()
    {
        cocos2d::Layer::onEnter();
        
        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,this};
        SCDictionary dic(pair);
        SCMsgDisp()->sendMessage(kSCMsgSceneEnter,dic);
    }
    
    void SCLayerRoot::onEnterTransitionDidFinish()
    {
        cocos2d::Layer::onEnterTransitionDidFinish();
        
        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,this};
        SCDictionary dic(pair);
        SCMsgDisp()->sendMessage(kSCMsgSceneEnterTransitionDidFinish,dic);
    }
    
    void SCLayerRoot::onExit()
    {
        cocos2d::Layer::onExit();
        
        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,this};
        SCDictionary dic(pair);
        SCMsgDisp()->sendMessage(kSCMsgSceneExit,dic);
    }
    
    void SCLayerRoot::onExitTransitionDidStart()
    {
        cocos2d::Layer::onExitTransitionDidStart();
        
        SCDictionary::SPair pair = {MSG_KEY_CONTROLLER,this};
        SCDictionary dic(pair);
        SCMsgDisp()->sendMessage(kSCMsgSceneExitTransitionDidStart,dic);
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
        
        _pRootLayer = SCLayerRoot::create();
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
    
    void SCScene::setRootLayer(SCLayerRoot* pLayer)
    {
        _pRootLayer = pLayer;
    }
    
    SCLayerRoot* SCScene::getRootLayer()
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


