
#include "HomeSceneController.h"

USING_NS_CC;

using namespace SpeedCC;

void HomeSceneController::onCreate(SCDictionary parameters)
{
    SCSceneControllerT::onCreate(parameters);

    Sprite* pSprite = cocos2d::Sprite::create("HelloWorld.png");
//    SCNodeProperty::setProperty<Sprite>(pSprite, "scale=2;");
//    this->getRootLayer()->addChild(pSprite);
    SC_BEGIN_CONTAINER_ROOT(NULL,0,0,NULL,SCWinSize())
//        SC_INSERT_USER_NODE(pSprite, 0, 0, "scale=2;")
//        SC_INSERT_SPRITE(NULL,0,0,"scale=2;","HelloWorld.png")
//        SC_INSERT_BUTTON_IMAGE(NULL,0,0,NULL,"HelloWorld.png","HelloWorld.png","HelloWorld.png",FN(onButtonClicked))
//        SC_BEGIN_CONTAINER_BUTTON_IMAGE(NULL,0,0,NULL,"HelloWorld.png","HelloWorld.png","HelloWorld.png",FN(onButtonClicked))
//            SC_INSERT_LABEL_TTF(NULL,0,0,"color-text=red;","ABCDEFG","fonts/Marker Felt.ttf",23)
//    SC_BEGIN_CONTAINER_LABEL(NULL,0,0,"color-text=red;","ABCDEFG","",23)
//                SC_INSERT_SPRITE(NULL,0,0,"scale=0.4;","HelloWorld.png")
//        SC_END_CONTAINER
//        SC_BEGIN_CONTAINER_SPRITE(NULL,0,0,"scale=2;","HelloWorld.png")
//            SC_BEGIN_CONTAINER_LABEL_BMFONT(NULL,0,0,"","ABCDEFG","fonts/blue_font.fnt")
////    SC_BEGIN_CONTAINER_BUTTON_TTF(NULL,0,0,"color-text=red;","ABCDEFG","fonts/Marker Felt.ttf",23,FN(onButtonClicked))
//        SC_INSERT_SPRITE(NULL,0,0,"scale=0.4;","HelloWorld.png")
//        SC_END_CONTAINER
    
    SC_BEGIN_CONTAINER_LAYER_GRA(NULL,0,0,NULL,SCWinSize(),Color4B::RED,Color4B::GREEN,Vec2(1,1))
//    SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"scale=2;",SCWinSize(),Color4B::RED)
//        SC_INSERT_SPRITE(NULL,0,0,NULL,"HelloWorld.png")
////    SC_INSERT_BUTTON_LABEL_BMFONT(NULL,0,0,"color-text=red;","ABCDEFG","fonts/blue_font.fnt",FN(onButtonClicked))
////        SC_BEGIN_CONTAINER_USER_NODE(pSprite, 0, 0, "scale=2;")
////            SC_INSERT_LABEL_TTF(NULL,0,0,"color-text=red;","ABCDEFG","fonts/Marker Felt.ttf",23)
////        SC_END_CONTAINER
////        SC_BEGIN_CONTAINER_LABEL_TTF(NULL,0,0,"color-text=red;","ABCDEFG","fonts/Marker Felt.ttf",23)
//
        SC_END_CONTAINER
    SC_END_CONTAINER
}

void HomeSceneController::onButtonClicked()
{
    int kkk = 0;
}


