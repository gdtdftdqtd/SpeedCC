#ifndef __TESTPROGRESS_SCENE_H__
#define __TESTPROGRESS_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"
#include "TestCaseController.h"

class TestProgressController : public TestCaseController
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters) override;
    
    void testCaseBarBasic();
    void testCaseRadialBasic();
    
    void testCaseBarBinding();
    void testCaseRadialBinding();
    
private:
    SCWatchString::Ptr      _ptrWatchStr1;
    SCWatchString::Ptr      _ptrWatchStr2;
    SCWatchString::Ptr      _ptrWatchStr3;
    SCWatchString::Ptr      _ptrWatchStr4;
};

#endif // __TESTPROGRESS_SCENE_H__
