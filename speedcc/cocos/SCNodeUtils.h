

#ifndef __SPEEDCC__SCNODEUTILS_H__
#define __SPEEDCC__SCNODEUTILS_H__

#include "cocos2d.h"
#include "../stage/SCPerformObject.h"

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
        static bool setPerPosition(cocos2d::Node* pNode,const cocos2d::Vec2& ptPer);
        static void setPositionBy(cocos2d::Node* pNode,float fXBy,float fYBy);
        static bool setDock(cocos2d::Node* pNode,const int dockFlag);
        
        static void setNodeClickable(cocos2d::Node* pNode,SCBehavior::Ptr ptrBvr);
        static void removeNodeClickable(cocos2d::Node* pNode);
        
    private:
        // nPark. <0:(left or bottom); 0:center; >0:(right or top)
        static float getDockPosition(cocos2d::Node* pNode,int nPark,const bool bIsX);
    };
}

#endif // __SPEEDCC__SCNODEUTILS_H__
