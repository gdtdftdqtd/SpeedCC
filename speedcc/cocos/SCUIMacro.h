

#ifndef __SPEEDCC__SCUIMACRO_H__
#define __SPEEDCC__SCUIMACRO_H__

namespace SpeedCC
{
    class SCUISetup
    {
    public:
        static inline void assignNode(...){}
        
        template<typename T1,typename T2>
        static inline void assignNode(T1* pNodeFrom,T2 *&pNodeTo) {pNodeTo = pNodeFrom;}
        
        static inline SCString purifyString(void*) {return "";}
        static inline SCString purifyString(long) {return "";}
        static inline SCString purifyString(int) {return "";}
        static inline SCString purifyString(const SCString& str) {return str;}
        
        static inline SCString purifyLabelString(...) {return "";}
        static inline SCString purifyLabelString(SCObject::Ptr binderPtr) {return "";}
        static inline SCString purifyLabelString(void*) {return "";}
        static inline SCString purifyLabelString(const SCString& str) {return str;}
        static inline SCString purifyLabelString(long n) {return SCString(n);}
        static inline SCString purifyLabelString(int n) {return SCString(n);}
        static inline SCString purifyLabelString(float n) {return SCString(n);}
        static inline SCString purifyLabelString(double n) {return SCString(n);}
        
