

#ifndef __SC__BASEDEF_H__
#define __SC__BASEDEF_H__

#include "SCMacroDef.h"
#include "cocos2d.h"

namespace SpeedCC
{
    ///-------------------- structure definition
    class SCSceneControllerInterface;
    struct SSceneControllerInfo
    {
        cocos2d::Scene*              pScene;
        SCSceneControllerInterface*   pInterface;
        
        SSceneControllerInfo():
        pScene(NULL),
        pInterface(NULL)
        {}
    };
    
    ///-------------------- function pointer type
    typedef bool (cocos2d::Ref::*FUN_SCButtonFunctor_t)();
    typedef bool (cocos2d::Ref::*FUN_SCButtonSenderFunctor_t)(cocos2d::MenuItem*);
    typedef void (cocos2d::Ref::*FUN_SCDelayExecuteFunction_t)(void* pData);
    
    ///-------------------- type definition
//    typedef std::map<SCString,SCValue>      SCDictionary;
}


#endif //__SC__BASEDEF_H__
