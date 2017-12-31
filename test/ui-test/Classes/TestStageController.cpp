
#include "TestStageController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestStageController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    SC_BEGIN_CONTAINER_ROOT(NULL,0.5,0.5,NULL,SCWinSize())

        // title
        SC_INSERT_LABEL_BMFONT(NULL,0.5,0.95,"","Test Stage","blue_font.fnt")
    
        // binding number
        SC_INSERT_BUTTON_LABEL(NULL,0.6,0.75,"color-text=red;","click","",33,SCF(onButtonAdd))

        // back
        SC_INSERT_BUTTON_LABEL(NULL,0.05,0.95,"color-text=red;","back","",25,SCF(onButtonBack))
    SC_END_CONTAINER
    
}

void TestStageController::onSetupStage()
{
//    SC_BEGIN_ROLE("test_role",NULL)
//    SC_END_ROLE
}

SCRole::Ptr TestStageController::onCreateRole(const SCString& strName)
{
    return NULL;
}

SCStrategy::Ptr TestStageController::onCreateStrategy(const SCString& strName)
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


