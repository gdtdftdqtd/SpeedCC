

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
/*
 pPTGEndFunctor => sc_container_pEndFunctor
 rootTLMenuItemArray => sc_container_MenuItemArray
 pPTGTemParentNode => sc_container_pParentNode
 ptgLayoutObjectList => sc_container_LayoutObjectList
 pPTGTemButtonListMenu => sc_container_pButtonListMenu
 
 nPTGContainerStackCounter => sc_root_nSCContainerStackCounter
 
 assignCCNode() => assignNode()
 */



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
    SCNodeProperty::setProperty(sc_container_pParentNode,purifyProertyString((_property_)));\
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
        cocos2d::Sprite* pSCTemSprite = cocos2d::Sprite::create((_image_));\
        assignNode(pSCTemSprite,(_node_));\
        sc_container_LayoutObjectList.push_back(pSCTemSprite);\
        ___SC_INSIDE_ADD_LAYOUT_NODE(sc_container_pParentNode,pSCTemSprite,_x_,_y_)\
        SCNodeProperty::setProperty(sc_container_pParentNode,purifyProertyString((_property_)));\
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





#endif // __SPEEDCC__SCUIMACRO_H__
