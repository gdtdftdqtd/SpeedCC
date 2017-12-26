

#ifndef __SPEEDCC__SCSCENELAYER_H__
#define __SPEEDCC__SCSCENELAYER_H__

#include "cocos2d.h"
#include "../base/SCObject.h"

namespace SpeedCC
{
    ///----------- SCSceneLayer
    class SCLayerRoot : public cocos2d::Layer
    {
    public:
        CREATE_FUNC(SCLayerRoot);
        void setController(SCObject::Ptr controllerPtr);
        inline SCObject::Ptr getController() {return _sceneControllerPtr;}
        
        virtual bool init() override;
    protected:
        /*
        virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);
        
        virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
        virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
        virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *unused_event);
        virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>&touches, cocos2d::Event *unused_event);
        
        virtual void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);
        
        virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
        virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
        */
        virtual void onEnter() override;
        virtual void onEnterTransitionDidFinish() override;
        virtual void onExit() override;
        virtual void onExitTransitionDidStart() override;
        
//        virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
        
    private:
        SCObject::Ptr           _sceneControllerPtr;
    };
    
    ///----------- SCScene
    class SCScene : public cocos2d::Scene
    {
    public:
        SCScene();
        CREATE_FUNC(SCScene);
        
        virtual bool init() override;

        virtual void onEnter() override;
        virtual void onEnterTransitionDidFinish() override;
        virtual void onExit() override;
        virtual void onExitTransitionDidStart() override;
        
        void setRootLayer(SCLayerRoot* pLayer);
        SCLayerRoot* getRootLayer();
        
        
    private:
        SCLayerRoot*           _pRootLayer;
    };
    
    ///------------ SCLayerNoTouch
    class SCLayerNoTouch : public cocos2d::Layer
    {
    public:
        CREATE_FUNC(SCLayerNoTouch);
        
        enum _tagNodeTag {kTAG = 1200};
        
        virtual void onEnter() override;
        virtual void onExit() override;
        bool onSCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    };
    
}

#endif // __SPEEDCC__SCSCENELAYER_H__
