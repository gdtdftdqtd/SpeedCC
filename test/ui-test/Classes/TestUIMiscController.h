#ifndef __TESTUIMISC_SCENE_H__
#define __TESTUIMISC_SCENE_H__
#include "cocos2d.h"
#include "SpeedCC.h"
#include "TestCaseController.h"

using namespace SpeedCC;

///--------- TestUIMiscController
class TestUIMiscController :
public TestCaseController,
public cocos2d::ui::EditBoxDelegate
{
public:
    virtual void onCreate(SpeedCC::SCDictionary parameters) override;
    void setupUI();
    
    virtual void editBoxReturn(cocos2d::ui::EditBox* editBox) override;
private:

};


#endif // __TESTUIMISC_SCENE_H__
