
#include "TestHomeController.h"
#include "TestPage1Controller.h"
#include "TestLabelBinderController.h"
#include "TestStageController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestHomeController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);

    SC_BEGIN_CONTAINER_ROOT(NULL,0.5,0.5,NULL,SCWinSize())
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize(),Color4B::RED)
            SC_INSERT_SPRITE(NULL, 0.75, 0.75, NULL, "HelloWorld.png")
            SC_INSERT_LABEL_BMFONT(NULL,0.5,0.90,"","Home Scene","blue_font.fnt")
            SC_INSERT_BUTTON_LABEL(NULL,0.5,0.6,"color-text=blue;","Label Binder","",23,SCF(onButtonClicked))
            SC_INSERT_BUTTON_LABEL(NULL,0.5,0.4,"color-text=blue;","Stage","",23,SCF(onButtonStage))
//            SC_INSERT_BUTTON_LABEL(NULL,0.8,0.8,NULL,"click","",23,FN(onButtonClicked2))
        SC_END_CONTAINER
    SC_END_CONTAINER
}

void TestHomeController::onButtonClicked()
{
    SCSceneNav()->switchScene<TestLabelBinderController>(SCSceneNavigator::SWITCH_REPLACE);
}

void TestHomeController::onButtonStage()
{
    SCSceneNav()->switchScene<TestStageController>(SCSceneNavigator::SWITCH_REPLACE);
}

