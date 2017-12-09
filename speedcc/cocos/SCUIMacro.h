

#ifndef __SPEEDCC__SCUIMACRO_H__
#define __SPEEDCC__SCUIMACRO_H__

namespace SpeedCC
{
    static inline void assignNode(...){}
    
    template<typename T1,typename T2>
    static inline void assignNode(T1* pNodeFrom,T2 *&pNodeTo) {pNodeTo = pNodeFrom;}
    
    static inline SCString purifyProertyString(void*) {return "";}
    static inline SCString purifyProertyString(long) {return "";}
    static inline SCString purifyProertyString(int) {return "";}
    static inline SCString purifyProertyString(const SCString& str) {return str;}
    
    static SCBehavior::Ptr purifyBehavior(cocos2d::Ref* pCall,cocos2d::SEL_CallFunc fun,cocos2d::Ref* pSender)
    {
        auto bvr = SCBehaviorCallFunc::create([pCall,fun]() -> bool
                                              {
                                                  (pCall->*fun)();
                                                  return true;
                                              });
        return bvr;
    }
    
    static SCBehavior::Ptr purifyBehavior(cocos2d::Ref* pCall,cocos2d::SEL_MenuHandler fun,cocos2d::Ref* pSender)
    {
        auto bvr = SCBehaviorCallFunc::create([pCall,fun,pSender](SCDictionary& par) -> bool
                                              {
                                                  (pCall->*fun)(pSender);
                                                  return true;
                                              });
        return bvr;
    }
    
    static SCBehavior::Ptr purifyBehavior(cocos2d::Ref* pCall,SCBehavior::Ptr bvr,cocos2d::Ref* pSender){ return bvr; }
    static SCBehavior::Ptr purifyBehavior(...){ return NULL;}
    
    
    typedef void (*FUN_SCSetProperty_t)(cocos2d::Node* pNode,const SCString& strProperty);
    
    struct SCContainerEndFunctor
    {
        cocos2d::Node*              pNode;
        SCString                    strProperty;
        FUN_SCSetProperty_t         pfunSetProperty;
        
        SCContainerEndFunctor():
        pfunSetProperty(NULL),
        pNode(NULL)
        {}
        
        virtual void operator()()
        {
            if(pNode!=NULL && pfunSetProperty!=NULL && !strProperty.isEmpty())
            {
                (*pfunSetProperty)(pNode,strProperty);
            }
        }
    };
}


///-------------- root container

#define SC_BEGIN_CONTAINER_ROOT(_node_,_x_,_y_,_property_,_size_) \
    SC_BEGIN_CONTAINER_ROOT_EX((_node_),(_x_),(_y_),(_property_),(_size_),getRootLayer())


#define SC_BEGIN_CONTAINER_ROOT_EX(_node_,_x_,_y_,_property_,_size_,_parent_)\
{\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(_parent_) \
    int sc_root_nSCContainerStackCounter = 1;\
    sc_container_pParentNode->setContentSize(_size_);\
    sc_container_pParentNode->setAnchorPoint(cocos2d::Vec2(0.5,0.5));\
    sc_container_pParentNode->setIgnoreAnchorPointForPosition(false);\
    cocos2d::Size temSize = (_size_);\
    if(temSize.width==0 || temSize.height==0) {temSize= sc_container_pParentNode->getContentSize();} \
    sc_container_pParentNode->setPosition(SCNodeUtils::posR2A(cocos2d::Vec2((_x_),(_y_)),temSize)) ; \
    assignNode(sc_container_pParentNode,(_node_));\
SCNodeProperty::setProperty<std::remove_pointer<decltype(sc_container_pParentNode)>::type>(sc_container_pParentNode,purifyProertyString((_property_)));\
    sc_container_LayoutObjectList.push_back(sc_container_pParentNode);


// end container
#define SC_END_CONTAINER \
    if(sc_container_pEndFunctor!=NULL){\
        (*sc_container_pEndFunctor)();\
        sc_container_pEndFunctor = NULL;\
    }\
    --sc_root_nSCContainerStackCounter;\
    SCASSERT(sc_root_nSCContainerStackCounter>=0);\
    if(sc_root_nSCContainerStackCounter==0){\
        sc_container_LayoutObjectList.clear();\
    }\
    sc_container_MenuItemArray.clear();\
    sc_container_pButtonListMenu = NULL;\
    sc_container_pParentNode = NULL;\
}


