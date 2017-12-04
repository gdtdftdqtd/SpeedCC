
#include "SCSceneLayer.h"
#include "SCSceneControllerT.h"

namespace SpeedCC
{
	SCDictionary     SCSceneControllerT::s_SceneParameterDic;

    ///------------- SCSceneLayer
//    SCSceneLayer* SCSceneLayer::create()
//    {
//        SCSceneLayer *ret = new (std::nothrow) SCSceneLayer();
//        if (ret && ret->init())
//        {
//            ret->autorelease();
//            return ret;
//        }
//        else
//        {
//            CC_SAFE_DELETE(ret);
//            return nullptr;
//        }
//    }
    
    void SCSceneLayer::setControllerInterface(SCObject::Ptr interfacePtr)
    {
        _sceneControllerPtr = interfacePtr;
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
    
	void SCScene::onEnter()
	{
        cocos2d::SCScene::onEnterTransitionDidFinish();
	}

	void SCScene::onEnterTransitionDidFinish()
	{
        cocos2d::SCScene::onEnterTransitionDidFinish();
	}

	void SCScene::onExit()
	{
        cocos2d::SCScene::onEnterTransitionDidFinish();
	}

	void SCScene::onExitTransitionDidStart()
	{
        cocos2d::SCScene::onEnterTransitionDidFinish();
	}

}


