
#include "SCSceneLayer.h"
#include "SCSceneControllerT.h"

namespace SpeedCC
{
//    SCDictionary     SCSceneControllerT::s_SceneParameterDic;

    ///------------- SCSceneLayer
    
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


