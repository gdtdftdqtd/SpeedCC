#ifndef __TESTHOME_SCENE_H__
#define __TESTHOME_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

class HomeSceneController : public SpeedCC::SCSceneControllerT<HomeSceneController>
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    
    void onButtonClicked();
};

#endif // __TESTHOME_SCENE_H__
