

#ifndef __SPEEDCC__SCUIMACRO_H__
#define __SPEEDCC__SCUIMACRO_H__

#include "../component/SCBehaviorCommon.h"

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
        
//        static inline cocos2d::Rect purifyRect(int) { return cocos2d::Rec::ZERO;}
//        static inline cocos2d::Rect purifyRect(const cocos2d::Rect& rect) { return rect;}
        
        // label binder
        static inline void bindLabel(...) {}
        static inline void bindLabel(cocos2d::Label* pLabel,...) {}
        static inline void bindLabel(cocos2d::Label* pLabel,SCBinderUILabel::Ptr ptrBinder,SCSceneController* pController)
        {
            if(ptrBinder!=NULL && pLabel!=NULL)
            {
                ptrBinder->setLabel(pLabel);
                pController->storeBinder(pLabel,ptrBinder);
            }
        }
        
        template<typename T,
        typename = typename std::enable_if<SCIsWatchClass<typename T::type>::value==1,T>::type >
        static inline SCBinderUILabel::Ptr createLabelBinder(T ptrWatch)
        {
            if(ptrWatch!=NULL)
            {
                auto ptrLabelBinder = SCBinderUILabel::create();

                ptrLabelBinder->setWatch(ptrWatch);
                return ptrLabelBinder;
            }
            
            return NULL;
        }
        
        static inline SCBinderUILabel::Ptr createLabelBinder(SCBinderUILabel::Ptr ptrBinder)
        {
            return ptrBinder;
        }
        
        static inline SCBinderUILabel::Ptr createLabelBinder(...) { return NULL; }
        
        // toggle binder
        static inline SCBinderUISwitch::Ptr createToggleBinder(SCBinderUISwitch::Ptr ptrBinder)
        {
            return ptrBinder;
        }
        
        static inline SCBinderUISwitch::Ptr createToggleBinder(SCWatchBool::Ptr ptrWatch)
        {
            return (ptrWatch==NULL) ? NULL : SCBinderUISwitch::create(ptrWatch);
        }
        
        static inline SCBinderUISwitch::Ptr createToggleBinder(...)
        {
            return NULL;
        }
        
        static inline void bindToggle(cocos2d::MenuItemToggle* pToggle,
                                      SCBinderUISwitch::Ptr ptrBinder,
                                      SCSceneController* pController,
                                      const std::function<void(cocos2d::Ref*)>& func)
        {
            if(ptrBinder!=NULL && pToggle!=NULL)
            {
                ptrBinder->setToggle(pToggle);
                pController->storeBinder(pToggle,ptrBinder);
                ptrBinder->setCallback(func);
            }
        }
        
        // behavior
        static SCBehavior::Ptr purifyBehavior(cocos2d::Ref* pCall,cocos2d::SEL_CallFunc func,cocos2d::Ref* pSender)
        {
            return SCBehaviorCallFunc::create([pCall,func]()
                                                  {
                                                      (pCall->*func)();
                                                  });
        }
        
        static SCBehavior::Ptr purifyBehavior(cocos2d::Ref* pCall,cocos2d::SEL_MenuHandler func,cocos2d::Ref* pSender)
        {
            return SCBehaviorCallFunc::create([pCall,func,pSender]()
                                                  {
                                                      (pCall->*func)(pSender);
                                                  });
        }
        
        static SCBehavior::Ptr purifyBehavior(cocos2d::Ref* pCall,SCBehavior::Ptr bvr,cocos2d::Ref* pSender){ return bvr; }
        static SCBehavior::Ptr purifyBehavior(cocos2d::Ref* pCall,...){ return NULL;}
        
        static bool purifyBool(const bool bValue) {return bValue;}
        static bool purifyBool(SCWatchBool::Ptr ptrBool) { return (ptrBool==NULL ? false : (bool)(*ptrBool)); }
        
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
    SC_BEGIN_CONTAINER_ROOT_EX((_node_),(_x_),(_y_),(_property_),(_size_),getBedNode(),this)

