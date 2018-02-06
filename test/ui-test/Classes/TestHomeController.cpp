
#include "TestHomeController.h"
#include "TestLabelBinderController.h"
#include "TestStageController.h"
#include "TestDockController.h"
#include "TestProgressController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestHomeController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);

    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,NULL)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)
            SC_INSERT_LABEL_BMFONT(NULL,0.5,0.90,"","Home Scene","blue_font.fnt")
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,20,SCNodeUtils::kDockCenter)
    
                SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","Label Binder","",23,SCBehaviorSceneNavigate::create<TestLabelBinderController>())
    
                SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","Stage","",23,SCBehaviorSceneNavigate::create<TestStageController>())
    
                SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","Dock","",23,SCBehaviorSceneNavigate::create<TestDockController>())
    
                SC_INSERT_BUTTON_LABEL(NULL,0,0,"color-text=blue;","Progress","",23,SCBehaviorSceneNavigate::create<TestProgressController>())
    
            SC_END_CONTAINER
        SC_END_CONTAINER
    SC_END_CONTAINER
}


