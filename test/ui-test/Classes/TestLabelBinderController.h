#ifndef __TESTLABELBINDER_SCENE_H__
#define __TESTLABELBINDER_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

using namespace SpeedCC;

class TestLabelBinderController : public SpeedCC::SCSceneController
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters) override;
    
    void onButtonAdd();
    void onButtonSub();
    void onButtonRandomText();
    void onButtonBack();
    
private:
    SCWatchInt::Ptr         _watchIntPtr;
    SCWatchString::Ptr      _watchStrPtr;
};

#endif // __TESTLABELBINDER_SCENE_H__
