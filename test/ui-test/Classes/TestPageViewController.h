#ifndef __TESTPAGEVIEW_SCENE_H__
#define __TESTPAGEVIEW_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"
#include "TestCaseController.h"

using namespace SpeedCC;

///--------- TestPageViewController
class TestPageViewController : public TestCaseController
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    
    void setupUI();
    
private:

};


#endif // __TESTPAGEVIEW_SCENE_H__
