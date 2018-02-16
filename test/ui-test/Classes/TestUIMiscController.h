#ifndef __TESTUIMISC_SCENE_H__
#define __TESTUIMISC_SCENE_H__
#include "cocos2d.h"
#include "SpeedCC.h"
#include "TestCaseController.h"

using namespace SpeedCC;

///--------- TestUIMiscController
class TestUIMiscController : public TestCaseController
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    void setupUI();
    
private:

};


#endif // __TESTUIMISC_SCENE_H__
