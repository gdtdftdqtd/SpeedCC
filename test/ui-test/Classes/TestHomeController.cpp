
#include "TestHomeController.h"
#include "TestLabelBinderController.h"
#include "TestStageController.h"
#include "TestDockController.h"
#include "TestProgressController.h"
#include "TestLoadingController.h"
#include "TestPageViewController.h"
#include "TestUIMiscController.h"

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
    
                    SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=black;","Label Binding","",23,SCBehaviorSceneNavigate::create<TestLabelBinderController>())
    
                    SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=black;","Stage","",23,SCBehaviorSceneNavigate::create<TestStageController>())
    
                    SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=black;","Dock","",23,SCBehaviorSceneNavigate::create<TestDockController>())
    
                    SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=black;","Progress","",23,SCBehaviorSceneNavigate::create<TestProgressController>())
    
        auto ptrLoadingBvr = SCBehaviorSceneNavigate::create<TestLoadingTraget0Controller,SCClassNull,TestLoadingController>();
                    SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=black;","Loading","",23,ptrLoadingBvr)
    
                    SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=black;","PageView","",23,SCBehaviorSceneNavigate::create<TestPageViewController>())
    
                    SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=black;","PageView","",23,SCBehaviorSceneNavigate::create<TestPageViewController>())
    
                    SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=black;","UI Misc","",23,SCBehaviorSceneNavigate::create<TestUIMiscController>())
    
                SC_END_CONTAINER
            SC_END_CONTAINER
        SC_END_CONTAINER
    SC_END_CONTAINER
}