#define SC_BEGIN_CONTAINER_ROOT_EX(_node_,_x_,_y_,_property_,_size_,_parent_,_controller_)\
{\
    int sc_root_nSCContainerStackCounter = 0;\
    SpeedCC::SCSceneController* pSCBelongController = (_controller_);\
    cocos2d::Size scTemRootContainerSize = (_size_);\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(_parent_) \
    sc_container_pParentNode->setContentSize(scTemRootContainerSize);\
    sc_container_pParentNode->setAnchorPoint(cocos2d::Vec2(0.5,0.5));\
    sc_container_pParentNode->setIgnoreAnchorPointForPosition(false);\
    if(scTemRootContainerSize.width==0 || scTemRootContainerSize.height==0) {scTemRootContainerSize= sc_container_pParentNode->getContentSize();} \
    if((_x_)!=kSCPositionIgnore && (_y_)!=kSCPositionIgnore){\
        sc_container_pParentNode->setPosition(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2((_x_),(_y_)),scTemRootContainerSize)); \
    } else if((_x_)!=kSCPositionIgnore){\
        sc_container_pParentNode->setPositionX(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2((_x_),(_y_)),scTemRootContainerSize).x);\
    }else if((_y_)!=kSCPositionIgnore){\
        sc_container_pParentNode->setPositionY(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2((_x_),(_y_)),scTemRootContainerSize).y);\
    }\
    ___SC_INSIDE_ASSIGN_NODE(sc_container_pParentNode,(_node_));\
SpeedCC::SCNodeProperty::setProperty<std::remove_pointer<decltype(sc_container_pParentNode)>::type>(sc_container_pParentNode,SpeedCC::SCUISetup::purifyString((_property_)));\
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
    ___SC_INSIDE_ASSIGN_NODE(pSCContainerSprite,(_node_)); \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerSprite)


///-------------- button related
// insert image button
#define SC_INSERT_BUTTON_IMAGE(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_func_)\
    do{\
        ___SC_INSIDE_ADD_BUTTON_IMAGE((_node_),(_x_),(_y_),(_property_),(_image_normal_),(_image_select_),(_image_disable_),(_func_)) \
    }while(0);

// container image button
#define SC_BEGIN_CONTAINER_BUTTON_IMAGE(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_func_) \
{\
    cocos2d::MenuItem* pSCContainerMenuItem = NULL;\
    ___SC_INSIDE_ADD_BUTTON_IMAGE(pSCContainerMenuItem,(_x_),(_y_),(_property_),(_image_normal_),(_image_select_),(_image_disable_),_func_) \
    ___SC_INSIDE_ASSIGN_NODE(pSCContainerMenuItem,(_node_)); \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCContainerMenuItem)


// insert ttf label button
#define SC_INSERT_BUTTON_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_func_) \
do{\
    SCString strSCTemText = SpeedCC::SCUISetup::purifyLabelString((_string_));\
    auto scTemLabelBinderPtr = SpeedCC::SCUISetup::createLabelBinder((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithTTF(strSCTemText.c_str(),(_font_),(_size_));\
    SpeedCC::SCUISetup::bindLabel(pSCTemLabel,scTemLabelBinderPtr,pSCBelongController);\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_func_))\
}while(0);

