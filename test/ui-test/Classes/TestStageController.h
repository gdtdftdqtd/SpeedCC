#ifndef __TESTSTAGE_SCENE_H__
#define __TESTSTAGE_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

using namespace SpeedCC;

class TestStageController : public SpeedCC::SCSceneController
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    virtual void onStageSetup() override;
    virtual SCRole::Ptr onCreateRole(const int nID) override;
    virtual SCStrategy::Ptr onCreateStrategy(const int nID) override;
    
    void onButtonAdd();
    void onButtonBack();

    
private:

};

#endif // __TESTSTAGE_SCENE_H__