////------------- sprite related
// insert sprite node
#define SC_INSERT_SPRITE(_node_,_x_,_y_,_property_,_image_) \
    do{\
        ___SC_INSIDE_ADD_SPRITE(_node_,_x_,_y_,_property_,_image_)\
    }while(0);

// sprite container
#define SC_BEGIN_CONTAINER_SPRITE(_node_,_x_,_y_,_property_,_image_) \
{\
    cocos2d::Sprite* pSCContainerSprite = NULL;\
    ___SC_INSIDE_ADD_SPRITE(pSCContainerSprite,_x_,_y_,_property_,_image_) \
    assignNode(pSCContainerSprite,(_node_)); \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerSprite)

///-------------- button related
// insert image button
#define SC_INSERT_BUTTON_IMAGE(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_fun_)\
    do{\
        ___SC_INSIDE_ADD_BUTTON_IMAGE((_node_),(_x_),(_y_),(_property_),(_image_normal_),(_image_select_),(_image_disable_),_fun_) \
    }while(0);

// container image button
#define SC_BEGIN_CONTAINER_BUTTON_IMAGE(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_fun_) \
{\
    cocos2d::MenuItem* pSCContainerMenuItem = NULL;\
    ___SC_INSIDE_ADD_BUTTON_IMAGE(pSCContainerMenuItem,(_x_),(_y_),(_property_),(_image_normal_),(_image_select_),(_image_disable_),_fun_) \
    assignNode(pSCContainerMenuItem,(_node_)); \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerMenuItem)


// insert ttf button
#define SC_INSERT_BUTTON_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_fun_) \
do{\
    SCString strSCTemText = (_string_);\
    auto pSCTemLabel = cocos2d::Label::createWithTTF(strSCTemText.c_str(),(_font_),(_size_));\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_fun_))\
    }while(0);

///-------------- user node related
// insert customize Node that user created
#define SC_INSERT_USER_NODE(_node_,_x_,_y_,_property_) \
    do{\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,(_node_),(_x_),(_y_));\
        SCNodeProperty::setProperty<std::remove_pointer<decltype(_node_)>::type>((_node_),purifyProertyString((_property_)));\
    }while(0);


#define SC_BEGIN_CONTAINER_USER_NODE(_node_,_x_,_y_,_property_) \
{\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,(_node_),(_x_),(_y_));\
    SCNodeProperty::setProperty<std::remove_pointer<decltype(_node_)>::type>((_node_),purifyProertyString((_property_)));\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR((_node_))

///-------------- label related
// insert a label
#define SC_INSERT_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
    do{\
        ___SC_INSIDE_ADD_LABEL_TTF((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_))\
    }while(0);

// label container
#define SC_BEGIN_CONTAINER_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
{\
    cocos2d::Label* pSCContainerLabel = NULL; \
    ___SC_INSIDE_ADD_LABEL_TTF(pSCContainerLabel,(_x_),(_y_),(_property_),(_string_),(_font_),(_size_)) \
    assignNode(pSCContainerLabel,(_node_)); \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerLabel)

///--------------- layer related

//////////////////------------------------- inside macros ---------------------------
// below macros are used inside above macros, do not use in game

// common
#define ___SC_INSIDE_DEFINE_CONTAINER_VAR(_parent_) \
    SCContainerEndFunctor* sc_container_pEndFunctor = NULL; \
    cocos2d::Node* sc_container_pParentNode = (_parent_); \
    cocos2d::Vector<cocos2d::MenuItem*> sc_container_MenuItemArray;\
    std::list<cocos2d::Ref*>    sc_container_LayoutObjectList;\
    cocos2d::Menu* sc_container_pButtonListMenu = NULL;

#define ___SC_INSIDE_ADD_LAYOUT_NODE(_parent_,_node_,_x_,_y_) \
    cocos2d::Node* pSCTemParent = (_parent_);\
    if(pSCTemParent){\
        const cocos2d::Size& tParentSizeTem = pSCTemParent->getContentSize();\
        pSCTemParent->addChild(_node_);\
        (_node_)->setPosition(SCNodeUtils::posR2A(cocos2d::Vec2((_x_),(_y_)),tParentSizeTem)); \
    }

