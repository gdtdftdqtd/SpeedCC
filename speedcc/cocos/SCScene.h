/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

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
        inline SCObject::Ptr getController() {return _ptrController;}
        
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
        SCObject::Ptr               _ptrController;
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
        
        enum {kTAG = 1200};
        
        virtual void onEnter() override;
        virtual void onExit() override;
        bool onSCTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent);
    };
    
}

#endif // __SPEEDCC__SCSCENE_H__
