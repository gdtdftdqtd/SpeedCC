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
    
    void setupUI();
    void setupStage();
    void setupRole();
    
    void onStrategyCommon(SCActor* pActor,SCMessage::Ptr ptrMsg);
    void onBvrEnterStrategy(const SCDictionary& par);
    void onBvrExitStrategy(const SCDictionary& par);
    void onBvrLog(const SCDictionary& par);
    
    void onSchedule(float fDelta);
    
    SCString getStrategyName(const int nID);
    
private:
    SCWatchBool::Ptr    _ptrWatchRun;
};

#endif // __TESTSTAGE_SCENE_H__
