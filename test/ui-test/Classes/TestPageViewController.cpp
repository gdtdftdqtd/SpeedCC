
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
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, nullptr, SCWinSize, _pContainerLayer, this)
    
        SC_BEGIN_CONTAINER_PAGEVIEW(nullptr,0.5,0.5,nullptr,true,Size(SCWinSize.width*2/3,SCWinSize.height/2),0,nullptr)
            SC_BEGIN_CONTAINER_PAGE(nullptr, SCWinSize)
                SC_INSERT_SPRITE(nullptr, 0.5, 0.5, nullptr, "HelloWorld.png")
            SC_END_CONTAINER

            SC_BEGIN_CONTAINER_PAGE(nullptr, SCWinSize)
                SC_INSERT_SPRITE(nullptr, 0.5, 0.5, nullptr, "HelloWorld.png")
            SC_END_CONTAINER

        SC_END_CONTAINER
    
    SC_END_CONTAINER
}
