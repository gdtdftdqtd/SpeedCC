
#include "TestLoadingController.h"

USING_NS_CC;

using namespace SpeedCC;

///------------ TestLoadingController
void TestLoadingController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    this->setupUI();
}
    
void TestLoadingController::setupUI()
{
    _ptrWatchStr = SCWatchString::create();
    _nCounter = 4;
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)
            // title
            SC_INSERT_LABEL_BMFONT(NULL,0,0,"dock=top|mid-x; y-by=-100;","Test Loading","blue_font.fnt")
    
            SC_INSERT_LABEL(NULL, 0, 0, "dock=center; color-text=black;", _ptrWatchStr, "", 20)
        SC_END_CONTAINER
    SC_END_CONTAINER
    
    this->listenMessage(SCID::Msg::kSCMsgSceneEnter, [this](SCMessage::Ptr ptrMsg)
                        {
                            this->schedule(SCF(onTimer), 1);
                        });
    
    this->onTimer(0);
}

void TestLoadingController::onTimer(float)
{
    if(--_nCounter<0)
    {
        this->finishLoading();
    }
    else
    {
        (*_ptrWatchStr) = SCString(0,"Time Left: %d seconds",_nCounter);
    }
}


///--------------- TestLoadingTraget0Controller
void TestLoadingTraget0Controller::onCreate(SpeedCC::SCDictionary parameters)
{
    parameters.setValue("title", "Test Target0 Loading");
    TestCaseController::onCreate(parameters);
    
    this->setupUI();
}

void TestLoadingTraget0Controller::setupUI()
{
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
        SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "dock=center; color-text=black;", "Test Back", "", 20, SCBehaviorSceneNavigate::create<TestLoadingTraget1Controller>())
    SC_END_CONTAINER
}

///--------------- TestLoadingTraget1Controller
void TestLoadingTraget1Controller::onCreate(SpeedCC::SCDictionary parameters)
{
    parameters.setValue("title", "Test Target1 Loading");
    TestCaseController::onCreate(parameters);
}






