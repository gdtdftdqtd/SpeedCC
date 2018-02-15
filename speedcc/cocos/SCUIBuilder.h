//
//  SCUIBuilder.hpp
//  libspeedcc
//
//  Created by Kevin on 21/1/2018.
//  Copyright © 2018 speedcc. All rights reserved.
//

#ifndef __SPEEDCC__SCUIBUILDER_H__
#define __SPEEDCC__SCUIBUILDER_H__

#include "../base/SCObject.h"
#include "SCUIArg.h"
#include "ui/CocosGUI.h"

namespace SpeedCC
{
    class SCSceneController;
    
    class SCUIBuilder : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCUIBuilder)
        SC_DEFINE_CLASS_PTR(SCUIBuilder)
        
        SC_DEFINE_CREATE_FUNC_0(SCUIBuilder)
        SC_DEFINE_CREATE_FUNC_1(SCUIBuilder,cocos2d::Node*)
        SC_DEFINE_CREATE_FUNC_2(SCUIBuilder,cocos2d::Node*,cocos2d::Ref*)
        
        ///------------- root container
        void beginContainerRoot(const float fPosX,
                                const float fPosY,
                                const SCUIArg::StringPurifier& style,
                                const SCUIArg::SizePurifier& sizePurifier,
                                const SCUIArg::NodePurifier& parentNode,
                                cocos2d::Ref* pRef);
        
        void pushContainerStack(cocos2d::Node* pNode);
        void popContainerStack();
        
        ///------------ layer
        
        cocos2d::LayerColor* insertLayerColor(cocos2d::LayerColor** ppLayer,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::StringPurifier& style,
                                              const cocos2d::Size& size,
                                              const cocos2d::Color4B& crBackground);
        
        cocos2d::Layer* insertLayer(cocos2d::Layer** ppLayer,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style,
                                    const cocos2d::Size& size);
        
        ///-------------- user node
        void insertUserNode(const SCUIArg::NodePurifier& userNode,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::StringPurifier& style);
        
        ///-------------- sprite
        cocos2d::Sprite* insertSprite(cocos2d::Sprite** ppSprite,
                                      const float fPosX,
                                      const float fPosY,
                                      const SCUIArg::StringPurifier& style,
                                      const SCString& strImage);
        
        ///--------------- label
        
        cocos2d::Label* insertLabel(cocos2d::Label** ppLabel,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::StringPurifier& style,
                                    const SCUIArg::LabelStringPurifier& labelString,
                                    const SCString& strFont,
                                    const float fFontSize);
        
        cocos2d::Label* insertLabelTTF(cocos2d::Label** ppLabel,
                                       const float fPosX,
                                       const float fPosY,
                                       const SCUIArg::StringPurifier& style,
                                       const SCUIArg::LabelStringPurifier& labelString,
                                       const SCString& strFont,
                                       const float fFontSize);
        
        cocos2d::Label* insertLabelBMFont(cocos2d::Label** ppLabel,
                                          const float fPosX,
                                          const float fPosY,
                                          const SCUIArg::StringPurifier& style,
                                          const SCUIArg::LabelStringPurifier& labelString,
                                          const SCString& strFile);
        
        
        ///-------------- button
        cocos2d::MenuItemSprite* insertButton(cocos2d::MenuItemSprite** ppMenuItemSprite,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::StringPurifier& style,
                                              const SCString& strImageNormal,
                                              const SCString& strSelect,
                                              const SCString& strDisable,
                                              SCUIArg::BehaviorPurifier bvrPurifier);
        
        cocos2d::MenuItemLabel* insertButtonLabel(cocos2d::MenuItemLabel** ppMenuItemLabel,
                                                  const float fPosX,
                                                  const float fPosY,
                                                  const SCUIArg::StringPurifier& style,
                                                  const SCUIArg::LabelStringPurifier& labelString,
                                                  const SCString& strFont,
                                                  const float fFontSize,
                                                  SCUIArg::BehaviorPurifier bvrPurifier);
        
        cocos2d::MenuItemLabel* insertButtonLabelTTF(cocos2d::MenuItemLabel** ppMenuItemLabel,
                                                     const float fPosX,
                                                     const float fPosY,
                                                     const SCUIArg::StringPurifier& style,
                                                     const SCUIArg::LabelStringPurifier& labelString,
                                                     const SCString& strFont,
                                                     const float fFontSize,
                                                     SCUIArg::BehaviorPurifier bvrPurifier);
        
        
        cocos2d::MenuItemLabel* insertButtonLabelBMFont(cocos2d::MenuItemLabel** ppMenuItemLabel,
                                                        const float fPosX,
                                                        const float fPosY,
                                                        const SCUIArg::StringPurifier& style,
                                                        const SCUIArg::LabelStringPurifier& labelString,
                                                        const SCString& strFile,
                                                        SCUIArg::BehaviorPurifier bvrPurifier);
        
        cocos2d::MenuItemToggle* insertButtonSwitch(cocos2d::MenuItemToggle** ppMenuItemToggle,
                                                    const float fPosX,
                                                    const float fPosY,
                                                    const SCUIArg::StringPurifier& style,
                                                    const SCUIArg::MenuItemPurifier& itemOn,
                                                    const SCUIArg::MenuItemPurifier& itemOff,
                                                    const SCUIArg::BoolPurifier& value,
                                                    SCUIArg::BehaviorPurifier bvrPurifier);
        
        
        cocos2d::ProgressTimer* insertProgressBar(cocos2d::ProgressTimer** ppProgress,
                                                  const float fPosX,
                                                  const float fPosY,
                                                  const SCUIArg::StringPurifier& style,
                                                  const SCString& strBackgroundImage,
                                                  const SCString& strFrontgroundImage,
                                                  SCUIArg::NumberPurifier value,
                                                  const bool bHorizontal,
                                                  const bool bBaseLB = true);
        
        cocos2d::ProgressTimer* insertProgressRadial(cocos2d::ProgressTimer** ppProgress,
                                                     const float fPosX,
                                                     const float fPosY,
                                                     const SCUIArg::StringPurifier& style,
                                                     const SCString& strBackgroundImage,
                                                     const SCString& strFrontgroundImage,
                                                     SCUIArg::NumberPurifier value,
                                                     const bool bCCW);
        
        void containerAlignment(cocos2d::Node** ppNode,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::StringPurifier& style,
                                              const bool bHorizontal,
                                              const float fPadding,
                                              const int nDock);
        
        
        ///---------------- cocos2d-x extension UI
        void containerScrollView(cocos2d::ui::ScrollView** ppScrollView,
                                 const float fPosX,
                                 const float fPosY,
                                 const SCUIArg::StringPurifier& style,
                                 const bool bHorizontal,
                                 const cocos2d::Size& viewSize,
                                 const cocos2d::Size& containerSize,
                                 const std::function<void(cocos2d::Ref*, cocos2d::ui::ScrollView::EventType)>& cbFunc);
        
    protected:
        SCUIBuilder():
        _pCurrentBedNode(NULL),
        _pCurrentRefCaller(NULL),
        _pDefaultBedNode(NULL),
        _pDefaultRefCaller(NULL)
        {
        }
        
        SCUIBuilder(cocos2d::Node* pBedNode,cocos2d::Ref* pRef):
        _pCurrentBedNode(NULL),
        _pCurrentRefCaller(NULL),
        _pDefaultBedNode(pBedNode),
        _pDefaultRefCaller(pRef)
        {
        }
        
        SCUIBuilder(cocos2d::Node* pBedNode):
        _pCurrentBedNode(NULL),
        _pCurrentRefCaller(NULL),
        _pDefaultBedNode(pBedNode),
        _pDefaultRefCaller(NULL)
        {
        }
        
    private:
        void addLayer(const SCUIArg::NodePurifier& layerNode,
                      const float fPosX,
                      const float fPosY,
                      const SCUIArg::StringPurifier& style,
                      const cocos2d::Size& size);
        
        void addLabel(const SCUIArg::NodePurifier& labelNode,
                      const float fPosX,
                      const float fPosY,
                      const SCUIArg::StringPurifier& style,
                      const SCUIArg::LabelStringPurifier& labelString);
        
        void addButton(const SCUIArg::NodePurifier& itemNode,
                       const float fPosX,
                       const float fPosY,
                       const SCUIArg::StringPurifier& style,
                       SCUIArg::BehaviorPurifier bvrPurifier);
        
        cocos2d::MenuItemLabel* addButtonLabel(cocos2d::Label* pLabel,
                                               const float fPosX,
                                               const float fPosY,
                                               const SCUIArg::StringPurifier& style,
                                               const SCUIArg::LabelStringPurifier& labelString,
                                               SCUIArg::BehaviorPurifier bvrPurifier);
        
        void bindLabel(const SCUIArg::NodePurifier& labelNode,
                       const SCUIArg::LabelStringPurifier& labelString);
        
    private:
        cocos2d::Node*                          _pCurrentBedNode;
        cocos2d::Ref*                           _pCurrentRefCaller;
        
        cocos2d::Node*                          _pDefaultBedNode;
        cocos2d::Ref*                           _pDefaultRefCaller;
        std::list<SCUITypeDef::SUIContext>          _contextStack;
    };
}

#endif // __SPEEDCC__SCUIBUILDER_H__