        static inline void bindLabel(...) {}
        static inline void bindLabel(cocos2d::Label* pLabel,...) {}
        static inline void bindLabel(cocos2d::Label* pLabel,SCBinderLabel::Ptr binderPtr)
        {
            if(binderPtr!=NULL && pLabel!=NULL)
            {
                binderPtr->setLabel(pLabel);
            }
        }
        
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
    };
    
    
    
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

// sc_container_type. 0:normal; 1:button list; 2:multiplex layer;

///-------------- root container

#define SC_BEGIN_CONTAINER_ROOT(_node_,_x_,_y_,_property_,_size_) \
    SC_BEGIN_CONTAINER_ROOT_EX((_node_),(_x_),(_y_),(_property_),(_size_),getRootLayer())

#define SC_BEGIN_CONTAINER_ROOT_EX(_node_,_x_,_y_,_property_,_size_,_parent_)\
{\
    int sc_root_nSCContainerStackCounter = 0;\
    typedef std::remove_pointer<decltype(this)>::type    sc_this_class_t;\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(_parent_) \
    sc_container_pParentNode->setContentSize(_size_);\
    sc_container_pParentNode->setAnchorPoint(cocos2d::Vec2(0.5,0.5));\
    sc_container_pParentNode->setIgnoreAnchorPointForPosition(false);\
    cocos2d::Size temSize = (_size_);\
    if(temSize.width==0 || temSize.height==0) {temSize= sc_container_pParentNode->getContentSize();} \
    sc_container_pParentNode->setPosition(SCNodeUtils::posR2A(cocos2d::Vec2((_x_),(_y_)),temSize)) ; \
    SCUISetup::assignNode(sc_container_pParentNode,(_node_));\
SCNodeProperty::setProperty<std::remove_pointer<decltype(sc_container_pParentNode)>::type>(sc_container_pParentNode,SCUISetup::purifyString((_property_)));\
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
    sc_container_MultiplexLayerArray.clear();\
    sc_container_pButtonListMenu = NULL;\
    sc_container_pParentNode = NULL;\
    sc_container_type = 0;\
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
    SCUISetup::assignNode(pSCContainerSprite,(_node_)); \
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
    SCUISetup::assignNode(pSCContainerMenuItem,(_node_)); \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerMenuItem)


// insert ttf label button
#define SC_INSERT_BUTTON_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_fun_) \
do{\
    SCString strSCTemText = SCUISetup::purifyLabelString((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithTTF(strSCTemText.c_str(),(_font_),(_size_));\
    SCUISetup::bindLabel(pSCTemLabel,(_string_));\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_fun_))\
}while(0);

// container ttf label button
#define SC_BEGIN_CONTAINER_BUTTON_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_fun_) \
{\
    SCString strSCTemText = SCUISetup::purifyLabelString((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithTTF(strSCTemText.c_str(),(_font_),(_size_));\
    SCUISetup::bindLabel(pSCTemLabel,(_string_));\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_fun_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCTemLabel)

// insert system label button
#define SC_INSERT_BUTTON_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_fun_) \
do{\
    SCString strSCTemText = SCUISetup::purifyLabelString((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithSystemFont(strSCTemText.c_str(),SCUISetup::purifyString((_font_)).c_str(),(_size_));\
    SCUISetup::bindLabel(pSCTemLabel,(_string_));\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_fun_))\
}while(0);

// container system label button
#define SC_BEGIN_CONTAINER_BUTTON_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_fun_) \
{\
    SCString strSCTemText = SCUISetup::purifyLabelString((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithSystemFont(strSCTemText.c_str(),(_font_),(_size_));\
    SCUISetup::bindLabel(pSCTemLabel,(_string_));\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_fun_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCTemLabel)

// insert bmfont label button
#define SC_INSERT_BUTTON_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_font_,_fun_) \
do{\
    SCString strSCTemText = SCUISetup::purifyLabelString((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithBMFont((_font_),strSCTemText.c_str());\
    SCUISetup::bindLabel(pSCTemLabel,(_string_));\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_fun_))\
}while(0);

// container bmfont label button
#define SC_BEGIN_CONTAINER_BUTTON_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_fun_) \
{\
    SCString strSCTemText = SCUISetup::purifyLabelString((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithBMFont((_font_),strSCTemText.c_str());\
    SCUISetup::bindLabel(pSCTemLabel,(_string_));\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_fun_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCTemLabel)


///-------------- user node related
// insert customize Node that user created
#define SC_INSERT_USER_NODE(_node_,_x_,_y_,_property_) \
    do{\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,(_node_),(_x_),(_y_));\
        SCNodeProperty::setProperty<std::remove_pointer<decltype(_node_)>::type>((_node_),SCUISetup::purifyString((_property_)));\
    }while(0);


#define SC_BEGIN_CONTAINER_USER_NODE(_node_,_x_,_y_,_property_) \
{\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,(_node_),(_x_),(_y_));\
    SCNodeProperty::setProperty<std::remove_pointer<decltype(_node_)>::type>((_node_),SCUISetup::purifyString((_property_)));\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR((_node_))

///-------------- label related

// insert a system font label
#define SC_INSERT_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
    do{\
        ___SC_INSIDE_ADD_LABEL((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_),1)\
    }while(0);

// label system font container
#define SC_BEGIN_CONTAINER_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
{\
    cocos2d::Label* pSCContainerLabel = NULL; \
    ___SC_INSIDE_ADD_LABEL(pSCContainerLabel,(_x_),(_y_),(_property_),(_string_),(_font_),(_size_),1) \
    SCUISetup::assignNode(pSCContainerLabel,(_node_)); \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerLabel)

// insert a ttf label
#define SC_INSERT_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
    do{\
        ___SC_INSIDE_ADD_LABEL((_node_),(_x_),(_y_),(_property_),(_string_),(_font_),(_size_),2)\
    }while(0);

// ttf label container
#define SC_BEGIN_CONTAINER_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_)\
{\
    cocos2d::Label* pSCContainerLabel = NULL; \
    ___SC_INSIDE_ADD_LABEL(pSCContainerLabel,(_x_),(_y_),(_property_),(_string_),(_font_),(_size_),2) \
    SCUISetup::assignNode(pSCContainerLabel,(_node_)); \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerLabel)

// insert a bmfont label
#define SC_INSERT_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_file_)\
    do{\
        ___SC_INSIDE_ADD_LABEL((_node_),(_x_),(_y_),(_property_),(_string_),(_file_),0,3)\
    }while(0);

// bmfont label container
#define SC_BEGIN_CONTAINER_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_font_)\
{\
    cocos2d::Label* pSCContainerLabel = NULL; \
    ___SC_INSIDE_ADD_LABEL(pSCContainerLabel,(_x_),(_y_),(_property_),(_string_),(_font_),0,3) \
    SCUISetup::assignNode(pSCContainerLabel,(_node_)); \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerLabel)

///--------------- layer related

// insert a layer
#define SC_INSERT_LAYER(_node_,_x_,_y_,_property_,_size_) \
do{\
    auto pSCTemLayer0 = cocos2d::Layer::create();\
    ___SC_INSIDE_ADD_LAYER((_node_),(_x_),(_y_),(_property_),pSCTemLayer0,(_size_))\
}while(0);

// layer container
#define SC_BEGIN_CONTAINER_LAYER(_node_,_x_,_y_,_property_,_size_) \
{\
    cocos2d::Layer* pSCContainerTemLayer = cocos2d::Layer::create(); \
    ___SC_INSIDE_ADD_LAYER((_node_),(_x_),(_y_),(_property_),pSCContainerTemLayer,(_size_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerTemLayer)

// insert a color layer
#define SC_INSERT_LAYER_COLOR(_node_,_x_,_y_,_property_,_size_,_color_) \
do{\
    auto pSCTemLayer0 = cocos2d::LayerColor::create((_color_));\
    ___SC_INSIDE_ADD_LAYER((_node_),(_x_),(_y_),(_property_),pSCTemLayer0,(_size_))\
}while(0);

// color layer container
#define SC_BEGIN_CONTAINER_LAYER_COLOR(_node_,_x_,_y_,_property_,_size_,_color_) \
{\
    cocos2d::Layer* pSCContainerTemLayer = cocos2d::LayerColor::create((_color_)); \
    ___SC_INSIDE_ADD_LAYER((_node_),(_x_),(_y_),(_property_),pSCContainerTemLayer,(_size_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerTemLayer)

// insert a color layer
#define SC_INSERT_LAYER_GRA(_node_,_x_,_y_,_property_,_size_,_start_color_,_end_color_,_dir_) \
do{\
    auto pSCTemLayer0 = cocos2d::LayerGradient::create((_start_color_),(_end_color_),(_dir_));\
    ___SC_INSIDE_ADD_LAYER((_node_),(_x_),(_y_),(_property_),pSCTemLayer0,(_size_))\
}while(0);

// color layer container
#define SC_BEGIN_CONTAINER_LAYER_GRA(_node_,_x_,_y_,_property_,_size_,_start_color_,_end_color_,_dir_) \
{\
    cocos2d::Layer* pSCContainerTemLayer = cocos2d::LayerGradient::create((_start_color_),(_end_color_),(_dir_)); \
    ___SC_INSIDE_ADD_LAYER((_node_),(_x_),(_y_),(_property_),pSCContainerTemLayer,(_size_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerTemLayer)

// insert a multiplex layer
#define SC_INSERT_LAYER_MUL(_node_,_x_,_y_,_property_,_size_) \
do{\
    auto pSCTemLayer0 = cocos2d::LayerMultiplex::create();\
    ___SC_INSIDE_ADD_LAYER((_node_),(_x_),(_y_),(_property_),pSCTemLayer0,(_size_))\
}while(0);

// multiplex layer container
#define SC_BEGIN_CONTAINER_LAYER_MUL(_node_,_x_,_y_,_property_,_size_) \
{\
    cocos2d::Layer* pSCContainerTemLayer = cocos2d::LayerMultiplex::create(); \
    ___SC_INSIDE_ADD_LAYER((_node_),(_x_),(_y_),(_property_),pSCContainerTemLayer,(_size_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerTemLayer)\
    sc_container_type = 2;

//////////////////------------------------- inside macros ---------------------------
// below macros are used inside above macros, do not use in game

// common
#define ___SC_INSIDE_DEFINE_CONTAINER_VAR(_parent_) \
    SCContainerEndFunctor* sc_container_pEndFunctor = NULL; \
    cocos2d::Node* sc_container_pParentNode = (_parent_); \
    cocos2d::Vector<cocos2d::MenuItem*> sc_container_MenuItemArray;\
    cocos2d::Vector<cocos2d::Layer*> sc_container_MultiplexLayerArray;\
    std::list<cocos2d::Ref*>    sc_container_LayoutObjectList;\
    cocos2d::Menu* sc_container_pButtonListMenu = NULL; \
    ++sc_root_nSCContainerStackCounter;\
    int sc_container_type = 0;

#define ___SC_INSIDE_ADD_LAYOUT_NODE(_parent_,_node_,_x_,_y_) \
    cocos2d::Node* pSCTemParent = (_parent_);\
    if(pSCTemParent){\
        const cocos2d::Size& tParentSizeTem = pSCTemParent->getContentSize();\
        pSCTemParent->addChild((_node_));\
        (_node_)->setPosition(SCNodeUtils::posR2A(cocos2d::Vec2((_x_),(_y_)),tParentSizeTem)); \
    }

// sprite
#define ___SC_INSIDE_ADD_SPRITE(_node_,_x_,_y_,_property_,_image_)\
    cocos2d::Sprite* pSCTemSprite = cocos2d::Sprite::create(SCFileUtils::getFullPathFile((_image_)).c_str());\
    SCUISetup::assignNode(pSCTemSprite,(_node_));\
    sc_container_LayoutObjectList.push_back(pSCTemSprite);\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemSprite,_x_,_y_)\
    SpeedCC::SCNodeProperty::setProperty<cocos2d::Sprite>(pSCTemSprite,SCUISetup::purifyString((_property_)));

// label
// _type_ (1:system; 2:ttf; 3:bmfont)
#define ___SC_INSIDE_ADD_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_type_) \
    SpeedCC::SCString strSCTemText = SCUISetup::purifyLabelString((_string_));\
    cocos2d::Label* pSCTemLabel;\
    if((_type_)==1){\
        pSCTemLabel = cocos2d::Label::createWithSystemFont(strSCTemText.c_str(),SCUISetup::purifyString((_font_)).c_str(),(_size_));\
    }else if((_type_)==2){\
        pSCTemLabel = cocos2d::Label::createWithTTF(strSCTemText.c_str(),(_font_),(_size_));\
    }else if((_type_)==3){\
        pSCTemLabel = cocos2d::Label::createWithBMFont((_font_),strSCTemText.c_str());\
    }\
    SCUISetup::bindLabel(pSCTemLabel,(_string_));\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemLabel,(_x_),(_y_));\
    SCUISetup::assignNode(pSCTemLabel,(_node_));\
    SpeedCC::SCNodeProperty::setProperty<std::remove_pointer<decltype(pSCTemLabel)>::type>(pSCTemLabel,SCUISetup::purifyString((_property_)));\
    sc_container_LayoutObjectList.push_back(pSCTemLabel);


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
        SpeedCC::SCNodeProperty::setProperty<cocos2d::Menu>(pMenu,SCUISetup::purifyString((_property_)));\
    }\
    _buttonItem2InfoMap[pSCItemImage] = SCUISetup::purifyBehavior(this,(_fun_),pSCItemImage);\
    SCUISetup::assignNode(pSCItemImage,(_node_));\
    SpeedCC::SCNodeProperty::SFilterConfig scTemFilterConfig;\
    scTemFilterConfig.bExclude = false;\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_IMAGE);\
    SpeedCC::SCNodeProperty::setProperty<cocos2d::MenuItemSprite>(pSCItemImage,SCUISetup::purifyString((_property_)),&scTemFilterConfig);\
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
        SCNodeProperty::setProperty<cocos2d::Menu>(pMenu,SCUISetup::purifyString((_property_)));\
    }\
    _buttonItem2InfoMap[pSCTemItemLabel] = SCUISetup::purifyBehavior(this,(_fun_),pSCTemItemLabel);\
    SCUISetup::assignNode(pSCTemItemLabel,(_node_));\
    SpeedCC::SCNodeProperty::setProperty<cocos2d::MenuItemLabel>(pSCTemItemLabel,SCUISetup::purifyString((_property_)));\
    SpeedCC::SCNodeProperty::SFilterConfig scTemFilterConfig;\
    scTemFilterConfig.bExclude = false;\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_LABEL);\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_COLOR_TEXT);\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_FONT_NAME);\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_FONT_SIZE);\
    SpeedCC::SCNodeProperty::setProperty<cocos2d::Label>((_label_),SpeedCC::SCUISetup::purifyString((_property_)),&scTemFilterConfig);\
    sc_container_LayoutObjectList.push_back(pSCTemItemLabel);

// layer
#define ___SC_INSIDE_ADD_LAYER(_node_,_x_,_y_,_property_,_layer_,_size_) \
    auto pSCTemLayer = (_layer_); \
    pSCTemLayer->setContentSize((_size_));\
    pSCTemLayer->setAnchorPoint(cocos2d::Vec2(0.5,0.5));\
    pSCTemLayer->setIgnoreAnchorPointForPosition(false);\
    if(sc_container_type==2){sc_container_MultiplexLayerArray.pushBack(pSCTemLayer);}\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemLayer,(_x_),(_y_));\
    SCUISetup::assignNode(pSCTemLayer,(_node_));\
    SpeedCC::SCNodeProperty::setProperty<std::remove_pointer<decltype(pSCTemLayer)>::type>(pSCTemLayer,SCUISetup::purifyString((_property_))); \
    sc_container_LayoutObjectList.push_back(pSCTemLayer);

#endif // __SPEEDCC__SCUIMACRO_H__
