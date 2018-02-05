#ifndef __TESDOCK_SCENE_H__
#define __TESDOCK_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

using namespace SpeedCC;

class TestDockController : public SpeedCC::SCSceneController
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    
    void testCaseNoScale();
    void testCaseWithScale();
    void testCaseWithScaleAnchor();
    void testCaseNoScaleWithAnchor();
    
private:
    cocos2d::Layer*                 _pContainerLayer;
    SCWatchString::Ptr              _ptrWatchDescription;
    SCBehaviorCaseInt::Ptr          _ptrCaseBvr;
    cocos2d::MenuItemSprite*        _pNextMenuItem;
    cocos2d::MenuItemSprite*        _pPreMenuItem;
};

#endif // __TESTHOME_SCENE_H__
