
#include "TestStageController.h"

USING_NS_CC;

using namespace SpeedCC;

enum ETestStageID
{
    kTestUserID = 65536,
    
    kTestRoleID1,
    
    kTestStrategyID1,
    kTestStrategyID2,
    kTestStrategyID3,
    kTestStrategyID4,
    
    kTestMsgIDLog,
    kTestMsgIDNextStrategy,
};

#define kTestCmdLog "cmd_log"

struct SActorProperty1 : SCObject
{
};

void TestStageController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    this->setupUI();
    this->setupStage();
    this->setupRole();
}
    
void TestStageController::setupUI()
{
    auto ptrBvrMsgLog = SCBehaviorDeliverMessage::create(false, kTestMsgIDLog);
    auto ptrBvrCmdLog = SCBehaviorDeliverMessage::create(false, kTestCmdLog);
    
    auto ptrBvrStart = SCBehaviorCallFunc::create([this]()
                                                  {
                                                      this->schedule(SCF(onSchedule), 1.5f);
                                                  });
    
    auto ptrBvrStop = SCBehaviorCallFunc::create([this]()
                                                 {
                                                     this->unschedule(SCF(onSchedule));
                                                 });
    
    auto ptrRunBvr = SCBehaviorCaseBool::create();
    _ptrWatchRun = ptrRunBvr->getWatch();
    (*_ptrWatchRun) = false;
    ptrRunBvr->setCase(true, ptrBvrStart);
    ptrRunBvr->setCase(false, ptrBvrStop);
    
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::GRAY)

            // title
            SC_INSERT_LABEL_BMFONT(NULL,0,0,"dock=top|middle-x; y-by=-100;","Test Stage","blue_font.fnt")

            SC_INSERT_BUTTON_SWITCH(NULL, 0.5, 0.6, "", SCUIArg::MenuItemPurifier("Stop",22), SCUIArg::MenuItemPurifier("Start",22), _ptrWatchRun, ptrRunBvr)
    
            SC_INSERT_BUTTON_LABEL(NULL, 0.5, 0.4, NULL, "Message Log", "", 20, ptrBvrMsgLog)
            SC_INSERT_BUTTON_LABEL(NULL, 0.5, 0.3, NULL, "Command Log", "", 20, ptrBvrCmdLog)

            // back button
            SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black; dock=left|top; x-by=3; y-by=-3;", "Back", "", 22, SCBehaviorSceneBack::create())
        SC_END_CONTAINER
    SC_END_CONTAINER
}

void TestStageController::setupStage()
{
    auto ptrBvrLog = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrLog, this));
    auto ptrBvrEnter = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrEnterStrategy, this));
    auto ptrBvrExit = SCBehaviorCallFunc::create(SC_MAKE_FUNC(onBvrExitStrategy, this));
    
    SC_BEGIN_ROLE(kTestRoleID1,kTestStrategyID1,this)
        IN_STRATEGY(kTestStrategyID2)
            ON_ENTER_STRATEGE(ptrBvrEnter)
            ON_EXIT_STRATEGE(ptrBvrExit)
            ON_MSG_NEXT_STRATEGY(kTestMsgIDNextStrategy, kTestStrategyID3)
            ON_MSG_BEHAVIOR(kTestMsgIDLog,ptrBvrLog)
            ON_CMD_BEHAVIOR(kTestCmdLog, ptrBvrLog)
    
            IN_STRATEGY(kTestStrategyID3)
                ON_ENTER_STRATEGE(ptrBvrEnter)
                ON_EXIT_STRATEGE(ptrBvrExit)
                ON_MSG_NEXT_STRATEGY(kTestMsgIDNextStrategy, kTestStrategyID4)
    
                ON_MSG_BEHAVIOR(kTestMsgIDLog,ptrBvrLog)
                ON_CMD_BEHAVIOR(kTestCmdLog, ptrBvrLog)
            ENDIN_STRATEGY
        ENDIN_STRATEGY
    
        IN_STRATEGY(kTestStrategyID4)
            ON_ENTER_STRATEGE(ptrBvrEnter)
            ON_EXIT_STRATEGE(ptrBvrExit)
            ON_MSG_NEXT_STRATEGY(kTestMsgIDNextStrategy, kTestStrategyID1)
    
            ON_MSG_BEHAVIOR(kTestMsgIDLog,ptrBvrLog)
            ON_CMD_BEHAVIOR(kTestCmdLog, ptrBvrLog)
        ENDIN_STRATEGY
    
        ON_ENTER_STRATEGE(ptrBvrEnter)
        ON_EXIT_STRATEGE(ptrBvrExit)
        ON_MSG_BEHAVIOR(kTestMsgIDLog,ptrBvrLog)
        ON_CMD_BEHAVIOR(kTestCmdLog, ptrBvrLog)
        ON_MSG_NEXT_STRATEGY(kTestMsgIDNextStrategy, kTestStrategyID2)
    SC_END_ROLE
}

SCStrategy::Ptr TestStageController::onCreateStrategy(const int nID)
{
    return SCStrategyFunc::create(nID, SC_MAKE_FUNC(onStrategyCommon, this));
}

void TestStageController::setupRole()
{
    this->createActor2Role<SActorProperty1>(kTestRoleID1);
}

void TestStageController::onStrategyCommon(SCActor* pActor,SCMessage::Ptr ptrMsg)
{
    SCLog("Strategy Called. ID: %s",this->getStrategyName(pActor->getStrategy()->getID()).c_str());
}

void TestStageController::onBvrEnterStrategy(const SCDictionary& par)
{
    auto ptrActor = par.getValue(SC_KEY_ACTOR).getObject<SCActor::Ptr>();
    
    SCLog("Enter Strategy Called. ID: %s",this->getStrategyName(ptrActor->getStrategy()->getID()).c_str());
}

void TestStageController::onBvrExitStrategy(const SCDictionary& par)
{
    auto ptrActor = par.getValue(SC_KEY_ACTOR).getObject<SCActor::Ptr>();
    
    SCLog("Exit Strategy Called. ID: %s",this->getStrategyName(ptrActor->getStrategy()->getID()).c_str());
}

void TestStageController::onBvrLog(const SCDictionary& par)
{
    auto ptrActor = par.getValue(SC_KEY_ACTOR).getObject<SCActor::Ptr>();
    auto ptrMsg = par.getValue(SC_KEY_MESSAGE).getObject<SCMessage::Ptr>();
    
    SCString strName;
    if(ptrMsg->nMsgID==kTestMsgIDLog)
    {
        strName = "Message";
    }
    else if(ptrMsg->nMsgID==SCID::Msg::kSCMsgCommand)
    {
        strName = "Command";
    }
    SCLog("Behavior Log From [%s]. ID: %s",strName.c_str(),this->getStrategyName(ptrActor->getStrategy()->getID()).c_str());
}

void TestStageController::onSchedule(float fDelta)
{
    if(*_ptrWatchRun)
    {
//        SCLog("Post Message: kTestMsgIDNextStrategy");
        SCMsgDisp()->postMessage(kTestMsgIDNextStrategy);
    }
}

SCString TestStageController::getStrategyName(const int nID)
{
    switch(nID)
    {
        case kTestStrategyID1: return "kTestStrategyID1";
        case kTestStrategyID2: return "kTestStrategyID2";
        case kTestStrategyID3: return "kTestStrategyID3";
        case kTestStrategyID4: return "kTestStrategyID4";
    }
    
    return "Unknown Strategy ID";
}


