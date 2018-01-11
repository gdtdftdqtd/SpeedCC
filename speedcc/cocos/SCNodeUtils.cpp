

#include "SCNodeUtils.h"
#include "SCMacroDef.h"
#include "SCCocosDef.h"

using namespace cocos2d;

namespace SpeedCC
{
    Vec2 SCNodeUtils::posA2P(const Vec2& ptAbs,const Size& frameSize=SCWinSize())
    {
        return Vec2(ptAbs.x/frameSize.width,ptAbs.y/frameSize.height);
    }
    
    Vec2 SCNodeUtils::posP2A(const Vec2& ptPer,const Size& frameSize=SCWinSize())
    {
        return Vec2(ptPer.x*frameSize.width,ptPer.y*frameSize.height);
    }
    
    bool SCNodeUtils::setRelPosition(cocos2d::Node* pNode,const cocos2d::Vec2& ptPer)
    {
        SC_RETURN_IF(pNode==NULL || pNode->getParent()==NULL,false);
        
        const auto frameSize = pNode->getParent()->getContentSize();
        const auto pos = SCNodeUtils::posP2A(ptPer,frameSize);
        pNode->setPosition(pos);
        
        return true;
    }
}
