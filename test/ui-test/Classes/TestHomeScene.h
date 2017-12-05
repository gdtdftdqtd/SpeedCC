#ifndef __TESTHOME_SCENE_H__
#define __TESTHOME_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

class TestHomeScene : public SpeedCC::SCSceneControllerT<TestHomeScene>
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
};

#endif // __TESTHOME_SCENE_H__
