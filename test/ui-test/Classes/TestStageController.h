#ifndef __TESTSTAGE_SCENE_H__
#define __TESTSTAGE_SCENE_H__

#include "cocos2d.h"
#include "SpeedCC.h"

using namespace SpeedCC;

class TestStageController : public SpeedCC::SCSceneController
{
public:
    
    virtual void onCreate(SpeedCC::SCDictionary parameters);
    virtual SCStrategy::Ptr onCreateStrategy(const int nID) override;
    
    void setUpStage();
    
    void onButtonAdd();
    void onStrategyCommon(SCActor* pActor,SCMessage::Ptr ptrMsg);
    void onEnterStrategy(const SCDictionary& par);
    void onExitStrategy(const SCDictionary& par);
    
private:

};

#endif // __TESTSTAGE_SCENE_H__
