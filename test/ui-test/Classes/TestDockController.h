#ifndef __TESDOCK_SCENE_H__
#define __TESDOCK_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"
#include "TestCaseController.h"

using namespace SpeedCC;

class TestDockController : public TestCaseController
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    
    void testCaseNoScale();
    void testCaseWithScale();
    void testCaseWithScaleAnchor();
    void testCaseNoScaleWithAnchor();
    
};

#endif // __TESTHOME_SCENE_H__
