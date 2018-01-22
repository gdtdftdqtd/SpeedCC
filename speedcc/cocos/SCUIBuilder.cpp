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

using namespace cocos2d;

namespace SpeedCC
{
#define SC_ASSIGN_NODE(_to_,_from_) \
    do{ if((_to_)!=NULL) { (*(_to_)) = (_from_); }} while(0)
    
    ///------------ root container
    void SCUIBuilder::beginContainerRoot(const float fPosX,
                                         const float fPosY,
                                         const SCUIArg::PurifyString& property,
                                         const cocos2d::Size& size)
    {
        this->beginContainerRootEx(fPosX,fPosY,property,size,_pBedNode,_pRefCaller);
    }
    
    void SCUIBuilder::beginContainerRootEx(const float fPosX,
                                 const float fPosY,
                                 const SCUIArg::PurifyString& property,
                                 const cocos2d::Size& size,
                                 const SCUIArg::PurifyNode& parentNode,
                                 cocos2d::Ref* pRef)
    {
        _pRefCaller = pRef;
        _pBedNode = parentNode.pNode;
        SCASSERT(_pBedNode!=NULL);
        SCASSERT(_pRefCaller!=NULL);
        
        _pBedNode->setContentSize(size);
        _pBedNode->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
        _pBedNode->setIgnoreAnchorPointForPosition(false);
        
        SCNodeUtils::setPerPosition(_pBedNode, Vec2(fPosX,fPosY));
        parentNode.pfunSetProperty(parentNode.pNode,property.strResult,NULL);
        
        this->pushContainerStack(parentNode.pNode);
    }
    
    void SCUIBuilder::endContainer()
    {
        SCASSERT(!_contextStack.empty());
        auto front = _contextStack.top();
        
        if(front.pfunEndFunctor!=NULL)
        {
            (*front.pfunEndFunctor)();
        }
        
        _contextStack.pop();
        
        if(_contextStack.empty())
        {// build ui finished.
            
        }
    }
    
    ///------------ user node
    void SCUIBuilder::insertUsertNode(const SCUIArg::PurifyNode& userNode,
                                     const float fPosX,
                                     const float fPosY,
                                     const SCUIArg::PurifyString& property)
    {
        SCASSERT(userNode.pNode!=NULL);
        _contextStack.top().pContainerNode->addChild(userNode.pNode);
        SCNodeUtils::setPerPosition(userNode.pNode, Vec2(fPosX,fPosY));
        userNode.pfunSetProperty(userNode.pNode,property.strResult,NULL);
    }
    
    void SCUIBuilder::beginContainerUsertNode(const SCUIArg::PurifyNode& userNode,
                                             const float fPosX,
                                             const float fPosY,
                                             const SCUIArg::PurifyString& property)
    {
        SCASSERT(userNode.pNode!=NULL);
        this->insertUsertNode(userNode,fPosX,fPosY,property);
        this->pushContainerStack(userNode.pNode);
    }
    
    ///---------------- sprite
    cocos2d::Sprite* SCUIBuilder::insertSprite(cocos2d::Sprite** ppSprite,
                                  const float fPosX,
                                  const float fPosY,
                                  const SCUIArg::PurifyString& property,
                                  const SCString& strImage)
    {
        auto pSprite = cocos2d::Sprite::create(SCFileUtils::getFullPathFile(strImage).c_str());
        this->insertUsertNode(pSprite,fPosX,fPosY,property);
        SC_ASSIGN_NODE(ppSprite,pSprite);
        return pSprite;
    }
    
    void SCUIBuilder::beginContainerSprite(cocos2d::Sprite** ppSprite,
                             const float fPosX,
                             const float fPosY,
                             const SCUIArg::PurifyString& property,
                             const SCString& strImage)
    {
        auto pSprite = this->insertSprite(ppSprite,fPosX,fPosY,property,strImage);
        this->pushContainerStack(pSprite);
    }
    
    ///------------ label
    
