
#include "TestPageViewController.h"

USING_NS_CC;

using namespace SpeedCC;

///------------ TestLoadingController
void TestPageViewController::onCreate(SCDictionary parameters)
{
    parameters.setValue("title", "Test PageView");
    
    TestCaseController::onCreate(parameters);
    
    this->setupUI();
}
    
void TestPageViewController::setupUI()
{
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)
    
            SC_BEGIN_CONTAINER_PAGEVIEW(NULL,0.5,0.5,NULL,true,SCWinSize,0,NULL)
                SC_BEGIN_CONTAINER_PAGE(NULL, SCWinSize)
                    SC_INSERT_SPRITE(NULL, 0.5, 0.5, NULL, "HelloWorld.png")
                SC_END_CONTAINER
    
            SC_BEGIN_CONTAINER_PAGE(NULL, SCWinSize)
                SC_INSERT_SPRITE(NULL, 0.5, 0.5, NULL, "HelloWorld.png")
            SC_END_CONTAINER
    
            SC_END_CONTAINER
    
        SC_END_CONTAINER
    SC_END_CONTAINER
}
