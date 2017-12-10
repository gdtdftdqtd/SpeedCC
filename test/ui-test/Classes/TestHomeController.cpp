
#include "TestHomeController.h"
#include "TestPage1Controller.h"

USING_NS_CC;

using namespace SpeedCC;

void TestHomeController::onCreate(SCDictionary parameters)
{
    SCSceneControllerT::onCreate(parameters);

//    Sprite* pSprite = cocos2d::Sprite::create("HelloWorld.png");
    SC_BEGIN_CONTAINER_ROOT(NULL,0,0,NULL,SCWinSize())
        SC_INSERT_LABEL_BMFONT(NULL,0,0.8,"","Home Scene","fonts/blue_font.fnt")
        SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=red;","go to page 1","",23,FN(onButtonClicked))
    SC_END_CONTAINER
}

void TestHomeController::onButtonClicked()
{
    SCSceneNavigator::switchScene<TestPage1Controller>();
}


