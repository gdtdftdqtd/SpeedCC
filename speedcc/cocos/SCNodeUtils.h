

#ifndef __SPEEDCC__SCNODEUTILS_H__
#define __SPEEDCC__SCNODEUTILS_H__

#include "cocos2d.h"

namespace SpeedCC
{
    class SCNodeUtils
    {
    public:
        static cocos2d::Vec2 posA2R(const cocos2d::Vec2& ptA,const cocos2d::Size& frameSize);
        static cocos2d::Vec2 posR2A(const cocos2d::Vec2& ptR,const cocos2d::Size& frameSize);
        static bool setRelPosition(cocos2d::Node* pNode,const cocos2d::Vec2& ptRel);
    };
}

#endif // __SPEEDCC__SCNODEUTILS_H__
