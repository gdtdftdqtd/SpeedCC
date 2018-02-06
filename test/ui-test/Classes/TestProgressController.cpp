
#include "TestProgressController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestProgressController::onCreate(SCDictionary parameters)
{
    TestCaseController::onCreate(parameters);

//    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,NULL)
//        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)
//            // title
//            SC_INSERT_LABEL_BMFONT(NULL,0.5,0.90,"","Progress Scene","blue_font.fnt")
//            // back
//            SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black; dock=left|top; x-by=3; y-by=-3;", "Back", "", 22, SCBehaviorSceneBack::create())
//            SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "dock=center;", "progressbar_bk.png", "progressbar_ft.png", 50, true, false, true)
//        SC_END_CONTAINER
//    SC_END_CONTAINER
    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseBase, this)));
    
    _ptrCaseBvr->execute();
}

void TestProgressController::testCaseBase()
{
    (*_ptrWatchDescription) = "(Base)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
    
        SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,10,SCNodeUtils::kDockCenter)
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, left to right, horizontal, 50%)", "", 15)
                SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_bk.png", "progressbar_ft.png", 50, true, false, true)
            SC_END_CONTAINER
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, right to left, horizontal, 50%)", "", 15)
                SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_bk.png", "progressbar_ft.png", 50, true, false, false)
            SC_END_CONTAINER
    
        SC_END_CONTAINER
    
    SC_END_CONTAINER
}