// container ttf label button
#define SC_BEGIN_CONTAINER_BUTTON_LABEL_TTF(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_func_) \
{\
    SCString strSCTemText = SpeedCC::SCUISetup::purifyLabelString((_string_));\
    auto scTemLabelBinderPtr = SpeedCC::SCUISetup::createLabelBinder((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithTTF(strSCTemText.c_str(),(_font_),(_size_));\
    SpeedCC::SCUISetup::bindLabel(pSCTemLabel,scTemLabelBinderPtr,pSCBelongController);\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_func_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCTemLabel)

// insert system label button
#define SC_INSERT_BUTTON_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_func_) \
do{\
    SpeedCC::SCString strSCTemText = SpeedCC::SCUISetup::purifyLabelString((_string_));\
    auto scTemLabelBinderPtr = SpeedCC::SCUISetup::createLabelBinder((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithSystemFont(strSCTemText.c_str(),SpeedCC::SCUISetup::purifyString((_font_)).c_str(),(_size_));\
    SpeedCC::SCUISetup::bindLabel(pSCTemLabel,scTemLabelBinderPtr,pSCBelongController);\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_func_))\
}while(0);

// container system label button
#define SC_BEGIN_CONTAINER_BUTTON_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_func_) \
{\
    SCString strSCTemText = SpeedCC::SCUISetup::purifyLabelString((_string_));\
    auto scTemLabelBinderPtr = SpeedCC::SCUISetup::createLabelBinder((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithSystemFont(strSCTemText.c_str(),(_font_),(_size_));\
    SpeedCC::SCUISetup::bindLabel(pSCTemLabel,scTemLabelBinderPtr,pSCBelongController);\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_func_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCTemLabel)

// insert bmfont label button
#define SC_INSERT_BUTTON_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_font_,_func_) \
do{\
    SCString strSCTemText = SpeedCC::SCUISetup::purifyLabelString((_string_));\
    auto scTemLabelBinderPtr = SpeedCC::SCUISetup::createLabelBinder((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithBMFont((_font_),strSCTemText.c_str());\
    SpeedCC::SCUISetup::bindLabel(pSCTemLabel,scTemLabelBinderPtr,pSCBelongController);\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_func_))\
}while(0);

// container bmfont label button
#define SC_BEGIN_CONTAINER_BUTTON_LABEL_BMFONT(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_func_) \
{\
    SCString strSCTemText = SpeedCC::SCUISetup::purifyLabelString((_string_));\
    auto scTemLabelBinderPtr = SpeedCC::SCUISetup::createLabelBinder((_string_));\
    auto pSCTemLabel = cocos2d::Label::createWithBMFont((_font_),strSCTemText.c_str());\
    SpeedCC::SCUISetup::bindLabel(pSCTemLabel,(scTemLabelBinderPtr),pSCBelongController);\
    ___SC_INSIDE_ADD_BUTTON_LABEL((_node_),(_x_),(_y_),(_property_),pSCTemLabel,(_func_))\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCTemLabel)


// toggle button
#define SC_INSERT_BUTTON_SWITCH(_node_,_x_,_y_,_property_,_true_item_,_false_item_,_value_,_func_) \
do{\
    ___SC_INSIDE_ADD_BUTTON_SWITCH((_node_),(_x_),(_y_),(_property_),(_true_item_),(_false_item_),(_value_),(_func_))\
}while(0);


#define SC_BEGIN_CONTAINER_BUTTON_SWITCH(_node_,_x_,_y_,_property_,_true_item_,_false_item_,_value_,_func_) \
{\
    cocos2d::MenuItemToggle* pSCMenuItemToggle = NULL;\
    ___SC_INSIDE_ADD_BUTTON_SWITCH(pSCMenuItemToggle,(_x_),(_y_),(_property_),(_true_item_),(_false_item_),(_value_),(_func_)) \
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCMenuItemToggle)


#define SC_INSERT_OPTION_MUSIC(_node_,_x_,_y_,_property_,_true_item_,_false_item_) \
do{\
    auto ptrMusic = SpeedCC::SCSetting::getInstance()->getMusicWatch();\
    SC_INSERT_BUTTON_SWITCH((_node_),(_x_),(_y_),(_property_),(_true_item_),(_false_item_),ptrMusic,NULL) \
}while(0);

#define SC_INSERT_OPTION_SOUND(_node_,_x_,_y_,_property_,_true_item_,_false_item_) \
do{\
    auto ptrSound = SpeedCC::SCSetting::getInstance()->getSoundWatch();\
    SC_INSERT_BUTTON_SWITCH((_node_),(_x_),(_y_),(_property_),(_true_item_),(_false_item_),ptrSound,NULL) \
}while(0);

///-------------- user node related
// insert customize Node that user created
#define SC_INSERT_USER_NODE(_node_,_x_,_y_,_property_) \
    do{\
        auto pSCUserNode = (_node_);\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCUserNode,(_x_),(_y_));\
        SpeedCC::SCNodeProperty::setProperty<std::remove_pointer<decltype(pSCUserNode)>::type>(pSCUserNode,SpeedCC::SCUISetup::purifyString((_property_)));\
    }while(0);


#define SC_BEGIN_CONTAINER_USER_NODE(_node_,_x_,_y_,_property_) \
{\
    auto pSCUserNode = (_node_);\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCUserNode,(_x_),(_y_));\
    SpeedCC::SCNodeProperty::setProperty<std::remove_pointer<decltype(pSCUserNode)>::type>(pSCUserNode,SpeedCC::SCUISetup::purifyString((_property_)));\
    ___SC_INSIDE_DEFINE_CONTAINER_VAR(pSCUserNode)

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
    ___SC_INSIDE_ASSIGN_NODE(pSCContainerLabel,(_node_)); \
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
    ___SC_INSIDE_ASSIGN_NODE(pSCContainerLabel,(_node_)); \
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
    ___SC_INSIDE_ASSIGN_NODE(pSCContainerLabel,(_node_)); \
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
    SpeedCC::SCContainerEndFunctor* sc_container_pEndFunctor = NULL; \
    cocos2d::Node* sc_container_pParentNode = (_parent_); \
    std::vector<cocos2d::MenuItem*> sc_container_MenuItemArray;\
    cocos2d::Vector<cocos2d::Layer*> sc_container_MultiplexLayerArray;\
    std::list<cocos2d::Ref*>    sc_container_LayoutObjectList;\
    cocos2d::Menu* sc_container_pButtonListMenu = NULL; \
    ++sc_root_nSCContainerStackCounter;\
    int sc_container_type = 0;

#define ___SC_INSIDE_ADD_LAYOUT_NODE(_parent_,_node_,_x_,_y_) \
do{\
    cocos2d::Node* pSCTemParent = (_parent_);\
    if(pSCTemParent){\
        const cocos2d::Size& tParentSizeTem = pSCTemParent->getContentSize();\
        pSCTemParent->addChild((_node_));\
        if((_x_)!=kSCPositionIgnore && (_y_)!=kSCPositionIgnore){\
            (_node_)->setPosition(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2((_x_),(_y_)),tParentSizeTem)); \
        } else if((_x_)!=kSCPositionIgnore){\
            (_node_)->setPositionX(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2((_x_),(_y_)),tParentSizeTem).x);\
        }else if((_y_)!=kSCPositionIgnore){\
            (_node_)->setPositionY(SpeedCC::SCNodeUtils::posP2A(cocos2d::Vec2((_x_),(_y_)),tParentSizeTem).y);\
        }\
    }\
}while(0);

// sprite
#define ___SC_INSIDE_ADD_SPRITE(_node_,_x_,_y_,_property_,_image_)\
do{\
    cocos2d::Sprite* pSCTemSprite = cocos2d::Sprite::create(SpeedCC::SCFileUtils::getFullPathFile((_image_)).c_str());\
    ___SC_INSIDE_ASSIGN_NODE(pSCTemSprite,(_node_));\
    sc_container_LayoutObjectList.push_back(pSCTemSprite);\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemSprite,_x_,_y_)\
    SpeedCC::SCNodeProperty::setProperty<cocos2d::Sprite>(pSCTemSprite,SpeedCC::SCUISetup::purifyString((_property_))); \
}while(0);

