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

namespace SpeedCC
{
    class SCSceneController;
    
    class SCUIBuilder : public SCObject
    {
    public:
        SC_AVOID_CLASS_COPY(SCUIBuilder)
        SC_DEFINE_CLASS_PTR(SCUIBuilder)
        
        SC_DEFINE_CREATE_FUNC_1(SCUIBuilder,cocos2d::Node*)
        SC_DEFINE_CREATE_FUNC_2(SCUIBuilder,cocos2d::Node*,cocos2d::Ref*)
        
        ///------------- root container
        void beginContainerRoot(const float fPosX,
                                const float fPosY,
                                const SCUIArg::PurifyString& property,
                                const cocos2d::Size& size);
        
        void beginContainerRootEx(const float fPosX,
                                     const float fPosY,
                                     const SCUIArg::PurifyString& property,
                                     const cocos2d::Size& size,
                                     const SCUIArg::PurifyNode& parentNode,
                                    cocos2d::Ref* pRef);
        void endContainer();
        
        ///------------ layer
        void beginContainerLayerColor(cocos2d::LayerColor** ppLayer,
                                      const float fPosX,
                                      const float fPosY,
                                      const SCUIArg::PurifyString& property,
                                      const cocos2d::Size& size,
                                      const cocos2d::Color4B& crBackground);
        
        cocos2d::LayerColor* insertLayerColor(cocos2d::LayerColor** ppLayer,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::PurifyString& property,
                                              const cocos2d::Size& size,
                                              const cocos2d::Color4B& crBackground);
        
        void beginContainerLayer(cocos2d::Layer** ppLayer,
                         const float fPosX,
                         const float fPosY,
                         const SCUIArg::PurifyString& property,
                         const cocos2d::Size& size);
        
        cocos2d::Layer* insertLayer(cocos2d::Layer** ppLayer,
                                  const float fPosX,
                                  const float fPosY,
                                  const SCUIArg::PurifyString& property,
                                  const cocos2d::Size& size);
        
        ///-------------- user node
        void insertUsertNode(const SCUIArg::PurifyNode& userNode,
                             const float fPosX,
                             const float fPosY,
                             const SCUIArg::PurifyString& property);
        
        void beginContainerUsertNode(const SCUIArg::PurifyNode& userNode,
                                     const float fPosX,
                                     const float fPosY,
                                     const SCUIArg::PurifyString& property);
        
        ///-------------- sprite
        cocos2d::Sprite* insertSprite(cocos2d::Sprite** ppSprite,
                                      const float fPosX,
                                      const float fPosY,
                                      const SCUIArg::PurifyString& property,
                                      const SCString& strImage);
        
        void beginContainerSprite(cocos2d::Sprite** ppSprite,
                                     const float fPosX,
                                     const float fPosY,
                                     const SCUIArg::PurifyString& property,
                                     const SCString& strImage);
        
        ///--------------- label
        
        cocos2d::Label* insertLabel(cocos2d::Label** ppLabel,
                                    const float fPosX,
                                    const float fPosY,
                                    const SCUIArg::PurifyString& property,
                                    const SCUIArg::PurifyLabelString& labelString,
                                    const SCString& strFont,
                                    const float fFontSize);
        
        void beginContainerLabel(cocos2d::Label** ppLabel,
                                     const float fPosX,
                                     const float fPosY,
                                     const SCUIArg::PurifyString& property,
                                     const SCUIArg::PurifyLabelString& labelString,
                                     const SCString& strFont,
                                     const float fFontSize);
        
        cocos2d::Label* insertLabelTTF(cocos2d::Label** ppLabel,
                                       const float fPosX,
                                       const float fPosY,
                                       const SCUIArg::PurifyString& property,
                                       const SCUIArg::PurifyLabelString& labelString,
                                       const SCString& strFont,
                                       const float fFontSize);
        
        void beginContainerLabelTTF(cocos2d::Label** ppLabel,
                                 const float fPosX,
                                 const float fPosY,
                                 const SCUIArg::PurifyString& property,
                                 const SCUIArg::PurifyLabelString& labelString,
                                 const SCString& strFont,
                                 const float fFontSize);
        
        cocos2d::Label* insertLabelBMFont(cocos2d::Label** ppLabel,
                                       const float fPosX,
                                       const float fPosY,
                                       const SCUIArg::PurifyString& property,
                                       const SCUIArg::PurifyLabelString& labelString,
                                       const SCString& strFile);
        
