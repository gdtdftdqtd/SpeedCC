

#ifndef __SPEEDCC__SCSCENE_H__
#define __SPEEDCC__SCSCENE_H__

#include "cocos2d.h"
#include "../base/SCObject.h"
#include "SCCocosDef.h"

namespace SpeedCC
{
    ///----------- SCSceneLayer
    class SCBedNode : public cocos2d::Node
    {
    public:
        CREATE_FUNC(SCBedNode);
        void setController(SCObject::Ptr controllerPtr);
        inline SCObject::Ptr getController() {return _sceneControllerPtr;}
        
        virtual bool init() override;
        
    protected:

//        void onAcceleration(cocos2d::Acceleration* pAcc, cocos2d::Event* pEvent);
        /*
        
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
        SCObject::Ptr               _sceneControllerPtr;
        cocos2d::EventListener*     _accListener;
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
        
        void setSceneNode(SCBedNode* pLayer);
        SCBedNode* getBedNode();
        
    private:
        SCBedNode*           _pSceneNode;
    };
    
    ///------------ SCLayerDisableTouch
    class SCLayerDisableTouch : public cocos2d::Layer
    {
    public:
        CREATE_FUNC(SCLayerDisableTouch);
        
        enum _tagNodeTag {kTAG = 1200};
        
        virtual void onEnter() override;
        virtual void onExit() override;
        bool onSCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    };
    
}

#endif // __SPEEDCC__SCSCENE_H__
