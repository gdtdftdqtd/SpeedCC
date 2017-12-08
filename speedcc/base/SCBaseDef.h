

#ifndef __SC__BASEDEF_H__
#define __SC__BASEDEF_H__

#include "SCMacroDef.h"
#include "cocos2d.h"

namespace SpeedCC
{
    ///-------------------- structure definition
    
    
    ///-------------------- function pointer type

    typedef bool (cocos2d::Ref::*FUN_SCButtonFunctor_t)();
    typedef bool (cocos2d::Ref::*FUN_SCButtonSenderFunctor_t)(cocos2d::MenuItem*);
    typedef void (cocos2d::Ref::*FUN_SCDelayExecuteFunction_t)(void* pData);
	typedef cocos2d::Scene* (*FUN_SCSceneTransitionCreateFunctor_t)(const float fDuration, cocos2d::Scene* pScene);
    
    ///-------------------- type definition
}


#endif //__SC__BASEDEF_H__
