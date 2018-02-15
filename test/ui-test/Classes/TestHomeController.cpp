
#include "TestHomeController.h"
#include "TestLabelBinderController.h"
#include "TestStageController.h"
#include "TestDockController.h"
#include "TestProgressController.h"
#include "TestLoadingController.h"
#include "TestPageViewController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestHomeController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);

    auto viewSize = Size(SCWinSize.width*3/4,SCWinSize.height*2/3);
    auto containerSize = Size(viewSize.width,viewSize.height);
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,NULL)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)
            SC_INSERT_LABEL_BMFONT(NULL,0.5,0.90,"","Home Scene","blue_font.fnt")
    
    SC_BEGIN_CONTAINER_SCROLLVIEW(NULL,0.5,0.5,"",false,viewSize,containerSize,NULL)
    SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0,0,"dock=top|mid-x;",false,20,SCNodeUtils::kDockCenter)
    
                SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","Label Binding","",23,SCBehaviorSceneNavigate::create<TestLabelBinderController>())
    
                SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","Stage","",23,SCBehaviorSceneNavigate::create<TestStageController>())
    
                SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","Dock","",23,SCBehaviorSceneNavigate::create<TestDockController>())
    
                SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","Progress","",23,SCBehaviorSceneNavigate::create<TestProgressController>())
    
    auto ptrLoadingBvr = SCBehaviorSceneNavigate::create<TestLoadingTraget0Controller,SCClassNull,TestLoadingController>();
                SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","Loading","",23,ptrLoadingBvr)
    
    SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","PageView","",23,SCBehaviorSceneNavigate::create<TestPageViewController>())
    
            SC_END_CONTAINER
    SC_END_CONTAINER
        SC_END_CONTAINER
    SC_END_CONTAINER
}