// label
// _type_ (1:system; 2:ttf; 3:bmfont)
#define ___SC_INSIDE_ADD_LABEL(_node_,_x_,_y_,_property_,_string_,_font_,_size_,_type_) \
do{\
    SpeedCC::SCString strSCTemText = SpeedCC::SCUISetup::purifyLabelString((_string_));\
    auto scTemLabelBinderPtr = SpeedCC::SCUISetup::createLabelBinder((_string_));\
    cocos2d::Label* pSCTemLabel;\
    if((_type_)==1){\
        pSCTemLabel = cocos2d::Label::createWithSystemFont(strSCTemText.c_str(),SpeedCC::SCUISetup::purifyString((_font_)).c_str(),(_size_));\
    }else if((_type_)==2){\
        pSCTemLabel = cocos2d::Label::createWithTTF(strSCTemText.c_str(),(_font_),(_size_));\
    }else if((_type_)==3){\
        pSCTemLabel = cocos2d::Label::createWithBMFont((_font_),strSCTemText.c_str());\
    }\
    SpeedCC::SCUISetup::bindLabel(pSCTemLabel,scTemLabelBinderPtr,pSCBelongController);\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemLabel,(_x_),(_y_));\
    ___SC_INSIDE_ASSIGN_NODE(pSCTemLabel,(_node_));\
    SpeedCC::SCNodeProperty::setProperty<std::remove_pointer<decltype(pSCTemLabel)>::type>(pSCTemLabel,SpeedCC::SCUISetup::purifyString((_property_)));\
    sc_container_LayoutObjectList.push_back(pSCTemLabel);\
}while(0);


