//
//  TestPage1Controller.cpp
//  UITest-mobile
//
//  Created by Kevin on 10/12/2017.
//

#include "TestPage1Controller.h"

using namespace SpeedCC;

void TestPage1Controller::onCreate(SCDictionary parameters)
{
    SCSceneControllerT::onCreate(parameters);
    
    SC_BEGIN_CONTAINER_ROOT(NULL,0,0,NULL,SCWinSize())
        SC_INSERT_LABEL(NULL,0,0.8,"","Page 1","",23)
        SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=red;","back","",23,FN(onButtonClicked))
    SC_END_CONTAINER
}

void TestPage1Controller::onButtonClicked()
{
    SCSceneNavigator::back();
}
