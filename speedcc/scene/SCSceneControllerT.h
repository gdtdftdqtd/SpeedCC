

#ifndef __SPEEDCC__SCSCENECONTROLLERT_H__
#define __SPEEDCC__SCSCENECONTROLLERT_H__

#include "cocos2d.h"
#include "SCSceneLayer.h"
#include "SCEventListener.h"
#include "../base/SCBaseCommon.h"

namespace SpeedCC
{
    template<typename TargetCtlerT>
    class SCSceneControllerT :
    public cocos2d::Ref,
    public SCEventListener
    {
    public:
        virtual void onCreate(SCParameters parameters);
        
        
    protected:
        SCSceneLayer*   _pSceneLayer;
    };
}

#endif // __SPEEDCC__SCSCENECONTROLLERT_H__