// button
#define ___SC_INSIDE_ADD_BUTTON_IMAGE(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_func_) \
do{\
    cocos2d::Sprite* pSCTemSprite[3] = {NULL};\
    pSCTemSprite[0] = cocos2d::Sprite::create(SpeedCC::SCFileUtils::getFullPathFile(_image_normal_).c_str());\
    pSCTemSprite[1] = cocos2d::Sprite::create(SpeedCC::SCFileUtils::getFullPathFile(_image_select_).c_str());\
    pSCTemSprite[2] = cocos2d::Sprite::create(SpeedCC::SCFileUtils::getFullPathFile(_image_disable_).c_str());\
    cocos2d::MenuItemSprite* pSCItemImage = cocos2d::MenuItemSprite::create(pSCTemSprite[0],pSCTemSprite[1],pSCTemSprite[2],\
[pSCBelongController](cocos2d::Ref* pSender) { pSCBelongController->onSCMenuItemPressed(pSender);}); \
    if(!sc_container_MenuItemArray.empty()){\
        sc_container_MenuItemArray.push_back(pSCItemImage);\
    }else if(sc_container_pButtonListMenu!=NULL){\
        sc_container_pButtonListMenu->addChild(pSCItemImage);\
    }else{\
        cocos2d::Menu* pMenu = cocos2d::Menu::create(pSCItemImage,NULL);\
        pMenu->setContentSize(pSCTemSprite[0]->getContentSize());\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pMenu,(_x_),(_y_));\
        SpeedCC::SCNodeProperty::setProperty<cocos2d::Menu>(pMenu,SpeedCC::SCUISetup::purifyString((_property_)));\
    }\
    auto pSCBvrFunc = (_func_); \
    _buttonItem2InfoMap[pSCItemImage] = SpeedCC::SCUISetup::purifyBehavior(pSCBelongController,pSCBvrFunc,pSCItemImage);\
    ___SC_INSIDE_ASSIGN_NODE(pSCItemImage,(_node_));\
    SpeedCC::SCNodeProperty::SFilterConfig scTemFilterConfig;\
    scTemFilterConfig.bExclude = true;\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_IMAGE);\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_SCALE_Y);\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_SCALE_X);\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_SCALE);\
    SpeedCC::SCNodeProperty::setProperty<cocos2d::MenuItemSprite>(pSCItemImage,SpeedCC::SCUISetup::purifyString((_property_)),&scTemFilterConfig);\
    sc_container_LayoutObjectList.push_back(pSCItemImage);\
}while(0);

// button label
#define ___SC_INSIDE_ADD_BUTTON_LABEL(_node_,_x_,_y_,_property_,_label_,_func_)\
do{\
    cocos2d::MenuItemLabel* pSCTemItemLabel = cocos2d::MenuItemLabel::create((_label_),\
    [pSCBelongController](cocos2d::Ref* pSender) { pSCBelongController->onSCMenuItemPressed(pSender);}); \
    if(!sc_container_MenuItemArray.empty()){\
        sc_container_MenuItemArray.push_back(pSCTemItemLabel);\
    }else if(sc_container_pButtonListMenu!=NULL){\
        sc_container_pButtonListMenu->addChild(pSCTemItemLabel);\
    }else{\
        cocos2d::Menu* pMenu = cocos2d::Menu::create(pSCTemItemLabel,NULL);\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pMenu,(_x_),(_y_));\
        SpeedCC::SCNodeProperty::setProperty<cocos2d::Menu>(pMenu,SpeedCC::SCUISetup::purifyString((_property_)));\
    }\
    auto pSCBvrFunc = (_func_); \
    _buttonItem2InfoMap[pSCTemItemLabel] = SpeedCC::SCUISetup::purifyBehavior(pSCBelongController,pSCBvrFunc,pSCTemItemLabel);\
    ___SC_INSIDE_ASSIGN_NODE(pSCTemItemLabel,(_node_));\
    SpeedCC::SCNodeProperty::setProperty<cocos2d::MenuItemLabel>(pSCTemItemLabel,SpeedCC::SCUISetup::purifyString((_property_)));\
    SpeedCC::SCNodeProperty::SFilterConfig scTemFilterConfig;\
    scTemFilterConfig.bExclude = false;\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_LABEL);\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_COLOR_TEXT);\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_FONT_NAME);\
    scTemFilterConfig.keyVtr.push_back(SC_NODE_PROPERTY_FONT_SIZE);\
    SpeedCC::SCNodeProperty::setProperty<cocos2d::Label>((_label_),SpeedCC::SCUISetup::purifyString((_property_)),&scTemFilterConfig);\
    sc_container_LayoutObjectList.push_back(pSCTemItemLabel); \
}while(0);

