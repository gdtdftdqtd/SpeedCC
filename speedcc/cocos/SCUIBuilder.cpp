//
//  SCUIBuilder.cpp
//  libspeedcc
//
//  Created by Kevin on 21/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#include "SCUIBuilder.h"
#include "SCSceneController.h"
#include "SCNodeUtils.h"

#include "../component/SCMessageDispatch.h"
#include "../component/SCComponentMacroDef.h"

#include "../system/SCFileUtils.h"
#include "../system/SCSystem.h"

using namespace cocos2d;

namespace SpeedCC
{
#define SC_ASSIGN_NODE(_to_,_from_) \
    do{ if((_to_)!=NULL) { (*(_to_)) = (_from_); }} while(0)
    
    ///------------ root container

    void SCUIBuilder::beginContainerRoot(const float fPosX,
                                 const float fPosY,
                                 const SCUIArg::StringPurifier& property,
                                 const SCUIArg::SizePurifier& sizePurifier,
                                 const SCUIArg::NodePurifier& parentNode,
                                 cocos2d::Ref* pRef)
    {
        Node* pParentNode = dynamic_cast<Node*>(parentNode.ptrNodeHolder->getRef());
        SCASSERT(pParentNode!=NULL);
        _pCurrentRefCaller = pRef;
        _pCurrentBedNode = pParentNode;
        SCASSERT(_pCurrentBedNode!=NULL);
        SCASSERT(_pCurrentRefCaller!=NULL);
        
        cocos2d::Size size = (sizePurifier.size.equals(Size::ZERO)) ?
        pParentNode->getContentSize() : sizePurifier.size;
        
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
        
        parentNode.pfunSetProperty(pParentNode,property.strResult,NULL);
        
        this->pushContainerStack(pParentNode);
    }
    
    void SCUIBuilder::popContainerStack()
    {
        SCASSERT(!_contextStack.empty());
        auto& front = _contextStack.front();
        
        if(front.endFunc!=NULL)
        {
            front.endFunc(front);
        }
        
        _contextStack.pop_front();
    }
    
    ///------------ user node
    void SCUIBuilder::insertUserNode(const SCUIArg::NodePurifier& userNode,
                                     const float fPosX,
                                     const float fPosY,
                                     const SCUIArg::StringPurifier& property)
    {
        Node* pNode = dynamic_cast<Node*>(userNode.ptrNodeHolder->getRef());
        SCASSERT(pNode!=NULL);
        auto& top = _contextStack.front();
        top.pContainerNode->addChild(pNode);
        SCNodeUtils::setPerPosition(pNode, Vec2(fPosX,fPosY));
        
        if(top.containerType==SCUITypeDef::EContainerType::kLayoutPadding)
        {// for padding layout container, all of children position are ignored
        // it's position is handled by layout container while container context pops.
            SCNodeProperty::SFilterConfig config;
            config.setupPosition(true);
            userNode.pfunSetProperty(pNode,property.strResult,&config);
        }
        else
        {
            userNode.pfunSetProperty(pNode,property.strResult,NULL);
        }
        
    }
    
    ///---------------- sprite
    cocos2d::Sprite* SCUIBuilder::insertSprite(cocos2d::Sprite** ppSprite,
                                  const float fPosX,
                                  const float fPosY,
                                  const SCUIArg::StringPurifier& property,
                                  const SCString& strImage)
    {
        auto pSprite = cocos2d::Sprite::create(SCFileUtils::getFullPathFile(strImage).c_str());
        this->insertUserNode(pSprite,fPosX,fPosY,property);
        SC_ASSIGN_NODE(ppSprite,pSprite);
        return pSprite;
    }
    
    ///------------ label
    
