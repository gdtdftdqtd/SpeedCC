//
//  TestPage1Controller.cpp
//  UITest-mobile
//
//  Created by Kevin on 10/12/2017.
//

#include "TestPage1Controller.h"

USING_NS_CC;
using namespace SpeedCC;

void TestPage1Controller::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    SC_BEGIN_CONTAINER_ROOT(0,0,NULL,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,NULL,cocos2d::Size(SCWinSize.width/2,SCWinSize.height/2),Color4B::BLUE)
            SC_INSERT_LABEL(NULL,0,0.8,"","Page 1","",23)
            SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=red;","back","",23,SCF(onButtonClicked))
        SC_END_CONTAINER
    SC_END_CONTAINER
}

void TestPage1Controller::onButtonClicked()
{
    SCSceneNav()->back();
}
