#ifndef __TESTHOME_SCENE_H__
#define __TESTHOME_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

class TestHomeController : public SpeedCC::SCSceneControllerT<TestHomeController>
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    
    void onButtonClicked();
    void onButtonClicked2();
};

#endif // __TESTHOME_SCENE_H__
