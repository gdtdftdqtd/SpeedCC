

#ifndef __SPEEDCC__SCNODEUTILS_H__
#define __SPEEDCC__SCNODEUTILS_H__

#include "cocos2d.h"

namespace SpeedCC
{
    class SCNodeUtils
    {
    public:
        static cocos2d::Vec2 posA2P(const cocos2d::Vec2& ptA,const cocos2d::Size& frameSize);
        static cocos2d::Vec2 posP2A(const cocos2d::Vec2& ptP,const cocos2d::Size& frameSize);
        static bool setRelPosition(cocos2d::Node* pNode,const cocos2d::Vec2& ptPer);
    };
}

#endif // __SPEEDCC__SCNODEUTILS_H__
