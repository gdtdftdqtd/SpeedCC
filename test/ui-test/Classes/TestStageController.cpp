
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
    
    kTestMsgIDStart,
    kTestMsgIDStop,
};

void TestStageController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    auto ptrBvrStart = SCBehaviorDeliverMessage::create(false, kTestMsgIDStart);
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)

            // title
            SC_INSERT_LABEL_BMFONT(NULL,0,0,"dock=top|middle-x; y-by=-100;","Test Stage","blue_font.fnt")
    
            // binding number
//            SC_INSERT_BUTTON_LABEL(NULL,0.6,0.75,"color-text=red;","click","",33,SCF(onButtonAdd))

            // back button
            SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black; dock=left|top; x-by=3; y-by=-3;", "Back", "", 22, SCBehaviorSceneBack::create())
        SC_END_CONTAINER
    SC_END_CONTAINER
    
}

void TestStageController::setUpStage()
{
    
    SC_BEGIN_ROLE(kTestRoleID1,kTestStrategyID1,this)
        IN_STRATEGY(kTestStrategyID2)
            ON_ENTER_STRATEGE(SCBehaviorCallFunc::create())
            ON_EXIT_STRATEGE(SCBehaviorCallFunc::create())
    
            IN_STRATEGY(kTestStrategyID4)
            ENDIN_STRATEGY
//            ON_MSG_BEHAVIOR(11,SCBehaviorCallFunc::create())
//            ON_CMD_BEHAVIOR("eee",SCBehaviorCallFunc::create())
        ENDIN_STRATEGY
    
        IN_STRATEGY(kTestStrategyID3)
            ON_ENTER_STRATEGE(SCBehaviorCallFunc::create())
            ON_EXIT_STRATEGE(SCBehaviorCallFunc::create())
            ON_MSG_BEHAVIOR(11,SCBehaviorCallFunc::create())
            ON_CMD_BEHAVIOR("eee",SCBehaviorCallFunc::create())
        ENDIN_STRATEGY
    
        ON_MSG_BEHAVIOR(11,SCBehaviorCallFunc::create())
    SC_END_ROLE
}

SCStrategy::Ptr TestStageController::onCreateStrategy(const int nID)
{
    return SCStrategyFunc::create(nID, SC_MAKE_FUNC(onStrategyCommon, this));
}

void TestStageController::onStrategyCommon(SCActor* pActor,SCMessage::Ptr ptrMsg)
{
    SCLog("strategy called. ID: %d",pActor->getStrategy()->getID());
}

void TestStageController::onEnterStrategy(const SCDictionary& par)
{
    auto ptrActor = par.getValue(SC_BVR_ARG_ACTOR).getObject<SCActor::Ptr>();
//    auto ptrMsg = par.getValue(SC_BVR_ARG_MESSAGE).getObject<SCMessage::Ptr>();
    
    SCLog("enter strategy called. ID: %d",ptrActor->getStrategy()->getID());
}

void TestStageController::onExitStrategy(const SCDictionary& par)
{
    auto ptrActor = par.getValue(SC_BVR_ARG_ACTOR).getObject<SCActor::Ptr>();
    //    auto ptrMsg = par.getValue(SC_BVR_ARG_MESSAGE).getObject<SCMessage::Ptr>();
    
    SCLog("exit strategy called. ID: %d",ptrActor->getStrategy()->getID());
}

void TestStageController::onButtonAdd()
{
    
}



