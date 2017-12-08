
#include "HomeSceneController.h"

USING_NS_CC;

using namespace SpeedCC;

void HomeSceneController::onCreate(SCDictionary parameters)
{
    SCSceneControllerT::onCreate(parameters);


//    SCNodeProperty::setProperty<Sprite>(pSprite, "scale=2;");
//    this->getRootLayer()->addChild(pSprite);
    SC_BEGIN_CONTAINER_ROOT(NULL,0,0,NULL,SCWinSize())
//        SC_INSERT_USER_NODE(pSprite, 0, 0, "scale=2;")
//        SC_INSERT_SPRITE(NULL,0,0,"scale=2;","HelloWorld.png")
        SC_INSERT_BUTTON_IMAGE(NULL,0,0,NULL,"HelloWorld.png","HelloWorld.png","HelloWorld.png",FN(onButtonClicked))
    SC_END_CONTAINER
}

void HomeSceneController::onButtonClicked()
{
    int kkk = 0;
}