        void beginContainerLabelBMFont(cocos2d::Label** ppLabel,
                                          const float fPosX,
                                          const float fPosY,
                                          const SCUIArg::PurifyString& property,
                                          const SCUIArg::PurifyLabelString& labelString,
                                          const SCString& strFile);
        
        ///-------------- button
        cocos2d::MenuItemSprite* insertButton(cocos2d::MenuItemSprite** ppMenuItemSprite,
                                              const float fPosX,
                                              const float fPosY,
                                              const SCUIArg::PurifyString& property,
                                              const SCString& strImageNormal,
                                              const SCString& strSelect,
                                              const SCString& strDisable,
                                            SCUIArg::PurifyBehavior bvrPurfier);
        
        void beginContainerButton(cocos2d::MenuItemSprite** ppMenuItemSprite,
                                  const float fPosX,
                                  const float fPosY,
                                  const SCUIArg::PurifyString& property,
                                  const SCString& strImageNormal,
                                  const SCString& strSelect,
                                  const SCString& strDisable,
                                  SCUIArg::PurifyBehavior bvrPurfier);
        
        cocos2d::MenuItemLabel* insertButtonLabel(cocos2d::MenuItemLabel** ppMenuItemLabel,
                                          const float fPosX,
                                          const float fPosY,
                                          const SCUIArg::PurifyString& property,
                                          const SCUIArg::PurifyLabelString& labelString,
                                          const SCString& strFont,
                                          const float fFontSize,
                                          SCUIArg::PurifyBehavior bvrPurfier);
        
        void beginContainerButtonLabel(cocos2d::MenuItemLabel** ppMenuItemLabel,
                                                  const float fPosX,
                                                  const float fPosY,
                                                  const SCUIArg::PurifyString& property,
                                                  const SCUIArg::PurifyLabelString& labelString,
                                                  const SCString& strFont,
                                                  const float fFontSize,
                                                  SCUIArg::PurifyBehavior bvrPurfier);
        
        cocos2d::Node* getLayoutNode(const int nID);
        void storeLayoutNode(const int nID,cocos2d::Node* pNode);
        void storeBinder(cocos2d::Ref* pObj,SCBinder::Ptr ptrBinder);
        SCBinder::Ptr getBinder(cocos2d::Ref* pObj) const;
        
    protected:
        SCUIBuilder(cocos2d::Node* pBedNode,cocos2d::Ref* pRef):
        _pBedNode(pBedNode),
        _pRefCaller(pRef)
        {
        }
        
        SCUIBuilder(cocos2d::Node* pBedNode):
        _pBedNode(pBedNode),
        _pRefCaller(NULL)
        {
        }
        
        void onSCMenuItemPressed(cocos2d::Ref* pSender);
        
    private:
        void addLayer(const SCUIArg::PurifyNode& layerNode,
                      const float fPosX,
                      const float fPosY,
                      const SCUIArg::PurifyString& property,
                      const cocos2d::Size& size);
        
        void addLabel(const SCUIArg::PurifyNode& labelNode,
                      const float fPosX,
                      const float fPosY,
                      const SCUIArg::PurifyString& property,
                      const SCUIArg::PurifyLabelString& labelString);
        
        void addButton(const SCUIArg::PurifyNode& itemNode,
                      const float fPosX,
                      const float fPosY,
                      const SCUIArg::PurifyString& property,
                      SCUIArg::PurifyBehavior bvrPurifier);
        
        cocos2d::MenuItemLabel* addButtonLabel(cocos2d::Label* pLabel,
                            const float fPosX,
                            const float fPosY,
                            const SCUIArg::PurifyString& property,
                                               const SCUIArg::PurifyLabelString& labelString,
                            SCUIArg::PurifyBehavior bvrPurifier);
        
        void bindLabel(const SCUIArg::PurifyNode& labelNode,
                       const SCUIArg::PurifyLabelString& labelString);
        void pushContainerStack(cocos2d::Node* pNode);
        
    private:
        cocos2d::Node*                          _pBedNode;
        cocos2d::Ref*                           _pRefCaller;
        std::stack<SCUITypeDef::SUIContext>          _contextStack;
        
        std::map<int,cocos2d::Node*>                _id2NodeMap;
        std::map<cocos2d::Ref*,SCBinder::Ptr>       _ref2BinderMap;
        std::map<cocos2d::Ref*,SCBehavior::Ptr>         _buttonItem2InfoMap;
    };
}

#endif // __SPEEDCC__SCUIBUILDER_H__
