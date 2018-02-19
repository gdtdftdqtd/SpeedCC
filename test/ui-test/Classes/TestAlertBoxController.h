#ifndef __TESTALERTBOX_SCENE_H__
#define __TESTALERTBOX_SCENE_H__
#include "cocos2d.h"
#include "SpeedCC.h"
#include "TestCaseController.h"

using namespace SpeedCC;

///--------- TestAlertBoxController
class TestAlertBoxController : public TestCaseController
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters) override;
    void setupUI();
    
    void showSystemAlertBox();
    void showCustomizeAlertBox();
};

///---------- TestCustomizeABController
class TestCustomizeABController : public SCSceneController
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters) override;
};

#endif // __TESTALERTBOX_SCENE_H__
