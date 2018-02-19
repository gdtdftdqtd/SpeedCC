
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
    
        SC_BEGIN_CONTAINER_PAGEVIEW(NULL,0.5,0.5,NULL,true,Size(SCWinSize.width*2/3,SCWinSize.height/2),0,NULL)
            SC_BEGIN_CONTAINER_PAGE(NULL, SCWinSize)
                SC_INSERT_SPRITE(NULL, 0.5, 0.5, NULL, "HelloWorld.png")
            SC_END_CONTAINER

            SC_BEGIN_CONTAINER_PAGE(NULL, SCWinSize)
                SC_INSERT_SPRITE(NULL, 0.5, 0.5, NULL, "HelloWorld.png")
            SC_END_CONTAINER

        SC_END_CONTAINER
    
    SC_END_CONTAINER
}