    Label* SCUIBuilder::insertLabel(cocos2d::Label** ppLabel,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::PurifyString& property,
                                const SCUIArg::PurifyLabelString& labelString,
                                const SCString& strFont,
                                const float fFontSize)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithSystemFont(strLabelText.c_str(),strFont.c_str(),fFontSize);
        this->addLabel(pLabel,fPosX,fPosY,property,labelString);
        SC_ASSIGN_NODE(ppLabel,pLabel);
        return pLabel;
    }
    
    void SCUIBuilder::beginContainerLabel(cocos2d::Label** ppLabel,
                             const float fPosX,
                             const float fPosY,
                             const SCUIArg::PurifyString& property,
                             const SCUIArg::PurifyLabelString& labelString,
                             const SCString& strFont,
                             const float fFontSize)
    {
        auto label = this->insertLabel(ppLabel,fPosX,fPosY,property,labelString,strFont,fFontSize);
        this->pushContainerStack(label);
    }
    
    Label* SCUIBuilder::insertLabelTTF(cocos2d::Label** ppLabel,
                                   const float fPosX,
                                   const float fPosY,
                                   const SCUIArg::PurifyString& property,
                                   const SCUIArg::PurifyLabelString& labelString,
                                   const SCString& strFont,
                                   const float fFontSize)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithTTF(strLabelText.c_str(),strFont.c_str(),fFontSize);
        this->addLabel(pLabel,fPosX,fPosY,property,labelString);
        SC_ASSIGN_NODE(ppLabel,pLabel);
        return pLabel;
    }
    
    void SCUIBuilder::beginContainerLabelTTF(cocos2d::Label** ppLabel,
                                const float fPosX,
                                const float fPosY,
                                const SCUIArg::PurifyString& property,
                                const SCUIArg::PurifyLabelString& labelString,
                                const SCString& strFont,
                                const float fFontSize)
    {
        auto label = this->insertLabelTTF(ppLabel,fPosX,fPosY,property,labelString,strFont,fFontSize);
        this->pushContainerStack(label);
    }
    
    cocos2d::Label* SCUIBuilder::insertLabelBMFont(cocos2d::Label** ppLabel,
                                      const float fPosX,
                                      const float fPosY,
                                      const SCUIArg::PurifyString& property,
                                      const SCUIArg::PurifyLabelString& labelString,
                                      const SCString& strFile)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithBMFont(strFile.c_str(),strLabelText.c_str());
        this->addLabel(pLabel,fPosX,fPosY,property,labelString);
        SC_ASSIGN_NODE(ppLabel,pLabel);
        return pLabel;
    }
    
    void SCUIBuilder::beginContainerLabelBMFont(cocos2d::Label** ppLabel,
                                               const float fPosX,
                                               const float fPosY,
                                               const SCUIArg::PurifyString& property,
                                               const SCUIArg::PurifyLabelString& labelString,
                                               const SCString& strFile)
    {
        auto label = this->insertLabelBMFont(ppLabel,fPosX,fPosY,property,labelString,strFile);
        this->pushContainerStack(label);
    }
    
    void SCUIBuilder::addLabel(const SCUIArg::PurifyNode& labelNode,
                               const float fPosX,
                              const float fPosY,
                              const SCUIArg::PurifyString& property,
                              const SCUIArg::PurifyLabelString& labelString)
    {
        this->bindLabel(labelNode,labelString);
        this->insertUsertNode(labelNode, fPosX, fPosY, property);
    }
    
    void SCUIBuilder::bindLabel(const SCUIArg::PurifyNode& labelNode,
                   const SCUIArg::PurifyLabelString& labelString)
    {
        auto ptrBinder = labelString.ptrLabelBinder;
        cocos2d::Label* pLabel = dynamic_cast<Label*>(labelNode.pNode);
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
                                                      const SCUIArg::PurifyString& property,
                                                      const SCString& strImageNormal,
                                                      const SCString& strSelect,
                                                      const SCString& strDisable,
                                                       SCUIArg::PurifyBehavior bvrPurifier)
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
    
    void SCUIBuilder::beginContainerButton(MenuItemSprite** ppMenuItemSprite,
                                          const float fPosX,
                                          const float fPosY,
                                          const SCUIArg::PurifyString& property,
                                          const SCString& strImageNormal,
                                          const SCString& strSelect,
                                          const SCString& strDisable,
                                          SCUIArg::PurifyBehavior bvr)
    {
        auto pItem = this->insertButton(ppMenuItemSprite,fPosX,fPosY,property,strImageNormal,strSelect,strDisable,bvr);
        this->pushContainerStack(pItem);
    }
    
    MenuItemLabel* SCUIBuilder::insertButtonLabel(MenuItemLabel** ppMenuItemLabel,
                                      const float fPosX,
                                      const float fPosY,
                                      const SCUIArg::PurifyString& property,
                                      const SCUIArg::PurifyLabelString& labelString,
                                      const SCString& strFont,
                                      const float fFontSize,
                                      SCUIArg::PurifyBehavior bvrPurifier)
    {
        SCString strLabelText = labelString.strResult;
        
        auto pLabel = Label::createWithSystemFont(strLabelText.c_str(),strFont.c_str(),fFontSize);
        
        auto ret = this->addButtonLabel(pLabel,fPosX,fPosY,property,labelString,bvrPurifier);
        SC_ASSIGN_NODE(ppMenuItemLabel,ret);
        return ret;
    }
    
    void SCUIBuilder::beginContainerButtonLabel(MenuItemLabel** ppMenuItemLabel,
                                                      const float fPosX,
                                                      const float fPosY,
                                                      const SCUIArg::PurifyString& property,
                                                      const SCUIArg::PurifyLabelString& labelString,
                                                      const SCString& strFont,
                                                      const float fFontSize,
                                                      SCUIArg::PurifyBehavior bvrPurfier)
    {
        auto pItem = this->insertButtonLabel(ppMenuItemLabel,
                                             fPosX,
                                             fPosY,
                                             property,
                                             labelString,
                                             strFont,
                                             fFontSize,
                                             bvrPurfier);
        this->pushContainerStack(pItem);
    }
    
    MenuItemLabel* SCUIBuilder::addButtonLabel(Label* pLabel,
                                            const float fPosX,
                                               const float fPosY,
                                               const SCUIArg::PurifyString& property,
                                               const SCUIArg::PurifyLabelString& labelString,
                                               SCUIArg::PurifyBehavior bvrPurifier)
    {
        this->bindLabel(pLabel,labelString);
        auto pItemLabel = MenuItemLabel::create(pLabel,
                                                [this](cocos2d::Ref* pSender){this->onSCMenuItemPressed(pSender);});
        
        this->addButton(pItemLabel,fPosX,fPosY,property,bvrPurifier);
        return pItemLabel;
    }
    
    void SCUIBuilder::addButton(const SCUIArg::PurifyNode& itemNode,
                   const float fPosX,
                   const float fPosY,
                   const SCUIArg::PurifyString& property,
                   SCUIArg::PurifyBehavior bvrPurifier)
    {
        auto pMenuItem = dynamic_cast<MenuItem*>(itemNode.pNode);
        auto context = _contextStack.top();
        
        if(!context.menuItemVtr.empty())
        {
            context.menuItemVtr.push_back(pMenuItem);
        }
        else
        {
            auto pMenu = cocos2d::Menu::create(pMenuItem,NULL);
            pMenu->setContentSize(pMenuItem->getContentSize());
            this->insertUsertNode(pMenu, fPosX, fPosY, property);
        }
        
        bvrPurifier.setupBehavior(_pRefCaller,pMenuItem);
        
        _buttonItem2InfoMap[pMenuItem] = bvrPurifier.ptrResultBvr;
        
        SpeedCC::SCNodeProperty::SFilterConfig scTemFilterConfig;
        scTemFilterConfig.bExclude = true;
        scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_IMAGE);
        scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_SCALE_Y);
        scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_SCALE_X);
        scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_SCALE);

        itemNode.pfunSetProperty(pMenuItem,property.strResult,&scTemFilterConfig);
    }
    
    ///------------ layer
    void SCUIBuilder::beginContainerLayerColor(cocos2d::LayerColor** ppLayer,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::PurifyString& property,
                                              const cocos2d::Size& size,
                                              const cocos2d::Color4B& crBackground)
    {
        auto pLayer = this->insertLayerColor(ppLayer,fPosX,fPosY,property,size,crBackground);
        this->pushContainerStack(pLayer);
    }
    
    LayerColor* SCUIBuilder::insertLayerColor(LayerColor** ppLayer,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::PurifyString& property,
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
                                const SCUIArg::PurifyString& property,
                                const cocos2d::Size& size)
    {
        auto pLayer = Layer::create();
        this->addLayer(pLayer,fPosX,fPosY,property,size);
        SC_ASSIGN_NODE(ppLayer,pLayer);
        
        return pLayer;
    }
    
    void SCUIBuilder::beginContainerLayer(cocos2d::Layer** ppLayer,
                             const float fPosX,
                             const float fPosY,
                             const SCUIArg::PurifyString& property,
                             const cocos2d::Size& size)
    {
        auto pLayer = this->insertLayer(ppLayer,fPosX,fPosY,property,size);
        this->pushContainerStack(pLayer);
    }
    
    void SCUIBuilder::addLayer(const SCUIArg::PurifyNode& layerNode,
                               const float fPosX,
                              const float fPosY,
                              const SCUIArg::PurifyString& property,
                              const cocos2d::Size& size)
    {
        cocos2d::Layer* pLayer = dynamic_cast<cocos2d::Layer*>(layerNode.pNode);

        pLayer->setContentSize(size);
        pLayer->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
        pLayer->setIgnoreAnchorPointForPosition(false);
        
        this->insertUsertNode(layerNode, fPosX, fPosY, property);
    }
    
    void SCUIBuilder::pushContainerStack(cocos2d::Node* pNode)
    {
        SCUITypeDef::SUIContext context;
        context.pContainerNode = pNode;
        context.containerType = SCUITypeDef::EContainerType::kNormal;
        _contextStack.push(context);
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
        SC_RETURN_IF_V(nID<=0 || pNode==NULL);
        
        _id2NodeMap[nID] = pNode;
    }
    
    void SCUIBuilder::storeBinder(cocos2d::Ref* pObj,SCBinder::Ptr ptrBinder)
    {
        SC_RETURN_IF_V(pObj==NULL || ptrBinder==NULL);
        
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
            
            SCDictionary dic  = {MSG_KEY_CCREF,pSender};
            
            SCMsgDisp()->postMessage(SCID::Msg::kSCMsgButtonClicked, dic);
        }
    }
    
}
