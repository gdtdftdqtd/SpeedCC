
#include "TestProgressController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestProgressController::onCreate(SCDictionary parameters)
{
    TestCaseController::onCreate(parameters);

    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseBarBasic, this)));
    _ptrCaseBvr->setCase(1, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseRadialBasic, this)));
    
    _ptrCaseBvr->execute();
}

void TestProgressController::testCaseBarBasic()
{
    (*_ptrWatchDescription) = "(Bar Basic)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
    
        SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,20,SCNodeUtils::kDockCenter)
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, left to right, horizontal, 60%)", "", 15)
                SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_bk.png", "progressbar_ft.png", 60, true, true)
            SC_END_CONTAINER
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, right to left, horizontal, 30%)", "", 15)
                SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_bk.png", "progressbar_ft.png", 30, true, false)
            SC_END_CONTAINER
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,20,SCNodeUtils::kDockCenter)
    
                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, down to up, vertical, 30%)", "", 15)
                    SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_v_bk.png", "progressbar_v_ft.png", 30, false,  true)
                SC_END_CONTAINER

                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, up to down, vertical, 30%)", "", 15)
                    SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_v_bk.png", "progressbar_v_ft.png", 30, false, false)
                SC_END_CONTAINER
    
            SC_END_CONTAINER
    
        SC_END_CONTAINER
    
    SC_END_CONTAINER
}

void TestProgressController::testCaseRadialBasic()
{
    (*_ptrWatchDescription) = "(Radial Basic)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
    
        SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,20,SCNodeUtils::kDockCenter)
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(radial, cw, 60%)", "", 15)
                SC_INSERT_PROGRESS_RADIAL(NULL, 0, 0, "", "HelloWorld.png", "mask.png", 60,false)
            SC_END_CONTAINER
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(radial, ccw, 60%)", "", 15)
                SC_INSERT_PROGRESS_RADIAL(NULL, 0, 0, "", "HelloWorld.png", "mask.png", 60,true)
            SC_END_CONTAINER
    
        SC_END_CONTAINER
    SC_END_CONTAINER
}

void TestProgressController::testCaseBarBinder()
{
    (*_ptrWatchDescription) = "(Bar Binder)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
    
        SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,20,SCNodeUtils::kDockCenter)
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, left to right, horizontal, 60%)", "", 15)
    
                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,5,SCNodeUtils::kDockCenter)
                    
                    SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_bk.png", "progressbar_ft.png", 60, true, true)
                SC_END_CONTAINER
    
            SC_END_CONTAINER

            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, right to left, horizontal, 30%)", "", 15)
                SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_bk.png", "progressbar_ft.png", 30, true, false)
            SC_END_CONTAINER

    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,20,SCNodeUtils::kDockCenter)

                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, down to up, vertical, 30%)", "", 15)
                    SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_v_bk.png", "progressbar_v_ft.png", 30, false,  true)
                SC_END_CONTAINER

                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", "(bar, up to down, vertical, 30%)", "", 15)
                    SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_v_bk.png", "progressbar_v_ft.png", 30, false, false)
                SC_END_CONTAINER
    
            SC_END_CONTAINER
    
        SC_END_CONTAINER
    
    SC_END_CONTAINER
}


void TestProgressController::testCaseRadialBinder()
{
    
}



