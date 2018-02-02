
#include "TestDockController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestDockController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)
    
            // title
            SC_INSERT_LABEL_BMFONT(NULL,0,0,"dock=top|middle-x; y-by=-100;","Test Dock","blue_font.fnt")
    
            // center
            SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=center;",Size(80,80),Color4B::RED)
                SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "center", "", 18)
            SC_END_CONTAINER
    
            // top-left
            SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|top;",Size(80,80),Color4B::RED)
                SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n left", "", 18)
            SC_END_CONTAINER
    
            // top-middle
            SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=top|middle-x;",Size(80,80),Color4B::RED)
                SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n middle-x", "", 18)
            SC_END_CONTAINER
    
            // top-right
            SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|top;",Size(80,80),Color4B::RED)
                SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n right", "", 18)
            SC_END_CONTAINER
    
            // bottom-left
            SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|bottom;",Size(80,80),Color4B::RED)
                SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n left", "", 18)
            SC_END_CONTAINER
    
            // bottom-middle
            SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=bottom|middle-x;",Size(80,80),Color4B::RED)
                SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n middle-x", "", 18)
            SC_END_CONTAINER
    
            // bottom-right
            SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|bottom;",Size(80,80),Color4B::RED)
                SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n right", "", 18)
            SC_END_CONTAINER
    
            // left middle-y
            SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|middle-y;",Size(80,80),Color4B::RED)
                SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "middle-y \n left", "", 18)
            SC_END_CONTAINER
    
            // right middle-y
            SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|middle-y;",Size(80,80),Color4B::RED)
                SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "middle-y \n right", "", 18)
            SC_END_CONTAINER

            // back button
            SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black; dock=left|top; x-by=3; y-by=-100;", "Back", "", 22, SCBehaviorSceneBack::create())

        SC_END_CONTAINER
    SC_END_CONTAINER
}



