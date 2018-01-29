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
                                 const SCUIArg::StringPurifier& property,
                                 const cocos2d::Size& size,
                                 const SCUIArg::NodePurifier& parentNode,
                                 cocos2d::Ref* pRef)
    {
        _pCurrentRefCaller = pRef;
        _pCurrentBedNode = parentNode.pNode;
        SCASSERT(_pCurrentBedNode!=NULL);
        SCASSERT(_pCurrentRefCaller!=NULL);
        
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
        
        parentNode.pfunSetProperty(parentNode.pNode,property.strResult,NULL);
        
        this->pushContainerStack(parentNode.pNode);
    }
    
    void SCUIBuilder::popContainerStack()
    {
        SCASSERT(!_contextStack.empty());
        auto& front = _contextStack.front();
        
        if(front.pfunEndFunctor!=NULL)
        {
            (*front.pfunEndFunctor)();
        }
        
        _contextStack.pop_front();
        
        if(_contextStack.empty())
        {// build ui finished.
            
        }
    }
    
    ///------------ user node
    void SCUIBuilder::insertUsertNode(const SCUIArg::NodePurifier& userNode,
                                     const float fPosX,
                                     const float fPosY,
                                     const SCUIArg::StringPurifier& property)
    {
        SCASSERT(userNode.pNode!=NULL);
        _contextStack.front().pContainerNode->addChild(userNode.pNode);
        SCNodeUtils::setPerPosition(userNode.pNode, Vec2(fPosX,fPosY));
        userNode.pfunSetProperty(userNode.pNode,property.strResult,NULL);
    }
    
    ///---------------- sprite
    cocos2d::Sprite* SCUIBuilder::insertSprite(cocos2d::Sprite** ppSprite,
                                  const float fPosX,
                                  const float fPosY,
                                  const SCUIArg::StringPurifier& property,
                                  const SCString& strImage)
    {
        auto pSprite = cocos2d::Sprite::create(SCFileUtils::getFullPathFile(strImage).c_str());
        this->insertUsertNode(pSprite,fPosX,fPosY,property);
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
        this->insertUsertNode(labelNode, fPosX, fPosY, property);
    }
    
    void SCUIBuilder::bindLabel(const SCUIArg::NodePurifier& labelNode,
                   const SCUIArg::LabelStringPurifier& labelString)
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
                                                const SCString& strImageOn,
                                                const SCString& strImageOff,
                                                const SCUIArg::BoolPurifier& value,
                                                SCUIArg::BehaviorPurifier bvrPurifier)
    {
        auto& context = _contextStack.front();
        context.menuItemVtr.push_back(NULL);
        
        MenuItemImage* pItemSprite[2] = {NULL};
        
        for(int i=0; i<2; ++i)
        {
            SCString strImage = i==0 ? strImageOn : strImageOff;
            pItemSprite[i] = MenuItemImage::create(strImage.c_str(),strImage.c_str(),strImage.c_str());
            
            bvrPurifier.setupBehavior(_pCurrentRefCaller,pItemSprite[i]);
            
            SpeedCC::SCNodeProperty::SFilterConfig scTemFilterConfig;
            scTemFilterConfig.bExclude = true;
            scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_IMAGE);
            scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_SCALE_Y);
            scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_SCALE_X);
            scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_SCALE);
            
            SCNodeProperty::setProperty<MenuItemImage>(pItemSprite[i], property.strResult,&scTemFilterConfig);
        }
        
        auto scCallbackFunc = [this](cocos2d::Ref* pSender) { this->onSCMenuItemPressed(pSender);};
        auto pSCInsideToggleItem = MenuItemToggle::createWithCallback(NULL,pItemSprite[0],pItemSprite[1],NULL);
        pSCInsideToggleItem->setSelectedIndex(value.bResult ? 0 : 1);
        
        if(value.ptrWatch!=NULL)
        {
            auto ptrLabelBinder = SCBinderUISwitch::create();
            
            ptrLabelBinder->setWatch(value.ptrWatch);
            ptrLabelBinder->setToggle(pSCInsideToggleItem);
            ptrLabelBinder->setCallback(scCallbackFunc);
            this->storeBinder(pSCInsideToggleItem,ptrLabelBinder);
        }
        else
        {
            pSCInsideToggleItem->setCallback(scCallbackFunc);
        }
        
        cocos2d::Menu* pMenu = cocos2d::Menu::create(pSCInsideToggleItem,NULL);
        pMenu->setContentSize(pItemSprite[0]->getContentSize());
        this->insertUsertNode(pMenu, fPosX, fPosY, property);
        
        bvrPurifier.setupBehavior(_pCurrentRefCaller, pSCInsideToggleItem);
        _buttonItem2InfoMap[pSCInsideToggleItem] = bvrPurifier.ptrResultBvr;
        
        SC_ASSIGN_NODE(ppMenuItemToggle,pSCInsideToggleItem);
        
        return pSCInsideToggleItem;
    }

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
        
        this->addButton(pItemLabel,fPosX,fPosY,property,bvrPurifier);
        return pItemLabel;
    }
    
    void SCUIBuilder::addButton(const SCUIArg::NodePurifier& itemNode,
                   const float fPosX,
                   const float fPosY,
                   const SCUIArg::StringPurifier& property,
                   SCUIArg::BehaviorPurifier bvrPurifier)
    {
        auto pMenuItem = dynamic_cast<MenuItem*>(itemNode.pNode);
        auto& context = _contextStack.front();
        
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
        
        bvrPurifier.setupBehavior(_pCurrentRefCaller,pMenuItem);
        
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
            
            SCDictionary dic  = {MSG_KEY_CCREF,pSender};
            
            SCMsgDisp()->postMessage(SCID::Msg::kSCMsgButtonClicked, dic);
        }
    }
    
}
