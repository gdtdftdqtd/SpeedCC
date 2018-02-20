
#include "TestAlertBoxController.h"

USING_NS_CC;

using namespace SpeedCC;

///------------ TestAlertBoxController
void TestAlertBoxController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test AlertBox");
    TestCaseController::onCreate(parameters);
    this->setupUI();
}
    
void TestAlertBoxController::setupUI()
{
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, nullptr, SCWinSize, _pContainerLayer, this)
        SC_BEGIN_CONTAINER_ALIGNMENT(nullptr,0,0,"dock=center;",false,20,SCNodeUtils::kDockCenter)
            SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","Show System AlertBox","",23,
                                   SCBehaviorCallFunc::create(SC_MAKE_FUNC(showSystemAlertBox, this)))
            SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","Show Customize AlertBox","",23,
                                   SCBehaviorCallFunc::create(SC_MAKE_FUNC(showCustomizeAlertBox, this)))
        SC_END_CONTAINER
    SC_END_CONTAINER
}

void TestAlertBoxController::showSystemAlertBox()
{
    SCSystem::showAlertBox("Test Title","System AlertBox","OK","Cancel",[](int nSelectedIndex)
                           {
                               SCLog("AlertBox Selected Button, Selected Index: %d", nSelectedIndex);
                           });
}

void TestAlertBoxController::showCustomizeAlertBox()
{
    SCSystem::showAlertBox<TestCustomizeABController>("Test Title","Customize AlertBox","OK","Cancel",[](int nSelectedIndex)
                           {
                               SCLog("AlertBox Selected Button, Selected Index: %d", nSelectedIndex);
                           });
}

///------------ TestCustomizeABController
void TestCustomizeABController::onCreate(SpeedCC::SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    bool bResult = false;
    auto strTitle = parameters.getValue(SC_KEY_TITLE).getString(&bResult);
    SCASSERT(bResult);
    bResult = false;
    auto strMessage = parameters.getValue(SC_KEY_TEXT).getString(&bResult);
    SCASSERT(bResult);
    bResult = false;
    auto strButton1 = parameters.getValue(SC_KEY_STRING0).getString(&bResult);
    SCASSERT(bResult);
    bResult = false;
    auto strButton2 = parameters.getValue(SC_KEY_STRING1).getString(&bResult);
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,nullptr,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0.5,0.5,nullptr,Size(280,140),Color4B::GRAY)
            SC_INSERT_LABEL(nullptr, 0, 0, "y-by=-5; x-by=5; dock=top|left;", strTitle, "", 15)
            SC_INSERT_LABEL(nullptr,0,0,"dock=center; y-by=10;",strMessage,"",20)
    
            SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=bottom|mid-x; x-by=-50; y-by=10;",Size(70,25),Color4B::BLUE)
                SC_INSERT_BUTTON_LABEL(nullptr, 0, 0, "dock=center;", strButton1, "", 18, SCBehaviorAlertBoxSelected::create(this,0))
            SC_END_CONTAINER
    
            SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0,0,"dock=bottom|mid-x; x-by=50; y-by=10;",Size(70,25),Color4B::BLUE)
                SC_INSERT_BUTTON_LABEL(nullptr, 0, 0, "dock=center;", strButton2, "", 18, SCBehaviorAlertBoxSelected::create(this,1))
            SC_END_CONTAINER
    
        SC_END_CONTAINER
    SC_END_CONTAINER
}