// sprite
#define ___SC_INSIDE_ADD_SPRITE(_node_,_x_,_y_,_property_,_image_)\
    cocos2d::Sprite* pSCTemSprite = cocos2d::Sprite::create(SCFileUtils::getFullPathFile((_image_)).c_str());\
    assignNode(pSCTemSprite,(_node_));\
    sc_container_LayoutObjectList.push_back(pSCTemSprite);\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemSprite,_x_,_y_)\
    SCNodeProperty::setProperty<cocos2d::Sprite>(pSCTemSprite,purifyProertyString((_property_)));

// label
#define ___SC_INSIDE_ADD_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_) \
    SCString strSCTemText = (_string_);\
    auto pSCTemLabel = cocos2d::Label::createWithTTF(strSCTemText.c_str(),(_font_),(_size_));\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemLabel,(_x_),(_y_));\
    assignNode(pSCTemLabel,(_node_));\
    SCNodeProperty::setProperty<std::remove_pointer<decltype(pSCTemLabel)>::type>(pSCTemLabel,purifyProertyString((_property_)));\
    sc_container_LayoutObjectList.push_back(pSCTemLabel);\

// button
#define ___SC_INSIDE_ADD_BUTTON_IMAGE(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_fun_) \
    cocos2d::Sprite* pSCTemSprite[3] = {NULL};\
    pSCTemSprite[0] = cocos2d::Sprite::create(SCFileUtils::getFullPathFile(_image_normal_).c_str());\
    pSCTemSprite[1] = cocos2d::Sprite::create(SCFileUtils::getFullPathFile(_image_select_).c_str());\
    pSCTemSprite[2] = cocos2d::Sprite::create(SCFileUtils::getFullPathFile(_image_disable_).c_str());\
    cocos2d::MenuItemSprite* pSCItemImage = cocos2d::MenuItemSprite::create(pSCTemSprite[0],pSCTemSprite[1],pSCTemSprite[2],\
[this](cocos2d::Ref* pSender) { this->onSCMenuItemPressed(pSender);}); \
    if(!sc_container_MenuItemArray.empty()){\
        sc_container_MenuItemArray.pushBack(pSCItemImage);\
    }else if(sc_container_pButtonListMenu!=NULL){\
        sc_container_pButtonListMenu->addChild(pSCItemImage);\
    }else{\
        cocos2d::Menu* pMenu = cocos2d::Menu::create(pSCItemImage,NULL);\
        pMenu->setContentSize(pSCTemSprite[0]->getContentSize());\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pMenu,(_x_),(_y_));\
        SCNodeProperty::setProperty<cocos2d::Menu>(pMenu,purifyProertyString((_property_)));\
    }\
    _buttonItem2InfoMap[pSCItemImage] = purifyBehavior(this,(_fun_),pSCItemImage);\
    assignNode(pSCItemImage,(_node_));\
    SCNodeProperty::setProperty<cocos2d::MenuItemSprite>(pSCItemImage,purifyProertyString((_property_)));\
    sc_container_LayoutObjectList.push_back(pSCItemImage);

// button label
#define ___SC_INSIDE_ADD_BUTTON_LABEL(_node_,_x_,_y_,_property_,_label_,_fun_)\
    cocos2d::MenuItemLabel* pSCTemItemLabel = cocos2d::MenuItemLabel::create((_label_),\
    [this](cocos2d::Ref* pSender) { this->onSCMenuItemPressed(pSender);}); \
    if(!sc_container_MenuItemArray.empty()){\
        sc_container_MenuItemArray.pushBack(pSCTemItemLabel);\
    }else if(sc_container_pButtonListMenu!=NULL){\
        sc_container_pButtonListMenu->addChild(pSCTemItemLabel);\
    }else{\
        cocos2d::Menu* pMenu = cocos2d::Menu::create(pSCTemItemLabel,NULL) ;\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pMenu,(_x_),(_y_));\
        SCNodeProperty::setProperty<cocos2d::Menu>(pMenu,purifyProertyString((_property_)));\
    }\
    _buttonItem2InfoMap[pSCTemItemLabel] = purifyBehavior(this,(_fun_),pSCTemItemLabel);\
    assignNode(pSCTemItemLabel,(_node_));\
    SCNodeProperty::setProperty<cocos2d::MenuItemLabel>(pSCTemItemLabel,purifyProertyString((_property_)));\
    sc_container_LayoutObjectList.push_back(pSCTemItemLabel);


#endif // __SPEEDCC__SCUIMACRO_H__
