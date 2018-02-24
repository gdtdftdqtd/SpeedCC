/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

#include "TestStageController.h"

USING_NS_CC;

using namespace SpeedCC;

enum ETestStageID
{
    kTestUserID = SCID::kSCUserID,
    
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
    parameters.setValue("title", "Test Stage");
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
                                                      SCLog("Timer Started.");
                                                  });
    
    auto ptrBvrStop = SCBehaviorCallFunc::create([this]()
                                                 {
                                                     this->unschedule(SCF(onSchedule));
                                                     SCLog("Timer Stopped.");
                                                 });
    
    auto ptrWatchBool = SCWatchBool::create();
    _ptrTrigger = SCTriggerBool::create(ptrWatchBool);
    _ptrTrigger->addCondition(SCTriggerBool::EComparsion::kEqual, true, ptrBvrStart);
    _ptrTrigger->addCondition(SCTriggerBool::EComparsion::kEqual, false, ptrBvrStop);
    
    
    SC_BEGIN_CONTAINER_ROOT(nullptr,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,"dock=center;",SCWinSize,Color4B::GRAY)

            // title
            SC_INSERT_LABEL_BMFONT(nullptr,"dock=top|mid-x; y-by=-100;","Test Stage","blue_font.fnt")

            SC_INSERT_BUTTON_SWITCH(nullptr, "x=0.5; y=0.6;", SCUIArg::MenuItemPurifier("Stop",22), SCUIArg::MenuItemPurifier("Start",22), ptrWatchBool, nullptr)
    
            SC_INSERT_BUTTON_LABEL(nullptr, "x=0.5; y=0.4;", "Message Log", "", 20, ptrBvrMsgLog)
            SC_INSERT_BUTTON_LABEL(nullptr, "x=0.5; y=0.3;", "Command Log", "", 20, ptrBvrCmdLog)

            // back button
            SC_INSERT_BUTTON_LABEL(nullptr, "color-text=black; dock=left|top; x-by=3; y-by=-3;", "Back", "", 22, SCBehaviorSceneBack::create())
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
    if(*(_ptrTrigger->getWatch()))
    {
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


