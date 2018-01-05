

#include "SCNodeUtils.h"
#include "SCMacroDef.h"
#include "SCCocosDef.h"

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
    
    bool SCNodeUtils::setRelPosition(cocos2d::Node* pNode,const cocos2d::Vec2& ptRel)
    {
        SC_RETURN_IF(pNode==NULL || pNode->getParent()==NULL,false);
        
        const auto frameSize = pNode->getParent()->getContentSize();
        const auto pos = SCNodeUtils::posR2A(ptRel,frameSize);
        pNode->setPosition(pos);
        
        return true;
    }
}
