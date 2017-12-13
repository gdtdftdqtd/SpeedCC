

#include "SCNodeUtils.h"

using namespace cocos2d;

namespace SpeedCC
{
    Vec2 SCNodeUtils::posA2R(const Vec2& ptAbs,const Size& frameSize)
    {
        return Vec2(ptAbs.x/(frameSize.width/2.0) - 1.0, ptAbs.y/(frameSize.height/2.0)-1.0);
    }
    
    Vec2 SCNodeUtils::posR2A(const Vec2& ptRel,const Size& frameSize)
    {
        return Vec2((ptRel.x + 1.0)*(frameSize.width/2.0),(ptRel.y + 1.0)*(frameSize.height/2.0));
    }
}
