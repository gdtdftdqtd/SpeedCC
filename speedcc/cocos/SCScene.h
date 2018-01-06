

#ifndef __SPEEDCC__SCSCENE_H__
#define __SPEEDCC__SCSCENE_H__

#include "cocos2d.h"
#include "../base/SCObject.h"
#include "SCCocosDef.h"

namespace SpeedCC
{
    ///----------- SCSceneLayer
    class SCSceneNode : public cocos2d::Node
    {
    public:
        CREATE_FUNC(SCSceneNode);
        void setController(SCObject::Ptr controllerPtr);
        inline SCObject::Ptr getController() {return _sceneControllerPtr;}
        
        virtual bool init() override;
        
        void setTouchMode(const ETouchMode touch);
        inline ETouchMode getTouchMode() const { return _touchMode;}
    protected:
        
        bool onSingleTouchBegan(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        void onSingleTouchMoved(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        void onSingleTouchEnded(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        void onSingleTouchCancelled(cocos2d::Touch* pTouch, cocos2d::Event* pEvent);
        
        void onMultipleTouchBegan(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        void onMultipleTouchMoved(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        void onMultipleTouchEnded(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        void onMultipleTouchCancelled(const std::vector<cocos2d::Touch*>& touchVtr, cocos2d::Event* pEvent);
        
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
        
//        void sendTouchMessage(const int nMsg,cocos2d::Touch* pTouch);
//        void sendMultipleTouchMessage(const int nMsg,const std::vector<cocos2d::Touch*>& touchVtr);
        
    private:
        SCObject::Ptr               _sceneControllerPtr;
        ETouchMode                  _touchMode;
        cocos2d::EventListener*     _touchListener;
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
        
        void setSceneNode(SCSceneNode* pLayer);
        SCSceneNode* getSceneNode();
        
        
    private:
        SCSceneNode*           _pRootLayer;
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