#define ___SC_INSIDE_ADD_BUTTON_SWITCH(_node_,_x_,_y_,_property_,_true_item_,_false_item_,_value_,_func_) \
do{\
    auto ptrSCToggleBinder = SpeedCC::SCUISetup::createToggleBinder((_value_));\
    auto scCallbackFunc = [pSCBelongController](cocos2d::Ref* pSender) { pSCBelongController->onSCMenuItemPressed(pSender);};\
    const bool bSCValue = SpeedCC::SCUISetup::purifyBool((_value_));\
    SpeedCC::SCString strSCToggleImage1 = (_true_item_);\
    SpeedCC::SCString strSCToggleImage2 = (_false_item_);\
    std::vector<cocos2d::MenuItem*> sc_container_MenuItemArray;\
    sc_container_MenuItemArray.push_back(NULL);/* the first element is NULL, in order to cause ___SC_INSIDE_ADD_BUTTON_IMAGE adds menu item to array, but not add to container node*/\
    {___SC_INSIDE_ADD_BUTTON_IMAGE(NULL,0,0,NULL,strSCToggleImage1,strSCToggleImage1,strSCToggleImage1,NULL)}\
    {___SC_INSIDE_ADD_BUTTON_IMAGE(NULL,0,0,NULL,strSCToggleImage2,strSCToggleImage2,strSCToggleImage2,NULL)}\
    cocos2d::MenuItemToggle* pSCInsideToggleItem = cocos2d::MenuItemToggle::createWithCallback(\
                    NULL, \
                    (cocos2d::MenuItem*)sc_container_MenuItemArray[1],\
                    (cocos2d::MenuItem*)sc_container_MenuItemArray[2],NULL);\
    sc_container_MenuItemArray.clear();\
    pSCInsideToggleItem->setSelectedIndex(bSCValue ? 0 : 1);\
    SpeedCC::SCUISetup::bindToggle(pSCInsideToggleItem,ptrSCToggleBinder,pSCBelongController,scCallbackFunc);\
    cocos2d::Menu* pMenu = cocos2d::Menu::create(pSCInsideToggleItem,NULL);\
    pMenu->setContentSize(sc_container_MenuItemArray[1]->getContentSize());\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pMenu,(_x_),(_y_));\
    SpeedCC::SCNodeProperty::setProperty<cocos2d::Menu>(pMenu,SpeedCC::SCUISetup::purifyString((_property_)));\
    auto pSCBvrFunc = (_func_); \
    _buttonItem2InfoMap[pSCInsideToggleItem] = SpeedCC::SCUISetup::purifyBehavior(pSCBelongController,pSCBvrFunc,pSCInsideToggleItem);\
    ___SC_INSIDE_ASSIGN_NODE(pSCInsideToggleItem,(_node_)); \
}while(0);


// layer
#define ___SC_INSIDE_ADD_LAYER(_node_,_x_,_y_,_property_,_layer_,_size_) \
do{\
    auto pSCTemLayer = (_layer_); \
    pSCTemLayer->setContentSize((_size_));\
    pSCTemLayer->setAnchorPoint(cocos2d::Vec2(0.5,0.5));\
    pSCTemLayer->setIgnoreAnchorPointForPosition(false);\
    if(sc_container_type==2){sc_container_MultiplexLayerArray.pushBack(pSCTemLayer);}\
    ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemLayer,(_x_),(_y_));\
    ___SC_INSIDE_ASSIGN_NODE(pSCTemLayer,(_node_));\
    SpeedCC::SCNodeProperty::setProperty<std::remove_pointer<decltype(pSCTemLayer)>::type>(pSCTemLayer,SpeedCC::SCUISetup::purifyString((_property_))); \
    sc_container_LayoutObjectList.push_back(pSCTemLayer);\
}while(0);


#define ___SC_INSIDE_ASSIGN_NODE(_node_ptr_,_node_) \
    this->storeLayoutNode((_node_),(_node_ptr_));\
    SpeedCC::SCUISetup::assignNode((_node_ptr_),(_node_));\

#endif // __SPEEDCC__SCUIMACRO_H__
