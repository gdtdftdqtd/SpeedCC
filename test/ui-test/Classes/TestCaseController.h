#ifndef __TESTCASE_SCENE_H__
#define __TESTCASE_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

using namespace SpeedCC;

class TestCaseController : public SpeedCC::SCSceneController
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    
protected:
    cocos2d::Layer*                 _pContainerLayer;
    SCWatchString::Ptr              _ptrWatchDescription;
    SCBehaviorCaseInt::Ptr          _ptrCaseBvr;
    cocos2d::MenuItemSprite*        _pNextMenuItem;
    cocos2d::MenuItemSprite*        _pPreMenuItem;
};

#endif // __TESTCASE_SCENE_H__
