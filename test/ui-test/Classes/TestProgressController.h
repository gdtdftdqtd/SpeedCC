#ifndef __TESTPROGRESS_SCENE_H__
#define __TESTPROGRESS_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"
#include "TestCaseController.h"

class TestProgressController : public TestCaseController
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    void testCaseBase();
    
};

#endif // __TESTPROGRESS_SCENE_H__
