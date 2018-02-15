
#include "TestProgressController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestProgressController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test Progress");
    TestCaseController::onCreate(parameters);

    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseBarBasic, this)));
    _ptrCaseBvr->setCase(1, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseRadialBasic, this)));
    _ptrCaseBvr->setCase(2, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseBarBinding, this)));
    _ptrCaseBvr->setCase(3, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseRadialBinding, this)));
    
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

void TestProgressController::testCaseBarBinding()
{
    (*_ptrWatchDescription) = "(Bar Binding)";
    _pContainerLayer->removeAllChildren();
    
    auto ptrInt1 = SCWatchInt::create(60);
    _ptrWatchStr1 = SCWatchString::create("(bar, left to right, horizontal, 60%)");
    ptrInt1->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr1) = SCString(0,"(bar, left to right, horizontal, %d%%)",kk);
                           });
    
    auto ptrInt2 = SCWatchInt::create(30);
    _ptrWatchStr2 = SCWatchString::create("(bar, right to left, horizontal, 30%)");
    ptrInt2->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr2) = SCString(0,"(bar, right to left, horizontal, %d%%)",kk);
                           });
    
    auto ptrInt3 = SCWatchInt::create(30);
    _ptrWatchStr3 = SCWatchString::create("(bar, down to up, vertical, 30%)");
    ptrInt3->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr3) = SCString(0,"(bar, down to up, vertical, %d%%)",kk);
                           });
    
    auto ptrInt4 = SCWatchInt::create(30);
    _ptrWatchStr4 = SCWatchString::create("(bar, right to left, horizontal, 30%)");
    ptrInt4->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr4) = SCString(0,"(bar, right to left, horizontal, %d%%)",kk);
                           });
    
    
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
    
        SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,20,SCNodeUtils::kDockCenter)
    
            // bar 1
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,10,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", _ptrWatchStr1, "", 15)
    
                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "-", "", 20,SCBehaviorAddInt::create(ptrInt1,-10))
                    SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_bk.png", "progressbar_ft.png", ptrInt1, true, true)
                    SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "+", "", 20,
                                           SCBehaviorAddInt::create(ptrInt1,10))
                SC_END_CONTAINER
    
            SC_END_CONTAINER
    
            // bar 2
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,10,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", _ptrWatchStr2, "", 15)
    
                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt2,10))
                    SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_bk.png", "progressbar_ft.png", ptrInt2, true, false)
                    SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "-", "", 20,
                                       SCBehaviorAddInt::create(ptrInt2,-10))
                SC_END_CONTAINER
    
            SC_END_CONTAINER
    
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,20,SCNodeUtils::kDockCenter)
    
                // bar 3
                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", _ptrWatchStr3, "", 15)
    
                    SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,5,SCNodeUtils::kDockCenter)
                        SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt3,10))
                        SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_v_bk.png", "progressbar_v_ft.png", ptrInt3, false, true)
                        SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "-", "", 20,
                                           SCBehaviorAddInt::create(ptrInt3,-10))
                    SC_END_CONTAINER
                SC_END_CONTAINER

                // bar 4
                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", _ptrWatchStr4, "", 15)
    
                    SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,5,SCNodeUtils::kDockCenter)
                        SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt4,10))
                        SC_INSERT_PROGRESS_BAR(NULL, 0, 0, "", "progressbar_v_bk.png", "progressbar_v_ft.png", ptrInt4, false, false)
                        SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "-", "", 20,
                                           SCBehaviorAddInt::create(ptrInt4,-10))
                    SC_END_CONTAINER
                SC_END_CONTAINER
    
            SC_END_CONTAINER
 
        SC_END_CONTAINER
    
    SC_END_CONTAINER
}


void TestProgressController::testCaseRadialBinding()
{
    (*_ptrWatchDescription) = "(Radial Binding)";
    _pContainerLayer->removeAllChildren();
    
    auto ptrInt1 = SCWatchInt::create(60);
    _ptrWatchStr1 = SCWatchString::create("(radial, cw, 60%)");
    ptrInt1->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr1) = SCString(0,"(radial, cw, %d%%)",kk);
                           });
    
    auto ptrInt2 = SCWatchInt::create(30);
    _ptrWatchStr2 = SCWatchString::create("(radial, ccw, 60%)");
    ptrInt2->addUpdateFunc([this](SCWatchInt::Ptr ptr,int n1,int n2)
                           {
                               int kk = (*ptr);
                               (*_ptrWatchStr2) = SCString(0,"(radial, ccw, %d%%)",kk);
                           });
    
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
    
        SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,20,SCNodeUtils::kDockCenter)
    
            // radial 1
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", _ptrWatchStr1, "", 15)
    
                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "-", "", 20,SCBehaviorAddInt::create(ptrInt1,-10))
                    SC_INSERT_PROGRESS_RADIAL(NULL, 0, 0, "", "HelloWorld.png", "mask.png", ptrInt1,false)
                    SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt1,10))
                SC_END_CONTAINER
            SC_END_CONTAINER
    
            // radial 2
            SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,false,5,SCNodeUtils::kDockCenter)
                SC_INSERT_LABEL(NULL, 0, 0, "color-text=black;", _ptrWatchStr2, "", 15)
    
                SC_BEGIN_CONTAINER_ALIGNMENT(NULL,0.5,0.5,NULL,true,5,SCNodeUtils::kDockCenter)
                    SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "-", "", 20,SCBehaviorAddInt::create(ptrInt2,-10))
                    SC_INSERT_PROGRESS_RADIAL(NULL, 0, 0, "", "HelloWorld.png", "mask.png", ptrInt2,true)
                    SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black;", "+", "", 20,SCBehaviorAddInt::create(ptrInt2,10))
                SC_END_CONTAINER
            SC_END_CONTAINER
    
        SC_END_CONTAINER
    SC_END_CONTAINER
}



