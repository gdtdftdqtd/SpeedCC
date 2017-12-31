#ifndef __TESTSTAGE_SCENE_H__
#define __TESTSTAGE_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

using namespace SpeedCC;

class TestStageController : public SpeedCC::SCSceneController
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    virtual void onSetupStage();
    virtual SCRole::Ptr onCreateRole(const SCString& strName);
    virtual SCStrategy::Ptr onCreateStrategy(const SCString& strName);
    
    void onButtonAdd();
    void onButtonBack();

    
private:

};

#endif // __TESTSTAGE_SCENE_H__
