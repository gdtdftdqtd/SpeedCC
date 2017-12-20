
#include "SCLayerRoot.h"
#include "SCSceneController.h"
#include "SCNodeUtils.h"

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
    }
    
    void SCLayerRoot::onEnterTransitionDidFinish()
    {
        cocos2d::Layer::onEnterTransitionDidFinish();
    }
    
    void SCLayerRoot::onExit()
    {
        cocos2d::Layer::onExit();
    }
    
    void SCLayerRoot::onExitTransitionDidStart()
    {
        cocos2d::Layer::onExitTransitionDidStart();
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
    
    ///-------------- SCNoTouchLayer
    
    void SCLayerNoTouch::onEnter()
    {
        EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
        pEventListener->setSwallowTouches(true);
        
        pEventListener->onTouchBegan = CC_CALLBACK_2(SCLayerNoTouch::onSCTouchBegan, this);
        
        SCCCTouchDispatch()->removeEventListenersForTarget(this);
        SCCCTouchDispatch()->addEventListenerWithSceneGraphPriority(pEventListener,this);
        
        Layer::onEnter();
    }
    
    void SCLayerNoTouch::onExit()
    {
        SCCCTouchDispatch()->removeEventListenersForTarget(this);
        Layer::onExit();
    }
    
    bool SCLayerNoTouch::onSCTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent)
    {
        return true;
    }
}


