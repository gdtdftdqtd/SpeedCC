
#include "TestUIMiscController.h"

USING_NS_CC;

using namespace SpeedCC;

///------------ TestLoadingController
void TestUIMiscController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test UI Misc");
    TestCaseController::onCreate(parameters);
    this->setupUI();
}
    
void TestUIMiscController::setupUI()
{
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
        SC_INSERT_EDITBOX(NULL,0.5,0.5,NULL,Size(100,26),"progressbar_bk.png",this)
    SC_END_CONTAINER
}

void TestUIMiscController::editBoxReturn(ui::EditBox* editBox)
{
    SCLog("editbox text: %s",editBox->getText());
}
