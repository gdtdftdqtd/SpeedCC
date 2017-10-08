

#ifndef __SPEEDCC__SCNODEACTION_H__
#define __SPEEDCC__SCNODEACTION_H__

#include "../SCComponent.h"

namespace SpeedCC
{
    class SCNodeAction : public SCComponent
    {
    private:
        SC_AVOID_CLASS_COPY(SCNodeAction);
        SCNodeAction():
        _pNode(NULL)
        {}
        
    public:
        static Ptr create(cocos2d::Node* pNode);
        cocos2d::Action* runAction(cocos2d::Action* action);
        void stopAllActions();
        void stopAction(cocos2d::Action* action);
        void stopActionByTag(int tag);
        void stopAllActionsByTag(int tag);
        void stopActionsByFlags(unsigned int flags);
        cocos2d::Action* getActionByTag(int tag);
        
    private:
        cocos2d::Node*    _pNode;
    };
}

#endif // __SPEEDCC__SCNODEACTION_H__
