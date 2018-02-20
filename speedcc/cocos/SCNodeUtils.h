

#ifndef __SPEEDCC__SCNODEUTILS_H__
#define __SPEEDCC__SCNODEUTILS_H__

#include "cocos2d.h"
#include "../stage/SCPerformObject.h"
#include "SCRefHolder.h"

namespace SpeedCC
{
    class SCNodeUtils
    {
    public:
        enum EDockType
        {
            kDockLeft           = (1<<0),
            kDockRight          = (1<<1),
            kDockMiddleX        = (kDockLeft | kDockRight),
            kDockTop            = (1<<2),
            kDockBottom         = (1<<3),
            kDockMiddleY        = (kDockTop | kDockBottom),
            kDockCenter         = (kDockMiddleX | kDockMiddleY)
        };
        
       
    public:
        static cocos2d::Vec2 posA2P(const cocos2d::Vec2& ptA,const cocos2d::Size& frameSize);
        static cocos2d::Vec2 posP2A(const cocos2d::Vec2& ptP,const cocos2d::Size& frameSize);
        static bool setPositionPer(cocos2d::Node* pNode,const cocos2d::Vec2& ptPer);
        static void setPositionBy(cocos2d::Node* pNode,float fXBy,float fYBy);
        static bool setDock(cocos2d::Node* pNode,const int nDockFlag);
        static cocos2d::Vec2 getDockPosition(cocos2d::Node* pNode,const int nDockFlag);
        
        static void addClickable(cocos2d::Node* pNode,SCBehavior::Ptr ptrBvr);
        static void removeClickable(cocos2d::Node* pNode);
        
        static void addUserObj(cocos2d::Node* pNode,cocos2d::Ref* pRef);
        static void addUserObj(cocos2d::Node* pNode,SCObject::Ptr ptrObj);
        
        template<typename T,
        typename = typename std::enable_if<std::is_convertible<T,cocos2d::Ref*>::value==1 ||
        SCIsObjPtrClassT<T>::value==1>::type>
        static void removeUserObj(cocos2d::Node* pNode)
        {
            SC_RETURN_V_IF(pNode==nullptr || pNode->getUserObject()==nullptr);
            auto pHolder = SCNodeUtils::getUserHolder(pNode);
            
            SC_RETURN_V_IF(pHolder->isEmpty());
            
            pHolder->removeObj<T>();
        }
        
        template<typename T,
        typename = typename std::enable_if<SCIsObjPtrClassT<T>::value==1 ||
        std::is_convertible<T,cocos2d::Ref*>::value==1 >::type>
        static T getUserObj(cocos2d::Node* pNode)
        {
            SC_RETURN_IF(pNode==nullptr || pNode->getUserObject()==nullptr,nullptr);
            auto pHolder = SCNodeUtils::getUserHolder(pNode,false);
            
            SC_RETURN_IF(pHolder==nullptr || pHolder->isEmpty(),nullptr);
            
            return pHolder->getObj<T>();
        }
        
        template<typename T,
        typename = typename std::enable_if<SCIsObjPtrClassT<T>::value==1 ||
        std::is_convertible<T,cocos2d::Ref*>::value==1 >::type>
        static bool hasUserObj(cocos2d::Node* pNode)
        {
            SC_RETURN_IF(pNode==nullptr || pNode->getUserObject()==nullptr,false);
            auto pHolder = SCNodeUtils::getUserHolder(pNode,false);
            SC_RETURN_IF(pHolder==nullptr || pHolder->isEmpty(),false);
            return pHolder->hasObj<T>();
        }
        
        static cocos2d::Sprite* createSprite(const SCString& strName);
        
    private:
        // nPark. <0:(left or bottom); 0:center; >0:(right or top)
        static float getDockPosition(cocos2d::Node* pNode,int nPark,const bool bIsX);
        
        // get ref holder from user object, if not exist, then create it.
        static SCRefHolder* getUserHolder(cocos2d::Node* pNode,const bool bCreate=false);
    };
}

#endif // __SPEEDCC__SCNODEUTILS_H__
