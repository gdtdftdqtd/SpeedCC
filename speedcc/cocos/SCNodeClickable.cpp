//
//  SCClickable.cpp
//  libspeedcc
//
//  Created by Kevin on 8/2/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCNodeClickable.h"
#include "SCRefHolder.h"

using namespace cocos2d;

namespace SpeedCC
{
    SCNodeClickable::SCNodeClickable():
    _bActive(true),
    _pNode(NULL),
    _bTrack(false),
    _bSelected(false),
    _pMenuItem(NULL)
    {
    }
    
    SCNodeClickable::SCNodeClickable(cocos2d::Node* pNode):
    _bActive(true),
    _bTrack(false),
    _bSelected(false),
    _pMenuItem(NULL)
    {
        this->setNode(pNode);
    }
    
    SCNodeClickable::SCNodeClickable(cocos2d::Node* pNode,SCBehavior::Ptr ptrBvr):
    _bActive(true),
    _bTrack(false),
    _bSelected(false),
    _pMenuItem(NULL),
    _ptrBvr(ptrBvr)
    {
        this->setNode(pNode);
    }
    
    SCNodeClickable::~SCNodeClickable()
    {
        
    }
    
    void SCNodeClickable::setActive(const bool bActive)
    {
        if(_ptrEventEmitter!=NULL)
        {
            _ptrEventEmitter->setActive(bActive);
        }
        
        _bActive = bActive;
    }
    
    void SCNodeClickable::setBehavior(SCBehavior::Ptr ptrBvr)
    {
        _ptrBvr = ptrBvr;
    }
    
    void SCNodeClickable::setNode(cocos2d::Node* pNode)
    {
        _ptrEventEmitter = NULL;
        _pMenuItem = NULL;
        _pNode = pNode;
        
        if(pNode!=NULL)
        {
            _ptrEventEmitter = SCEventEmitter::create(pNode,this);
            _ptrEventEmitter->setTouchMode(SCEventEmitter::ETouchMode::kSingle);
            _ptrEventEmitter->setActive(_bActive);
            _pMenuItem = dynamic_cast<MenuItem*>(_pNode);
        }
    }
    
    void SCNodeClickable::onSCMessageProcess(SCMessage::Ptr ptrMsg)
    {
        switch(ptrMsg->nMsgID)
        {
            case SCID::Msg::kSCMsgTouchBegan:
            {
                ptrMsg->paramters.setValue(SC_KEY_RESULT,false);
                
                auto pCamera = Camera::getVisitingCamera();
                SC_RETURN_V_IF(!pCamera || !_pNode->isVisible());
                
                SC_RETURN_V_IF(_pMenuItem!=NULL && !_pMenuItem->isEnabled());
                
                Node* pTemNode = _pNode;
                do
                {
                    pTemNode = pTemNode->getParent();
                    SC_BREAK_IF(pTemNode==NULL);
                    SC_RETURN_V_IF(!pTemNode->isVisible());
                }while(true);
                
                auto pEvent = (cocos2d::Touch*)ptrMsg->paramters.getValue(SC_KEY_TOUCH).getPointer();
                SC_RETURN_V_IF(!this->isNodeInTouch(pEvent,pCamera));
                
                _bTrack = true;
                _bSelected = true;
                ptrMsg->paramters.setValue(SC_KEY_RESULT,true);
                _pSelectedCamera = pCamera;
                if(_pMenuItem!=NULL)
                {
                    _pMenuItem->selected();
                }
            }
                break;
                
            case SCID::Msg::kSCMsgTouchMoved:
            {
                SC_RETURN_V_IF(_pMenuItem==NULL || !_bTrack);
                auto pEvent = (cocos2d::Touch*)ptrMsg->paramters.getValue(SC_KEY_TOUCH).getPointer();
                const bool bNewSelect = this->isNodeInTouch(pEvent,_pSelectedCamera);
                
                SC_RETURN_V_IF(bNewSelect==_bSelected);
                _bSelected = bNewSelect;
                if(_bSelected)
                {
                    _pMenuItem->selected();
                }
                else
                {
                    _pMenuItem->unselected();
                }
            }
                break;
                
            case SCID::Msg::kSCMsgTouchEnded:
            {
                SC_RETURN_V_IF(!_bTrack);
                SCDictionary dic = {SC_KEY_CCREF, SCRef2Ptr::create(_pNode)};
                SCMsgDisp()->postMessage(SCID::Msg::kSCMsgNodeClicked, dic);
                if(_ptrBvr!=NULL)
                {
                    _ptrBvr->execute(dic);
                }
                if(_pMenuItem!=NULL)
                {
                    _pMenuItem->unselected();
                    _pMenuItem->activate();
                }
                _bTrack = false;
                _pSelectedCamera = NULL;
                _bSelected = false;
            }
                break;
                
            case SCID::Msg::kSCMsgTouchCancelled:
            {
                SC_RETURN_V_IF(!_bTrack);
                _pNode->retain();
                _bSelected = false;
                _bTrack = false;
                if(_pMenuItem!=NULL)
                {
                    _pMenuItem->unselected();
                }
                _pNode->release();
            }
                break;
        }
    }
    
    bool SCNodeClickable::isNodeInTouch(cocos2d::Touch* pTouch, const cocos2d::Camera* pCamera)
    {
        Vec2 touchLocation = pTouch->getLocation();
        Rect rect;
        rect.size = _pNode->getContentSize();
        return cocos2d::isScreenPointInRect(touchLocation, pCamera, _pNode->getWorldToNodeTransform(), rect, nullptr);
    }
    
}


