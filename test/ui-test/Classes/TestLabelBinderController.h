#ifndef __TESTLABELBINDER_SCENE_H__
#define __TESTLABELBINDER_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

using namespace SpeedCC;

class TestLabelBinderController : public SpeedCC::SCSceneControllerT<TestLabelBinderController>
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    
    void onButtonAdd();
    void onButtonSub();
    void onButtonRandomText();
    
private:
    SCWatchInt::Ptr         _watchIntPtr;
    SCWatchString::Ptr      _watchStrPtr;
};

#endif // __TESTLABELBINDER_SCENE_H__
