
#include "SCSceneLayer.h"
#include "SCSceneControllerT.h"
#include "SCNodeUtils.h"

using namespace cocos2d;

namespace SpeedCC
{
    ///------------- SCSceneLayer
    
    bool SCSceneLayer::init()
    {
        SC_RETURN_IF(!Layer::init(),false);
        this->setContentSize(SCWinSize());
        return true;
    }
    
    void SCSceneLayer::setController(SCObject::Ptr controllerPtr)
    {
        _sceneControllerPtr = controllerPtr;
    }
    
    void SCSceneLayer::onEnter()
    {
        cocos2d::Layer::onEnter();
    }
    
    void SCSceneLayer::onEnterTransitionDidFinish()
    {
        cocos2d::Layer::onEnterTransitionDidFinish();
    }
    
    void SCSceneLayer::onExit()
    {
        cocos2d::Layer::onExit();
    }
    
    void SCSceneLayer::onExitTransitionDidStart()
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
        
        _pRootLayer = SCSceneLayer::create();
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
    
    void SCScene::setRootLayer(SCSceneLayer* pLayer)
    {
        _pRootLayer = pLayer;
    }
    
    SCSceneLayer* SCScene::getRootLayer()
    {
        return _pRootLayer;
    }
     

}


