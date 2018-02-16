
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
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)
            
        SC_END_CONTAINER
    SC_END_CONTAINER
}
