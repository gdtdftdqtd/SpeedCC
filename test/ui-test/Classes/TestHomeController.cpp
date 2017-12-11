
#include "TestHomeController.h"
#include "TestPage1Controller.h"

USING_NS_CC;

using namespace SpeedCC;

void TestHomeController::onCreate(SCDictionary parameters)
{
    SCSceneControllerT::onCreate(parameters);

    SC_BEGIN_CONTAINER_ROOT(NULL,0,0,NULL,SCWinSize())
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,NULL,SCWinSize(),Color4B::RED)
            SC_INSERT_LABEL_BMFONT(NULL,0,0.8,"","Home Scene","fonts/blue_font.fnt")
            SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","go to page 1","",23,FN(onButtonClicked))
            SC_INSERT_BUTTON_LABEL(NULL,0.8,0.8,NULL,"click","",23,FN(onButtonClicked2))
        SC_END_CONTAINER
    SC_END_CONTAINER
}

void TestHomeController::onButtonClicked()
{
    SCSceneNavigator::switchScene<TestPage1Controller>(SCSceneNavigator::SWITCH_MODAL);
}

void TestHomeController::onButtonClicked2()
{
    int ppp = 0;
}

