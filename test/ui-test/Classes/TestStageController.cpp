
#include "TestStageController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestStageController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,SCWinSize())

        // title
        SC_INSERT_LABEL_BMFONT(NULL,0.5,0.95,"","Test Stage","blue_font.fnt")
    
        // binding number
        SC_INSERT_BUTTON_LABEL(NULL,0.6,0.75,"color-text=red;","click","",33,SCF(onButtonAdd))

        // back
        SC_INSERT_BUTTON_LABEL(NULL,0.05,0.95,"color-text=red;","back","",25,SCF(onButtonBack))
    SC_END_CONTAINER
    
}

void TestStageController::setUpStage()
{
    SC_BEGIN_ROLE(123,0,this)
        IN_STRATEGY(22)
            ON_ENTER_STRATEGE(SCBehaviorCallFunc::create())
            ON_EXIT_STRATEGE(SCBehaviorCallFunc::create())
            ON_MSG_BEHAVIOR(11,SCBehaviorCallFunc::create())
            ON_CMD_BEHAVIOR("eee",SCBehaviorCallFunc::create())
        ENDIN_STRATEGY
    
        IN_STRATEGY(24)
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
    return NULL;
}

void TestStageController::onButtonAdd()
{
    
}

void TestStageController::onButtonBack()
{
    SCSceneNav()->back();
}


