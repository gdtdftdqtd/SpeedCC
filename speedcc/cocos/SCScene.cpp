/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
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


#include "SCScene.h"
#include "SCSceneController.h"
#include "SCNodeUtils.h"

using namespace cocos2d;

namespace SpeedCC
{
    ///------------- SCSceneLayer
    
    bool SCBedNode::init()
    {
        SC_RETURN_IF(!Node::init(),false);
        this->setContentSize(SCWinSize);
        return true;
    }
    
    void SCBedNode::setController(SCObject::Ptr controllerPtr)
    {
        _ptrController = controllerPtr;
    }
    
    
    void SCBedNode::onEnter()
    {
        cocos2d::Node::onEnter();
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgSceneEnter;
        _ptrController.cast<SCSceneController::Ptr>()->onSCMessageProcess(ptrMsg);
    }
    
    void SCBedNode::onEnterTransitionDidFinish()
    {
        cocos2d::Node::onEnterTransitionDidFinish();
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgSceneEnterTransitionDidFinish;
        _ptrController.cast<SCSceneController::Ptr>()->onSCMessageProcess(ptrMsg);
    }
    
    void SCBedNode::onExit()
    {
        cocos2d::Node::onExit();
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgSceneExit;
        _ptrController.cast<SCSceneController::Ptr>()->onSCMessageProcess(ptrMsg);
    }
    
    void SCBedNode::onExitTransitionDidStart()
    {
        cocos2d::Node::onExitTransitionDidStart();
        
        SCMessage::Ptr ptrMsg = SCMessage::create();
        ptrMsg->nMsgID = SCID::Msg::kSCMsgSceneExitTransitionDidStart;
        _ptrController.cast<SCSceneController::Ptr>()->onSCMessageProcess(ptrMsg);
    }

    ///-------------- SCScene
    
    SCScene::SCScene():
    _pSceneNode(nullptr),
    cocos2d::Scene()
    {
    }
    
    bool SCScene::init()
    {
        SC_RETURN_IF(!Scene::init(),false);
        
        _pSceneNode = SCBedNode::create();
        _pSceneNode->setContentSize(SCWinSize);
        _pSceneNode->setPosition(SCNodeUtils::posP2A(Vec2(0,0),SCWinSize));
        this->addChild(_pSceneNode);
        
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
    
    void SCScene::setSceneNode(SCBedNode* pLayer)
    {
        _pSceneNode = pLayer;
    }
    
    SCBedNode* SCScene::getBedNode()
    {
        return _pSceneNode;
    }
    
    ///-------------- SCDisableTouchLayer
    
    void SCLayerDisableTouch::onEnter()
    {
        EventListenerTouchOneByOne* pEventListener = EventListenerTouchOneByOne::create();
        pEventListener->setSwallowTouches(true);
        
        pEventListener->onTouchBegan = SC_MAKE_FUNC(onSCTouchBegan, this);
        
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


