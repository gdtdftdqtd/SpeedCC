

#include "SCNodeUtils.h"
#include "../base/SCMacroDef.h"

using namespace cocos2d;

namespace SpeedCC
{
    Vec2 SCNodeUtils::posA2R(const Vec2& ptAbs,const Size& frameSize=SCWinSize())
    {
        return Vec2(ptAbs.x/frameSize.width,ptAbs.y/frameSize.height);
    }
    
    Vec2 SCNodeUtils::posR2A(const Vec2& ptRel,const Size& frameSize=SCWinSize())
    {
        return Vec2(ptRel.x*frameSize.width,ptRel.y*frameSize.height);
    }
}
