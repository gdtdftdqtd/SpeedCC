

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


#define SC_DEFINE_CONTAINER_VAR(_parent_) \
    SCContainerEndFunctor* sc_container_pEndFunctor = NULL; \
    cocos2d::Layer* sc_container_pParentNode = (_parent_); \
    cocos2d::Vector<cocos2d::MenuItem*> sc_container_MenuItemArray;\
    std::list<cocos2d::Ref*>    sc_container_LayoutObjectList;\
    cocos2d::Menu* sc_container_pButtonListMenu = NULL;


// begin root container
#define SC_BEGIN_CONTAINER_ROOT(_node_,_x_,_y_,_property_,_size_) \
    SC_BEGIN_CONTAINER_ROOT_EX((_node_),(_x_),(_y_),(_property_),(_size_),getRootLayer())


#define SC_BEGIN_CONTAINER_ROOT_EX(_node_,_x_,_y_,_property_,_size_,_parent_)\
{\
    SC_DEFINE_CONTAINER_VAR(_parent_) \
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


// insert a sprite
#define SC_INSERT_SPRITE(_node_,_x_,_y_,_property_,_image_) \
    do{\
        cocos2d::Sprite* pSCTemSprite = cocos2d::Sprite::create(SCFileUtils::getFullPathFile((_image_)).c_str());\
        assignNode(pSCTemSprite,(_node_));\
        sc_container_LayoutObjectList.push_back(pSCTemSprite);\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemSprite,_x_,_y_)\
        SCNodeProperty::setProperty<cocos2d::Sprite>(pSCTemSprite,purifyProertyString((_property_)));\
    }while(0);

// insert button with image
#define SC_INSERT_BUTTON_IMAGE(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_fun_)\
    ___SC_INSIDE_ADD_BUTTON_IMAGE((_node_),(_x_),(_y_),(_property_),(_image_normal_),(_image_select_),(_image_disable_),_fun_)

// insert customize's Node that user created
#define SC_INSERT_USER_NODE(_node_,_x_,_y_,_property_) \
    do{\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,(_node_),(_x_),(_y_));\
        SCNodeProperty::setProperty<std::remove_pointer<decltype(_node_)>::type>((_node_),purifyProertyString((_property_)));\
    }while(0);



////---------------- inside macro
// below macros are used inside above macros, do not use in game

#define ___SC_INSIDE_ADD_LAYOUT_NODE(_parent_,_node_,_x_,_y_) \
    cocos2d::Node* pSCTemParent = (_parent_);\
    if(pSCTemParent){\
        const cocos2d::Size& tParentSizeTem = pSCTemParent->getContentSize();\
        pSCTemParent->addChild(_node_);\
        (_node_)->setPosition(SCNodeUtils::posR2A(cocos2d::Vec2((_x_),(_y_)),tParentSizeTem)); \
    }\


#define ___SC_INSIDE_ADD_BUTTON_IMAGE(_node_,_x_,_y_,_property_,_image_normal_,_image_select_,_image_disable_,_fun_) \
do{\
    cocos2d::Sprite* pSCTemSprite[3] = {NULL};\
    pSCTemSprite[0] = cocos2d::Sprite::create(SCFileUtils::getFullPathFile(_image_normal_).c_str());\
    pSCTemSprite[1] = cocos2d::Sprite::create(SCFileUtils::getFullPathFile(_image_select_).c_str());\
    pSCTemSprite[2] = cocos2d::Sprite::create(SCFileUtils::getFullPathFile(_image_disable_).c_str());\
    cocos2d::MenuItemSprite* pSCItemImage = cocos2d::MenuItemSprite::create(pSCTemSprite[0],pSCTemSprite[1],pSCTemSprite[2],\
[this](cocos2d::Ref* pSender) { this->onSCMenuItemPressed(pSender);}) ; \
    if(!sc_container_MenuItemArray.empty()){\
        sc_container_MenuItemArray.pushBack(pSCItemImage);\
    }else if(sc_container_pButtonListMenu!=NULL){\
        sc_container_pButtonListMenu->addChild(pSCItemImage);\
    }else{\
        cocos2d::Menu* pMenu = cocos2d::Menu::create(pSCItemImage,NULL) ;\
        pMenu->setContentSize(pSCTemSprite[0]->getContentSize());\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pMenu,(_x_),(_y_)) ;\
        SCNodeProperty::setProperty<cocos2d::Menu>(pMenu,purifyProertyString((_property_)));\
    }\
    _buttonItem2InfoMap[pSCItemImage] = purifyBehavior(this,(_fun_),pSCItemImage);\
    assignNode(pSCItemImage,(_node_));\
    SCNodeProperty::setProperty<cocos2d::MenuItemSprite>(pSCItemImage,purifyProertyString((_property_)));\
    sc_container_LayoutObjectList.push_back(pSCItemImage);\
}while(0);


#endif // __SPEEDCC__SCUIMACRO_H__
