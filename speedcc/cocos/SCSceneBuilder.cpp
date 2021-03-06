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

#include "SCSceneBuilder.h"
#include "SCSceneController.h"
#include "SCNodeUtils.h"

#include "../stage/SCMessageDispatch.h"
#include "../stage/SCStageMacros.h"

#include "../system/SCSystem.h"

using namespace cocos2d;

namespace SpeedCC
{
#define SC_ASSIGN_NODE(_to_,_from_) \
    do{ if((_to_)!=nullptr) { (*(_to_)) = (_from_); }} while(0)
    
    ///------------ root container

    void SCSceneBuilder::beginContainerRoot(const float fPosX,
                                 const float fPosY,
                                 const SCUIArg::StringPurifier& style,
                                 const SCUIArg::SizePurifier& sizePurifier,
                                 const SCUIArg::NodePurifier& parentNode,
                                 cocos2d::Ref* pRef)
    {
        Node* pParentNode = dynamic_cast<Node*>(parentNode.ptrNodeHolder->getRef());
        SCASSERT(pParentNode!=nullptr);
        _pCurrentRefCaller = pRef;
        _pCurrentBedNode = pParentNode;
        SCASSERT(_pCurrentBedNode!=nullptr);
        SCASSERT(_pCurrentRefCaller!=nullptr);
        
        cocos2d::Size size = (sizePurifier.size.equals(Size::ZERO)) ? pParentNode->getContentSize() : sizePurifier.size;
        
        _pCurrentBedNode->setContentSize(size);
        
        _pCurrentBedNode->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
        _pCurrentBedNode->setIgnoreAnchorPointForPosition(false);
        
        if(fPosX!=kSCPositionIgnore && fPosY!=kSCPositionIgnore)
        {
            _pCurrentBedNode->setPosition(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2(fPosX,fPosY),size));
        }
        else if(fPosX!=kSCPositionIgnore)
        {
            _pCurrentBedNode->setPositionX(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2(fPosX,fPosY),size).x);
        }
        else if(fPosY!=kSCPositionIgnore)
        {
            _pCurrentBedNode->setPositionY(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2(fPosX,fPosY),size).y);
        }
        
        SCNodeStyle::SFilterConfig config;
        config.setupPosition(true);
        parentNode.pfunSetStyle(pParentNode,style.strResult,&config);
        
        this->pushContainerStack(pParentNode);
    }
    
    void SCSceneBuilder::popContainerStack()
    {
        SCASSERT(!_contextStack.empty());
        auto& front = _contextStack.front();
        
        if(front.endFunc!=nullptr)
        {
            front.endFunc(front);
        }
        
        _contextStack.pop_front();
    }
    
    ///------------ user node
    cocos2d::Node* SCSceneBuilder::insertUserNode(const SCUIArg::NodePurifier& userNode,
                                               const float fPosX,
                                               const float fPosY,
                                               const SCUIArg::StringPurifier& style)
    {
        Node* pNode = dynamic_cast<Node*>(userNode.ptrNodeHolder->getRef());
        SCASSERT(pNode!=nullptr);
        auto& top = _contextStack.front();
        top.pContainerNode->addChild(pNode);
        SCNodeUtils::setPositionPer(pNode, Vec2(fPosX,fPosY));
        
        if(top.containerType==SCUITypeDef::EContainerType::kLayoutPadding)
        {// for padding layout container, all of children position are ignored
        // it's position is handled by layout container while container context pops.
            SCNodeStyle::SFilterConfig config;
            config.setupPosition(true);
            userNode.pfunSetStyle(pNode,style.strResult,&config);
        }
        else
        {
            userNode.pfunSetStyle(pNode,style.strResult,nullptr);
        }
        
        return pNode;
    }
    
    ///---------------- sprite
    cocos2d::Sprite* SCSceneBuilder::insertSprite(cocos2d::Sprite** ppSprite,
                                  const float fPosX,
                                  const float fPosY,
                                  const SCUIArg::StringPurifier& style,
                                  const SCString& strImage)
    {
        auto pSprite = SCNodeUtils::createSprite(strImage);
        this->insertUserNode(pSprite,fPosX,fPosY,style);
        SC_ASSIGN_NODE(ppSprite,pSprite);
        return pSprite;
    }
    
    ///------------ label
    
    Label* SCSceneBuilder::insertLabel(cocos2d::Label** ppLabel,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const SCUIArg::LabelStringPurifier& labelString,
                                const SCString& strFont,
                                const float fFontSize)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithSystemFont(strLabelText.c_str(),strFont.c_str(),fFontSize);
        this->addLabel(pLabel,fPosX,fPosY,style,labelString);
        SC_ASSIGN_NODE(ppLabel,pLabel);
        return pLabel;
    }
    
    Label* SCSceneBuilder::insertLabelTTF(cocos2d::Label** ppLabel,
                                   const float fPosX,
                                   const float fPosY,
                                   const SCUIArg::StringPurifier& style,
                                   const SCUIArg::LabelStringPurifier& labelString,
                                   const SCString& strFont,
                                   const float fFontSize)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithTTF(strLabelText.c_str(),strFont.c_str(),fFontSize);
        this->addLabel(pLabel,fPosX,fPosY,style,labelString);
        SC_ASSIGN_NODE(ppLabel,pLabel);
        return pLabel;
    }
    
    cocos2d::Label* SCSceneBuilder::insertLabelBMFont(cocos2d::Label** ppLabel,
                                      const float fPosX,
                                      const float fPosY,
                                      const SCUIArg::StringPurifier& style,
                                      const SCUIArg::LabelStringPurifier& labelString,
                                      const SCString& strFile)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithBMFont(strFile.c_str(),strLabelText.c_str());
        this->addLabel(pLabel,fPosX,fPosY,style,labelString);
        SC_ASSIGN_NODE(ppLabel,pLabel);
        return pLabel;
    }
    
    void SCSceneBuilder::addLabel(const SCUIArg::NodePurifier& labelNode,
                               const float fPosX,
                              const float fPosY,
                              const SCUIArg::StringPurifier& style,
                              const SCUIArg::LabelStringPurifier& labelString)
    {
        this->bindLabel(labelNode,labelString);
        this->insertUserNode(labelNode, fPosX, fPosY, style);
    }
    
    void SCSceneBuilder::bindLabel(const SCUIArg::NodePurifier& labelNode,
                   const SCUIArg::LabelStringPurifier& labelString)
    {
        auto ptrBinder = labelString.ptrLabelBinder;
        cocos2d::Label* pLabel = dynamic_cast<Label*>(labelNode.ptrNodeHolder->getRef());
        SCASSERT(pLabel!=nullptr);
        
        if(ptrBinder!=nullptr && pLabel!=nullptr)
        {
            ptrBinder->setLabel(pLabel);
            SCNodeUtils::addUserObj(pLabel, ptrBinder);
        }
    }
    ///---------------- button
    cocos2d::MenuItemSprite* SCSceneBuilder::insertButton(cocos2d::MenuItemSprite** ppMenuItemSprite,
                                                      const float fPosX,
                                                      const float fPosY,
                                                      const SCUIArg::StringPurifier& style,
                                                      const SCString& strImageNormal,
                                                      const SCString& strSelect,
                                                      const SCString& strDisable,
                                                       SCUIArg::BehaviorPurifier bvrPurifier)
    {
        cocos2d::Sprite* pSpriteArray[3] = {nullptr};
        pSpriteArray[0] = SCNodeUtils::createSprite(strImageNormal);
        pSpriteArray[1] = SCNodeUtils::createSprite(strSelect);
        pSpriteArray[2] = SCNodeUtils::createSprite(strDisable);
        
        auto pItemImage = MenuItemSprite::create(pSpriteArray[0],
                                                 pSpriteArray[1],
                                                 pSpriteArray[2]);
        
        this->addButton(pItemImage,fPosX,fPosY,style,bvrPurifier);
        SC_ASSIGN_NODE(ppMenuItemSprite,pItemImage);
        
        return pItemImage;
    }
    
    MenuItemLabel* SCSceneBuilder::insertButtonLabel(MenuItemLabel** ppMenuItemLabel,
                                      const float fPosX,
                                      const float fPosY,
                                      const SCUIArg::StringPurifier& style,
                                      const SCUIArg::LabelStringPurifier& labelString,
                                      const SCString& strFont,
                                      const float fFontSize,
                                      SCUIArg::BehaviorPurifier bvrPurifier)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithSystemFont(strLabelText.c_str(),strFont.c_str(),fFontSize);
        
        auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,style,labelString,bvrPurifier);
        SC_ASSIGN_NODE(ppMenuItemLabel,ret);
        return ret;
    }
    
    MenuItemLabel* SCSceneBuilder::insertButtonLabelTTF(MenuItemLabel** ppMenuItemLabel,
                                                 const float fPosX,
                                                 const float fPosY,
                                                 const SCUIArg::StringPurifier& style,
                                                 const SCUIArg::LabelStringPurifier& labelString,
                                                 const SCString& strFont,
                                                 const float fFontSize,
                                                 SCUIArg::BehaviorPurifier bvrPurifier)
    {
        SCString strLabelText = labelString.strResult;
        auto pLabel = Label::createWithTTF(strLabelText.c_str(),strFont.c_str(),fFontSize);
        auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,style,labelString,bvrPurifier);
        SC_ASSIGN_NODE(ppMenuItemLabel,ret);
        return ret;
    }
    
    MenuItemLabel* SCSceneBuilder::insertButtonLabelBMFont(cocos2d::MenuItemLabel** ppMenuItemLabel,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& style,
                                                    const SCUIArg::LabelStringPurifier& labelString,
                                                    const SCString& strFile,
                                                    SCUIArg::BehaviorPurifier bvrPurifier)
    {
        SCString strLabelText = labelString.strResult;
        auto pLabel = Label::createWithBMFont(strFile.c_str(),strLabelText.c_str());
        auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,style,labelString,bvrPurifier);
        SC_ASSIGN_NODE(ppMenuItemLabel,ret);
        return ret;
    }
    
    MenuItemToggle* SCSceneBuilder::insertButtonSwitch(MenuItemToggle** ppMenuItemToggle,
                                                const float fPosX,
                                                const float fPosY,
                                                const SCUIArg::StringPurifier& style,
                                                const SCUIArg::MenuItemPurifier& itemOn,
                                                const SCUIArg::MenuItemPurifier& itemOff,
                                                const SCUIArg::BoolPurifier& value,
                                                SCUIArg::BehaviorPurifier bvrPurifier)
    {
        MenuItem* pOnItem = (MenuItem*)itemOn.ptrHolder->getRef();
        MenuItem* pOffItem = (MenuItem*)itemOff.ptrHolder->getRef();
        
        bvrPurifier.setupBehavior(_pCurrentRefCaller,pOnItem);
        bvrPurifier.setupBehavior(_pCurrentRefCaller,pOffItem);
        
        auto pToggleItem = MenuItemToggle::createWithCallback(nullptr,pOnItem,pOffItem,nullptr);
        pToggleItem->setSelectedIndex(value.bResult ? 0 : 1);
        
        if(value.ptrWatch!=nullptr)
        {
            auto ptrLabelBinder = SCBinderUISwitch::create();
            
            ptrLabelBinder->setWatch(value.ptrWatch);
            ptrLabelBinder->setToggle(pToggleItem);
            SCNodeUtils::addUserObj(pToggleItem, ptrLabelBinder);
        }

        bvrPurifier.setupBehavior(_pCurrentRefCaller, pToggleItem);
        SCNodeUtils::addClickable(pToggleItem, bvrPurifier.ptrResultBvr);
        
        this->insertUserNode(pToggleItem, fPosX, fPosY, style);
        
        SC_ASSIGN_NODE(ppMenuItemToggle,pToggleItem);
        
        return pToggleItem;
    }

    cocos2d::ProgressTimer* SCSceneBuilder::insertProgressBar(cocos2d::ProgressTimer** ppProgress,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::StringPurifier& style,
                                              const SCString& strBackgroundImage,
                                              const SCString& strFrontgroundImage,
                                              SCUIArg::NumberPurifier value,
                                              const bool bHorizontal,
                                              const bool bBaseLB)
    {
        SCASSERT(!strFrontgroundImage.isEmpty());
        
        Sprite* pSpriteBar = SCNodeUtils::createSprite(strFrontgroundImage);
        
        auto pProgressBar =  ProgressTimer::create(pSpriteBar);
        pProgressBar->setAnchorPoint(Vec2(0.5,0.5));
        pProgressBar->setIgnoreAnchorPointForPosition(false);
        if(bHorizontal)
        {
            pProgressBar->setBarChangeRate(Vec2(1,0));
            pProgressBar->setMidpoint(Vec2((bBaseLB)?0.0:1.0,0.5));
        }
        else
        {
            pProgressBar->setBarChangeRate(Vec2(0,1)) ;
            pProgressBar->setMidpoint(Vec2(0.5,(bBaseLB)?0.0:1.0));
        }

        pProgressBar->setType(ProgressTimer::Type::BAR);
        
        if(!strBackgroundImage.isEmpty())
        {
            Sprite* pSpriteBack = SCNodeUtils::createSprite(strBackgroundImage);
            pProgressBar->addChild(pSpriteBack,-1);
            pSpriteBack->setPosition(Vec2(pSpriteBar->getContentSize().width/2,pSpriteBar->getContentSize().height/2));
        }
        
        this->insertUserNode(pProgressBar, fPosX, fPosY, style);
        
        if(value.ptrBinderProgress!=nullptr)
        {
            value.ptrBinderProgress->setProgressTimer(pProgressBar);
            SCNodeUtils::addUserObj(pProgressBar, value.ptrBinderProgress);
        }
        else
        {
            pProgressBar->setPercentage(value.nPercentage);
        }
        SC_ASSIGN_NODE(ppProgress,pProgressBar);
        
        return pProgressBar;
    }
    
    ProgressTimer* SCSceneBuilder::insertProgressRadial(cocos2d::ProgressTimer** ppProgress,
                                                     const float fPosX,
                                                     const float fPosY,
                                                     const SCUIArg::StringPurifier& style,
                                                     const SCString& strBackgroundImage,
                                                     const SCString& strFrontgroundImage,
                                                     SCUIArg::NumberPurifier value,
                                                     const bool bCCW)
    {
        SCASSERT(!strFrontgroundImage.isEmpty());
        
        Sprite* pSpriteBar = SCNodeUtils::createSprite(strFrontgroundImage);
        
        auto pProgressBar =  ProgressTimer::create(pSpriteBar);
        pProgressBar->setType(ProgressTimer::Type::RADIAL);
        
        if(!strBackgroundImage.isEmpty())
        {
            Sprite* pSpriteBack = SCNodeUtils::createSprite(strBackgroundImage);
            pProgressBar->addChild(pSpriteBack,-1);
            SCNodeUtils::setPositionPer(pSpriteBack, Vec2(0.5,0.5));
        }
        
        pProgressBar->setReverseDirection(!bCCW);
        
        this->insertUserNode(pProgressBar, fPosX, fPosY, style);
        
        if(value.ptrBinderProgress!=nullptr)
        {
            value.ptrBinderProgress->setProgressTimer(pProgressBar);
            SCNodeUtils::addUserObj(pProgressBar, value.ptrBinderProgress);
        }
        else
        {
            pProgressBar->setPercentage(value.nPercentage);
        }
        SC_ASSIGN_NODE(ppProgress,pProgressBar);
        
        return pProgressBar;
    }
    
    void SCSceneBuilder::containerAlignment(Node** ppNode,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::StringPurifier& style,
                                              const bool bHorizontal,
                                              const float fPadding,
                                              const SCUIArg::DockPurifier& dockPurifier)
    {
        Node* pNode = Node::create();
        pNode->setIgnoreAnchorPointForPosition(false);
        pNode->setAnchorPoint(Vec2(0.5,0.5));
        
        SCString strDockStyle = SCNodeStyle::extractKey(SC_STYLE_DOCK, style.strResult);
        SCString strXByStyle = SCNodeStyle::extractKey(SC_STYLE_X_BY, style.strResult);
        SCString strYByStyle = SCNodeStyle::extractKey(SC_STYLE_Y_BY, style.strResult);
        
        SCString strNewStyle = style.strResult;
        if(!strDockStyle.isEmpty())
        {
            strNewStyle = SCNodeStyle::removeKey(SC_STYLE_DOCK,strNewStyle);
        }
        
        if(!strXByStyle.isEmpty())
        {
            strNewStyle = SCNodeStyle::removeKey(SC_STYLE_X_BY,strNewStyle);
        }
        
        if(!strYByStyle.isEmpty())
        {
            strNewStyle = SCNodeStyle::removeKey(SC_STYLE_Y_BY,strNewStyle);
        }
        
        SCString strDelayStyle = strDockStyle + strXByStyle + strYByStyle;
        
        SCUITypeDef::SUIContext context;
        context.pContainerNode = pNode;
        context.containerType = SCUITypeDef::EContainerType::kLayoutPadding;
        
        int nDock = dockPurifier.nDock;
        if(nDock==0)
        {
            nDock = SCNodeUtils::EDockType::kDockCenter;
        }
        
        context.endFunc = [bHorizontal,
                           fPadding,
                           nDock,
                           strDelayStyle](SCUITypeDef::SUIContext& context)
        {
            Node* pNode = context.pContainerNode;
            auto childrenVec = pNode->getChildren();
            SC_RETURN_V_IF(childrenVec.empty());
            
            if(bHorizontal)
            {// x
                float fWidth = 0;
                int nDock2 = SC_BIT_REMOVE(nDock,SCNodeUtils::kDockMiddleX);
                const bool bApplyDock = SC_BIT_HAS_OR(nDock2, SCNodeUtils::kDockMiddleY);
                
                float fMaxHeight = 0;
                for(const auto& child : childrenVec)
                {
                    fWidth += child->getContentSize().width * child->getScaleX() + fPadding;
                    
                    const float fRealHeight = child->getContentSize().height * child->getScaleY();
                    fMaxHeight = MAX(fMaxHeight,fRealHeight);
                }
                
                fWidth -= fPadding;
                pNode->setContentSize(Size(fWidth,fMaxHeight));
                
                float fOffset = (pNode->getContentSize().width-fWidth)/2;
                
                for(const auto& child : childrenVec)
                {
                    const float fRealWidth = child->getContentSize().width * child->getScaleX();
                    const auto& ptAnchor = child->isIgnoreAnchorPointForPosition() ? Vec2::ZERO : child->getAnchorPoint();
                    float fAnchorOffset = (ptAnchor.x-0.5)*fRealWidth;
                    
                    child->setPositionX(fOffset + fRealWidth/2 + fAnchorOffset);
                    fOffset += fRealWidth + fPadding;
                    
                    if(bApplyDock)
                    {
                        SCNodeUtils::setDock(child, nDock2);
                    }
                }
            }
            else
            {// y
                float fHeight = 0;
                int nDock2 = SC_BIT_REMOVE(nDock,SCNodeUtils::kDockMiddleY);
                const bool bApplyDock = SC_BIT_HAS_OR(nDock2, SCNodeUtils::kDockMiddleX);
                
                float fMaxWidth = 0;
                for(const auto& child : childrenVec)
                {
                    fHeight += child->getContentSize().height * child->getScaleY() + fPadding;
                    const float fRealWidth = child->getContentSize().width * child->getScaleX();
                    fMaxWidth = MAX(fMaxWidth,fRealWidth);
                }
                
                fHeight -= fPadding;
                pNode->setContentSize(Size(fMaxWidth,fHeight));
                float fOffset = fHeight + (pNode->getContentSize().height-fHeight)/2;
                
                for(const auto& child : childrenVec)
                {
                    const float fRealHeight = child->getContentSize().height * child->getScaleY();
                    const auto& ptAnchor = child->isIgnoreAnchorPointForPosition() ? Vec2::ZERO : child->getAnchorPoint();
                    float fAnchorOffset = (ptAnchor.y-0.5)*fRealHeight;
                    
                    child->setPositionY(fOffset - fRealHeight/2 + fAnchorOffset);
                    fOffset -= fRealHeight + fPadding;
                    
                    if(bApplyDock)
                    {
                        SCNodeUtils::setDock(child, nDock2);
                    }
                }
            }
            
            if(!strDelayStyle.isEmpty())
            {
                SCNodeStyle::setStyle<Node>(pNode, strDelayStyle);
            }
        };
        
        this->insertUserNode(pNode, fPosX, fPosY, strNewStyle);
        _contextStack.push_front(context);
        SC_ASSIGN_NODE(ppNode,pNode);
    }
    
    ///------------- cocos2d-x extension UI
    void SCSceneBuilder::containerScrollView(cocos2d::ui::ScrollView** ppScrollView,
                             const float fPosX,
                             const float fPosY,
                             const SCUIArg::StringPurifier& style,
                             const SCUIArg::ScrollViewDirectionPurifier& direction,
                             const cocos2d::Size& viewSize,
                             const cocos2d::Size& containerSize,
                             const std::function<void(cocos2d::Ref*, cocos2d::ui::ScrollView::EventType)>& funcCallback)
    {
        auto pScrollView = ui::ScrollView::create();
        
        pScrollView->setIgnoreAnchorPointForPosition(false);
        pScrollView->setAnchorPoint(Vec2(0.5,0.5));
        pScrollView->setBounceEnabled(true);
        pScrollView->setDirection(direction.direction);
        
        pScrollView->setContentSize(viewSize);
        pScrollView->setInnerContainerSize(containerSize);
        pScrollView->addEventListener(funcCallback);
        
        SCUITypeDef::SUIContext context;
        context.pContainerNode = pScrollView;
        context.containerType = SCUITypeDef::EContainerType::kNormal;
        
        this->insertUserNode(pScrollView, fPosX, fPosY, style);
        _contextStack.push_front(context);
        
        SC_ASSIGN_NODE(ppScrollView,pScrollView);
    }
    
    void SCSceneBuilder::containerPageView(cocos2d::ui::PageView** ppPageView,
                                        const float fPosX,
                                        const float fPosY,
                                        const SCUIArg::StringPurifier& style,
                                        const bool bHorizontal,
                                        const cocos2d::Size& size,
                                        int nPageIndex,
                                        const std::function<void(cocos2d::Ref*, cocos2d::ui::PageView::EventType)>& funcCallback)
    {
        auto pPageView = ui::PageView::create();
        pPageView->setContentSize(size);
        pPageView->setDirection(bHorizontal ? ui::PageView::Direction::HORIZONTAL
                                : ui::PageView::Direction::VERTICAL);
        pPageView->setIgnoreAnchorPointForPosition(false);
        pPageView->setAnchorPoint(Vec2(0.5,0.5));
        pPageView->addEventListener(funcCallback);
        
        nPageIndex = (nPageIndex<0) ? 0 : nPageIndex;
        
        SCUITypeDef::SUIContext context;
        context.pContainerNode = pPageView;
        context.containerType = SCUITypeDef::EContainerType::kNormal;
        context.endFunc = [nPageIndex,pPageView](SCUITypeDef::SUIContext& context)
        {
            const auto nCount = pPageView->getItems().size();
            if(nCount>nPageIndex && nCount<nPageIndex)
            {
                pPageView->setCurrentPageIndex(nPageIndex);
            }
        };
        
        this->insertUserNode(pPageView, fPosX, fPosY, style);
        _contextStack.push_front(context);
        
        SC_ASSIGN_NODE(ppPageView,pPageView);
    }
    
    void SCSceneBuilder::containerPage(cocos2d::ui::Widget** ppWidget,
                       const cocos2d::Size& size)
    {
        auto& top = _contextStack.front();
        auto pPageView = dynamic_cast<ui::PageView*>(top.pContainerNode);
        SCASSERT(pPageView!=nullptr);
        auto pWidget = ui::Widget::create();
        
        pPageView->addPage(pWidget);
        
        SCUITypeDef::SUIContext context;
        context.pContainerNode = pWidget;
        context.containerType = SCUITypeDef::EContainerType::kNormal;
        
        _contextStack.push_front(context);
        
        SC_ASSIGN_NODE(ppWidget,pWidget);
    }
    
    cocos2d::ui::EditBox* SCSceneBuilder::insertEditBox(cocos2d::ui::EditBox** ppEditBox,
                                        const float fPosX,
                                        const float fPosY,
                                        const SCUIArg::StringPurifier& style,
                                        const cocos2d::Size& size,
                                        const SCString& strImage,
                                        cocos2d::ui::EditBoxDelegate* pCallback)
    {
        auto pEditBox = cocos2d::ui::EditBox::create(size, strImage.c_str());
        pEditBox->setDelegate(pCallback);
        pEditBox->setInputMode(cocos2d::ui::EditBox::InputMode::SINGLE_LINE);
        
        this->insertUserNode(pEditBox, fPosX, fPosY, style);
        SC_ASSIGN_NODE(ppEditBox,pEditBox);
        return pEditBox;
    }
    
    ///-------------- internal methods
    MenuItemLabel* SCSceneBuilder::addButtonLabel(Label* pLabel,
                                            const float fPosX,
                                               const float fPosY,
                                               const SCUIArg::StringPurifier& style,
                                               const SCUIArg::LabelStringPurifier& labelString,
                                               SCUIArg::BehaviorPurifier bvrPurifier)
    {
        this->bindLabel(pLabel,labelString);
        auto pItemLabel = MenuItemLabel::create(pLabel);
        
        SpeedCC::SCNodeStyle::SFilterConfig scTemFilterConfig;
        scTemFilterConfig.bExclude = false;
        scTemFilterConfig.keyVtr.push_back(SC_STYLE_TEXT_COLOR);
        scTemFilterConfig.keyVtr.push_back(SC_STYLE_FONT_SIZE);
        scTemFilterConfig.keyVtr.push_back(SC_STYLE_FONT_NAME);
        scTemFilterConfig.keyVtr.push_back(SC_STYLE_TEXT);
        
        SCNodeStyle::setStyle<Label>(pLabel, style.strResult,&scTemFilterConfig);
        
        this->addButton(pItemLabel,fPosX,fPosY,style,bvrPurifier);
        return pItemLabel;
    }
    
    void SCSceneBuilder::addButton(const SCUIArg::NodePurifier& itemNode,
                   const float fPosX,
                   const float fPosY,
                   const SCUIArg::StringPurifier& style,
                   SCUIArg::BehaviorPurifier bvrPurifier)
    {
        auto pMenuItem = dynamic_cast<MenuItem*>(itemNode.ptrNodeHolder->getRef());
        
        bvrPurifier.setupBehavior(_pCurrentRefCaller,pMenuItem);
        SCNodeUtils::addClickable(pMenuItem, bvrPurifier.ptrResultBvr);
        
        this->insertUserNode(pMenuItem, fPosX, fPosY, style);
    }
    
    ///------------ layer
    
    LayerColor* SCSceneBuilder::insertLayerColor(LayerColor** ppLayer,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::StringPurifier& style,
                                              const cocos2d::Size& size,
                                              const cocos2d::Color4B& crBackground)
    {
        auto pLayer = LayerColor::create(crBackground);
        this->addLayer(pLayer,fPosX,fPosY,style,size);
        
        SC_ASSIGN_NODE(ppLayer,pLayer);
        
        return pLayer;
    }
    
    cocos2d::Layer* SCSceneBuilder::insertLayer(cocos2d::Layer** ppLayer,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const cocos2d::Size& size)
    {
        auto pLayer = Layer::create();
        this->addLayer(pLayer,fPosX,fPosY,style,size);
        SC_ASSIGN_NODE(ppLayer,pLayer);
        
        return pLayer;
    }
    
    void SCSceneBuilder::addLayer(const SCUIArg::NodePurifier& layerNode,
                               const float fPosX,
                              const float fPosY,
                              const SCUIArg::StringPurifier& style,
                              const cocos2d::Size& size)
    {
        cocos2d::Layer* pLayer = dynamic_cast<cocos2d::Layer*>(layerNode.ptrNodeHolder->getRef());
        SCASSERT(pLayer!=nullptr);
        
        pLayer->setContentSize(size);
        pLayer->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
        pLayer->setIgnoreAnchorPointForPosition(false);
        
        this->insertUserNode(layerNode, fPosX, fPosY, style);
    }
    
    void SCSceneBuilder::pushContainerStack(cocos2d::Node* pNode)
    {
        SCUITypeDef::SUIContext context;
        context.pContainerNode = pNode;
        context.containerType = SCUITypeDef::EContainerType::kNormal;
        _contextStack.push_front(context);
    }
    
}
