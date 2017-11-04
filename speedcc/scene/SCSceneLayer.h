

#ifndef __SPEEDCC__SCSCENELAYER_H__
#define __SPEEDCC__SCSCENELAYER_H__

#include "cocos2d.h"

namespace SpeedCC
{
    class SCSceneController;
    
    class SCSceneLayer : public cocos2d::Layer
    {
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
        virtual void onEnter();
        virtual void onEnterTransitionDidFinish();
        virtual void onExit();
        virtual void onExitTransitionDidStart();
        
        virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags);
        
    private:
//        SCSceneController*      _pSceneController;
    };
}

#endif // __SPEEDCC__SCSCENELAYER_H__