    Label* SCUIBuilder::insertLabel(cocos2d::Label** ppLabel,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& property,
                                const SCUIArg::LabelStringPurifier& labelString,
                                const SCString& strFont,
                                const float fFontSize)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithSystemFont(strLabelText.c_str(),strFont.c_str(),fFontSize);
        this->addLabel(pLabel,fPosX,fPosY,property,labelString);
        SC_ASSIGN_NODE(ppLabel,pLabel);
        return pLabel;
    }
    
    Label* SCUIBuilder::insertLabelTTF(cocos2d::Label** ppLabel,
                                   const float fPosX,
                                   const float fPosY,
                                   const SCUIArg::StringPurifier& property,
                                   const SCUIArg::LabelStringPurifier& labelString,
                                   const SCString& strFont,
                                   const float fFontSize)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithTTF(strLabelText.c_str(),strFont.c_str(),fFontSize);
        this->addLabel(pLabel,fPosX,fPosY,property,labelString);
        SC_ASSIGN_NODE(ppLabel,pLabel);
        return pLabel;
    }
    
    cocos2d::Label* SCUIBuilder::insertLabelBMFont(cocos2d::Label** ppLabel,
                                      const float fPosX,
                                      const float fPosY,
                                      const SCUIArg::StringPurifier& property,
                                      const SCUIArg::LabelStringPurifier& labelString,
                                      const SCString& strFile)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithBMFont(strFile.c_str(),strLabelText.c_str());
        this->addLabel(pLabel,fPosX,fPosY,property,labelString);
        SC_ASSIGN_NODE(ppLabel,pLabel);
        return pLabel;
    }
    
    void SCUIBuilder::addLabel(const SCUIArg::NodePurifier& labelNode,
                               const float fPosX,
                              const float fPosY,
                              const SCUIArg::StringPurifier& property,
                              const SCUIArg::LabelStringPurifier& labelString)
    {
        this->bindLabel(labelNode,labelString);
        this->insertUserNode(labelNode, fPosX, fPosY, property);
    }
    
    void SCUIBuilder::bindLabel(const SCUIArg::NodePurifier& labelNode,
                   const SCUIArg::LabelStringPurifier& labelString)
    {
        auto ptrBinder = labelString.ptrLabelBinder;
        cocos2d::Label* pLabel = dynamic_cast<Label*>(labelNode.ptrNodeHolder->getRef());
        SCASSERT(pLabel!=NULL);
        
        if(ptrBinder!=NULL && pLabel!=NULL)
        {
            ptrBinder->setLabel(pLabel);
            this->storeBinder(pLabel,ptrBinder);
        }
    }
    ///---------------- button
    cocos2d::MenuItemSprite* SCUIBuilder::insertButton(cocos2d::MenuItemSprite** ppMenuItemSprite,
                                                      const float fPosX,
                                                      const float fPosY,
                                                      const SCUIArg::StringPurifier& property,
                                                      const SCString& strImageNormal,
                                                      const SCString& strSelect,
                                                      const SCString& strDisable,
                                                       SCUIArg::BehaviorPurifier bvrPurifier)
    {
        cocos2d::Sprite* pSpriteArray[3] = {NULL};
        pSpriteArray[0] = Sprite::create(SCFileUtils::getFullPathFile(strImageNormal).c_str());
        pSpriteArray[1] = Sprite::create(SCFileUtils::getFullPathFile(strSelect).c_str());
        pSpriteArray[2] = Sprite::create(SCFileUtils::getFullPathFile(strDisable).c_str());
        
        auto pItemImage = MenuItemSprite::create(pSpriteArray[0],
                                                 pSpriteArray[1],
                                                 pSpriteArray[2],
                                                 [this](cocos2d::Ref* pSender){this->onSCMenuItemPressed(pSender);});
        
        this->addButton(pItemImage,fPosX,fPosY,property,bvrPurifier);
        SC_ASSIGN_NODE(ppMenuItemSprite,pItemImage);
        
        return pItemImage;
    }
    
    MenuItemLabel* SCUIBuilder::insertButtonLabel(MenuItemLabel** ppMenuItemLabel,
                                      const float fPosX,
                                      const float fPosY,
                                      const SCUIArg::StringPurifier& property,
                                      const SCUIArg::LabelStringPurifier& labelString,
                                      const SCString& strFont,
                                      const float fFontSize,
                                      SCUIArg::BehaviorPurifier bvrPurifier)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithSystemFont(strLabelText.c_str(),strFont.c_str(),fFontSize);
        
        auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,property,labelString,bvrPurifier);
        SC_ASSIGN_NODE(ppMenuItemLabel,ret);
        return ret;
    }
    
    MenuItemLabel* SCUIBuilder::insertButtonLabelTTF(MenuItemLabel** ppMenuItemLabel,
                                                 const float fPosX,
                                                 const float fPosY,
                                                 const SCUIArg::StringPurifier& property,
                                                 const SCUIArg::LabelStringPurifier& labelString,
                                                 const SCString& strFont,
                                                 const float fFontSize,
                                                 SCUIArg::BehaviorPurifier bvrPurifier)
    {
        SCString strLabelText = labelString.strResult;
        auto pLabel = Label::createWithTTF(strLabelText.c_str(),strFont.c_str(),fFontSize);
        auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,property,labelString,bvrPurifier);
        SC_ASSIGN_NODE(ppMenuItemLabel,ret);
        return ret;
    }
    
    MenuItemLabel* SCUIBuilder::insertButtonLabelBMFont(cocos2d::MenuItemLabel** ppMenuItemLabel,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& property,
                                                    const SCUIArg::LabelStringPurifier& labelString,
                                                    const SCString& strFile,
                                                    SCUIArg::BehaviorPurifier bvrPurifier)
    {
        SCString strLabelText = labelString.strResult;
        auto pLabel = Label::createWithBMFont(strFile.c_str(),strLabelText.c_str());
        auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,property,labelString,bvrPurifier);
        SC_ASSIGN_NODE(ppMenuItemLabel,ret);
        return ret;
    }
    
    MenuItemToggle* SCUIBuilder::insertButtonSwitch(MenuItemToggle** ppMenuItemToggle,
                                                const float fPosX,
                                                const float fPosY,
                                                const SCUIArg::StringPurifier& property,
                                                const SCUIArg::MenuItemPurifier& itemOn,
                                                const SCUIArg::MenuItemPurifier& itemOff,
                                                const SCUIArg::BoolPurifier& value,
                                                SCUIArg::BehaviorPurifier bvrPurifier)
    {
        MenuItem* pOnItem = (MenuItem*)itemOn.ptrHolder->getRef();
        MenuItem* pOffItem = (MenuItem*)itemOff.ptrHolder->getRef();
        
        bvrPurifier.setupBehavior(_pCurrentRefCaller,pOnItem);
        bvrPurifier.setupBehavior(_pCurrentRefCaller,pOffItem);
        
        auto scCallbackFunc = [this](cocos2d::Ref* pSender) { this->onSCMenuItemPressed(pSender);};
        auto pToggleItem = MenuItemToggle::createWithCallback(NULL,pOnItem,pOffItem,NULL);
        pToggleItem->setSelectedIndex(value.bResult ? 0 : 1);
        
        if(value.ptrWatch!=NULL)
        {
            auto ptrLabelBinder = SCBinderUISwitch::create();
            
            ptrLabelBinder->setWatch(value.ptrWatch);
            ptrLabelBinder->setToggle(pToggleItem);
            ptrLabelBinder->setCallback(scCallbackFunc);
            this->storeBinder(pToggleItem,ptrLabelBinder);
        }
        else
        {
            pToggleItem->setCallback(scCallbackFunc);
        }
        
        cocos2d::Menu* pMenu = cocos2d::Menu::create(pToggleItem,NULL);
        pMenu->setContentSize(pOnItem->getContentSize());
//        pMenu->setIgnoreAnchorPointForPosition(false);
//        pMenu->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
//        SCNodeUtils::setPerPosition(pMenuItemArray[0], cocos2d::Vec2(0.5,0.5));
        this->insertUserNode(pMenu, fPosX, fPosY, property);
        
        bvrPurifier.setupBehavior(_pCurrentRefCaller, pToggleItem);
        _buttonItem2InfoMap[pToggleItem] = bvrPurifier.ptrResultBvr;
        
        SC_ASSIGN_NODE(ppMenuItemToggle,pToggleItem);
        
        return pToggleItem;
    }

    cocos2d::ProgressTimer* SCUIBuilder::insertProgressBar(cocos2d::ProgressTimer** ppProgress,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::StringPurifier& property,
                                              const SCString& strBackgroundImage,
                                              const SCString& strFrontgroundImage,
                                              SCUIArg::NumberPurifier value,
                                              const bool bHorizontal,
                                              const bool bDesc,
                                              const bool bBaseLB)
    {
        SCASSERT(!strFrontgroundImage.isEmpty());
        
        Sprite* pSpriteBar = Sprite::create( SCFileUtils::getFullPathFile(strFrontgroundImage).c_str());
        
        auto pProgressBar =  ProgressTimer::create(pSpriteBar);
        pProgressBar->setAnchorPoint(Vec2(0.5,0.5));
        pProgressBar->setIgnoreAnchorPointForPosition(false);
        if(bHorizontal)
        {
            pProgressBar->setBarChangeRate(Vec2(bDesc?0:1,0)) ;
            pProgressBar->setMidpoint(Vec2((bBaseLB)?0.0:1.0,0.5));
        }
        else
        {
            pProgressBar->setBarChangeRate( Vec2(0,(bDesc?0:1))) ;
            pProgressBar->setMidpoint(Vec2(0.5,(bBaseLB)?0.0:1.0));

        }

        pProgressBar->setType(ProgressTimer::Type::BAR);
        
        if(!strBackgroundImage.isEmpty())
        {
            Sprite* pSpriteBack = Sprite::create(SCFileUtils::getFullPathFile(strBackgroundImage).c_str());
            pProgressBar->addChild(pSpriteBack,-1);
            pSpriteBack->setPosition(Vec2(pSpriteBar->getContentSize().width/2,pSpriteBar->getContentSize().height/2));
        }
        
        this->insertUserNode(pProgressBar, fPosX, fPosY, property);
        
        if(value.ptrBinderProgress!=NULL)
        {
            value.ptrBinderProgress->setProgressTimer(pProgressBar);
            this->storeBinder(pProgressBar,value.ptrBinderProgress);
        }
        else
        {
            pProgressBar->setPercentage(value.nPercentage);
        }
        SC_ASSIGN_NODE(ppProgress,pProgressBar);
        
        return pProgressBar;
    }
    
    cocos2d::ProgressTimer* SCUIBuilder::insertProgressRadial(cocos2d::ProgressTimer** ppProgress,
                                                 const float fPosX,
                                                 const float fPosY,
                                                 const SCUIArg::StringPurifier& property,
                                                 const SCString& strBackgroundImage,
                                                 const SCString& strFrontgroundImage,
                                                 SCUIArg::NumberPurifier value)
    {
        SCASSERT(!strFrontgroundImage.isEmpty());
        
        Sprite* pSpriteBar = Sprite::create(SCFileUtils::getFullPathFile(strFrontgroundImage).c_str());
        
        auto pProgressBar =  ProgressTimer::create(pSpriteBar);
        pProgressBar->setType(ProgressTimer::Type::RADIAL);
        
        if(!strBackgroundImage.isEmpty())
        {
            Sprite* pSpriteBack = Sprite::create(SCFileUtils::getFullPathFile(strBackgroundImage).c_str());
            pProgressBar->addChild(pSpriteBack,-1);
        }
        
        this->insertUserNode(pProgressBar, fPosX, fPosY, property);
        
        if(value.ptrBinderProgress!=NULL)
        {
            value.ptrBinderProgress->setProgressTimer(pProgressBar);
            this->storeBinder(pProgressBar,value.ptrBinderProgress);
        }
        else
        {
            pProgressBar->setPercentage(value.nPercentage);
        }
        SC_ASSIGN_NODE(ppProgress,pProgressBar);
        
        return pProgressBar;
    }
    
    void SCUIBuilder::containerAlignment(Node** ppNode,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::StringPurifier& property,
                                              const bool bHorizontal,
                                              const float fPadding,
                                              const int nDock)
    {
        Node* pNode = Node::create();
        pNode->setIgnoreAnchorPointForPosition(false);
        pNode->setAnchorPoint(Vec2(0.5,0.5));
        
        SCString strDockProperty = SCNodeProperty::extractKey(SC_NODE_PROPERTY_DOCK, property.strResult);
        SCString strNewProperty = property.strResult;
        if(!strDockProperty.isEmpty())
        {
            strNewProperty = SCNodeProperty::removeKey(SC_NODE_PROPERTY_DOCK,property.strResult);
        }
        
        SCUITypeDef::SUIContext context;
        context.pContainerNode = pNode;
        context.containerType = SCUITypeDef::EContainerType::kLayoutPadding;
        
        context.endFunc = [bHorizontal,fPadding,nDock,strDockProperty](SCUITypeDef::SUIContext& context)
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
            
            if(!strDockProperty.isEmpty())
            {
                SCNodeProperty::setProperty<Node>(pNode, strDockProperty);
            }
        };
        
        this->insertUserNode(pNode, fPosX, fPosY, strNewProperty);
        
        _contextStack.push_front(context);
    }
    
    ///------------ internal methods
    MenuItemLabel* SCUIBuilder::addButtonLabel(Label* pLabel,
                                            const float fPosX,
                                               const float fPosY,
                                               const SCUIArg::StringPurifier& property,
                                               const SCUIArg::LabelStringPurifier& labelString,
                                               SCUIArg::BehaviorPurifier bvrPurifier)
    {
        this->bindLabel(pLabel,labelString);
        auto pItemLabel = MenuItemLabel::create(pLabel,
                                                [this](cocos2d::Ref* pSender){this->onSCMenuItemPressed(pSender);});
        
        SpeedCC::SCNodeProperty::SFilterConfig scTemFilterConfig;
        scTemFilterConfig.bExclude = false;
        scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_COLOR_TEXT);
        scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_FONT_SIZE);
        scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_FONT_NAME);
        scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_LABEL);
        
        SCNodeProperty::setProperty<Label>(pLabel, property.strResult,&scTemFilterConfig);
        
        this->addButton(pItemLabel,fPosX,fPosY,property,bvrPurifier);
        return pItemLabel;
    }
    
    void SCUIBuilder::addButton(const SCUIArg::NodePurifier& itemNode,
                   const float fPosX,
                   const float fPosY,
                   const SCUIArg::StringPurifier& property,
                   SCUIArg::BehaviorPurifier bvrPurifier)
    {
        auto pMenuItem = dynamic_cast<MenuItem*>(itemNode.ptrNodeHolder->getRef());
        
        auto pMenu = cocos2d::Menu::create(pMenuItem,NULL);
        pMenu->setIgnoreAnchorPointForPosition(false);
        pMenu->setContentSize(pMenuItem->getContentSize());
        pMenu->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
        SCNodeUtils::setPerPosition(pMenuItem, cocos2d::Vec2(0.5,0.5));
        this->insertUserNode(pMenu, fPosX, fPosY, property);
        
        bvrPurifier.setupBehavior(_pCurrentRefCaller,pMenuItem);
        
        _buttonItem2InfoMap[pMenuItem] = bvrPurifier.ptrResultBvr;
    }
    
    ///------------ layer
    
    LayerColor* SCUIBuilder::insertLayerColor(LayerColor** ppLayer,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::StringPurifier& property,
                                              const cocos2d::Size& size,
                                              const cocos2d::Color4B& crBackground)
    {
        auto pLayer = LayerColor::create(crBackground);
        this->addLayer(pLayer,fPosX,fPosY,property,size);
        
        SC_ASSIGN_NODE(ppLayer,pLayer);
        
        return pLayer;
    }
    
    cocos2d::Layer* SCUIBuilder::insertLayer(cocos2d::Layer** ppLayer,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& property,
                                const cocos2d::Size& size)
    {
        auto pLayer = Layer::create();
        this->addLayer(pLayer,fPosX,fPosY,property,size);
        SC_ASSIGN_NODE(ppLayer,pLayer);
        
        return pLayer;
    }
    
    void SCUIBuilder::addLayer(const SCUIArg::NodePurifier& layerNode,
                               const float fPosX,
                              const float fPosY,
                              const SCUIArg::StringPurifier& property,
                              const cocos2d::Size& size)
    {
        cocos2d::Layer* pLayer = dynamic_cast<cocos2d::Layer*>(layerNode.ptrNodeHolder->getRef());
        SCASSERT(pLayer!=NULL);
        
        pLayer->setContentSize(size);
        pLayer->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
        pLayer->setIgnoreAnchorPointForPosition(false);
        
        this->insertUserNode(layerNode, fPosX, fPosY, property);
    }
    
    void SCUIBuilder::pushContainerStack(cocos2d::Node* pNode)
    {
        SCUITypeDef::SUIContext context;
        context.pContainerNode = pNode;
        context.containerType = SCUITypeDef::EContainerType::kNormal;
        _contextStack.push_front(context);
    }
    
    
    cocos2d::Node* SCUIBuilder::getLayoutNode(const int nID)
    {
        SC_RETURN_IF(nID<=0, NULL);
        
        auto it = _id2NodeMap.find(nID);
        SC_RETURN_IF(it==_id2NodeMap.end(), NULL);
        
        return (*it).second;
    }
    
    void SCUIBuilder::storeLayoutNode(const int nID,cocos2d::Node* pNode)
    {
        SC_RETURN_V_IF(nID<=0 || pNode==NULL);
        
        _id2NodeMap[nID] = pNode;
    }
    
    void SCUIBuilder::storeBinder(cocos2d::Ref* pObj,SCBinder::Ptr ptrBinder)
    {
        SC_RETURN_V_IF(pObj==NULL || ptrBinder==NULL);
        
        _ref2BinderMap[pObj] = ptrBinder;
    }
    
    SCBinder::Ptr SCUIBuilder::getBinder(cocos2d::Ref* pObj) const
    {
        auto it = _ref2BinderMap.find(pObj);
        return ((it==_ref2BinderMap.end()) ? NULL : (*it).second);
    }
    
    void SCUIBuilder::onSCMenuItemPressed(cocos2d::Ref* pSender)
    {
        auto it = _buttonItem2InfoMap.find(pSender);
        
        SCASSERT(it!=_buttonItem2InfoMap.end());
        if(it!=_buttonItem2InfoMap.end() && (*it).second!=NULL)
        {
            (*it).second->execute();
            
            SCDictionary dic  = {SC_KEY_CCREF,pSender};
            SCMsgDisp()->postMessage(SCID::Msg::kSCMsgButtonClicked, dic);
        }
    }
    
}
