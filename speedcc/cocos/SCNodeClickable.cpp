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

#include "SCNodeClickable.h"
#include "SCRefHolder.h"

using namespace cocos2d;

namespace SpeedCC
{
    SCNodeClickable::SCNodeClickable():
    _bActive(true),
    _pNode(nullptr),
    _bTrack(false),
    _bSelected(false),
    _pMenuItem(nullptr)
    {
    }
    
    SCNodeClickable::SCNodeClickable(cocos2d::Node* pNode):
    _bActive(true),
    _bTrack(false),
    _bSelected(false),
    _pMenuItem(nullptr)
    {
        this->setNode(pNode);
    }
    
    SCNodeClickable::SCNodeClickable(cocos2d::Node* pNode,SCBehavior::Ptr ptrBvr):
    _bActive(true),
    _bTrack(false),
    _bSelected(false),
    _pMenuItem(nullptr),
    _ptrBvr(ptrBvr)
    {
        this->setNode(pNode);
    }
    
    SCNodeClickable::~SCNodeClickable()
    {
        
    }
    
    void SCNodeClickable::setActive(const bool bActive)
    {
        if(_ptrEventEmitter!=nullptr)
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
        _ptrEventEmitter = nullptr;
        _pMenuItem = nullptr;
        _pNode = pNode;
        
        if(pNode!=nullptr)
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
                ptrMsg->parameters.setValue(SC_KEY_RESULT,false);
                
                auto pCamera = Camera::getVisitingCamera();
                SC_RETURN_V_IF(!pCamera || !_pNode->isVisible());
                
                SC_RETURN_V_IF(_pMenuItem!=nullptr && !_pMenuItem->isEnabled());
                
                Node* pTemNode = _pNode;
                do
                {
                    pTemNode = pTemNode->getParent();
                    SC_BREAK_IF(pTemNode==nullptr);
                    SC_RETURN_V_IF(!pTemNode->isVisible());
                }while(true);
                
                auto pEvent = (cocos2d::Touch*)ptrMsg->parameters.getValue(SC_KEY_TOUCH).getPointer();
                SC_RETURN_V_IF(!this->isNodeInTouch(pEvent,pCamera));
                
                _bTrack = true;
                _bSelected = true;
                ptrMsg->parameters.setValue(SC_KEY_RESULT,true);
                _pSelectedCamera = pCamera;
                if(_pMenuItem!=nullptr)
                {
                    _pMenuItem->selected();
                }
            }
                break;
                
            case SCID::Msg::kSCMsgTouchMoved:
            {
                SC_RETURN_V_IF(_pMenuItem==nullptr || !_bTrack);
                auto pEvent = (cocos2d::Touch*)ptrMsg->parameters.getValue(SC_KEY_TOUCH).getPointer();
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
                if(_ptrBvr!=nullptr)
                {
                    _ptrBvr->execute(dic);
                }
                if(_pMenuItem!=nullptr)
                {
                    _pMenuItem->unselected();
                    _pMenuItem->activate();
                }
                _bTrack = false;
                _pSelectedCamera = nullptr;
                _bSelected = false;
            }
                break;
                
            case SCID::Msg::kSCMsgTouchCancelled:
            {
                SC_RETURN_V_IF(!_bTrack);
                _pNode->retain();
                _bSelected = false;
                _bTrack = false;
                if(_pMenuItem!=nullptr)
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


