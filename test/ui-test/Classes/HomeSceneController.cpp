
#include "HomeSceneController.h"
//#include <list>

USING_NS_CC;

using namespace SpeedCC;

void HomeSceneController::onCreate(SCDictionary parameters)
{
    SCSceneControllerT::onCreate(parameters);

    SC_BEGIN_CONTAINER_ROOT(NULL,0,0,NULL,SCWinSize())
        SC_INSERT_SPRITE(NULL,0,0,NULL,"HelloWorld.png")
    SC_END_CONTAINER
}


