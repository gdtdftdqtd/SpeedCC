

#include "SCNodeAction.h"

namespace SpeedCC
{
    Ptr SCNodeAction::create(cocos2d::Node* pNode)
    {
        Ptr ret;
        return ret;
    }
    
    cocos2d::Action* SCNodeAction::runAction(cocos2d::Action* action)
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->runAction(action);
    }
    
    void SCNodeAction::stopAllActions()
    {
        SCASSERT(_pNode!=NULL);
        _pNode->stopAllActions();
    }
    
    void SCNodeAction::stopAction(cocos2d::Action* action)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->stopAction(action);
    }
    
    void SCNodeAction::stopActionByTag(int tag)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->stopActionByTag(tag);
    }
    
    void SCNodeAction::stopAllActionsByTag(int tag)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->stopAllActionsByTag(tag);
    }
    
    void SCNodeAction::stopActionsByFlags(unsigned int flags)
    {
        SCASSERT(_pNode!=NULL);
        _pNode->stopActionsByFlags(flags);
    }
    
    cocos2d::Action* SCNodeAction::getActionByTag(int tag)
    {
        SCASSERT(_pNode!=NULL);
        return _pNode->getActionByTag(tag);
    }
}

