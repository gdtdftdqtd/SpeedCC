
#include "TestCaseController.h"

USING_NS_CC;

void TestCaseController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);
    
    _ptrWatchDescription = SCWatchString::create();
    _ptrCaseBvr = SCBehaviorCaseInt::create();
    auto ptrNextBvr = SCBehaviorCallFunc::create([this]()
                                                 {
                                                     (*_ptrCaseBvr->getWatch())++;
                                                     if(_ptrCaseBvr->getCaseCount()-1 <= (*_ptrCaseBvr->getWatch()))
                                                     {
                                                         _pNextMenuItem->getParent()->setVisible(false);
                                                     }
                                                     
                                                     _pPreMenuItem->getParent()->setVisible(true);
                                                     _ptrCaseBvr->execute();
                                                 });
    
    auto ptrPreBvr = SCBehaviorCallFunc::create([this]()
                                                 {
                                                     (*_ptrCaseBvr->getWatch())--;
                                                     if((*_ptrCaseBvr->getWatch())<=0)
                                                     {
                                                         _pPreMenuItem->getParent()->setVisible(false);
                                                     }
                                                     _pNextMenuItem->getParent()->setVisible(true);
                                                     _ptrCaseBvr->execute();
                                                 });
    
    bool bDock = false;
    if(parameters.hasKey("name"))
    {
        auto value = parameters.getValue("name");
        bDock = (value.getString()=="dock");
    }
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)
    
            if(bDock)
            {
                // title
                SC_INSERT_LABEL_BMFONT(NULL,0,0,"dock=top|mid-x; y-by=-100;","Test Stage","blue_font.fnt")
                SC_INSERT_LABEL(NULL, 0, 0, "dock=top|mid-x; y-by=-150; color-text=black;", _ptrWatchDescription, "", 18)
                
                // back button
                SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black; dock=left|top; x-by=3; y-by=-100;", "Back", "", 22, SCBehaviorSceneBack::create())
                
                SC_INSERT_BUTTON(&_pNextMenuItem, 0, 0, "dock=bottom|mid-x; y-by=100; x-by=60;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrNextBvr)
                
                SC_INSERT_BUTTON(&_pPreMenuItem, 0, 0, "dock=bottom|mid-x; y-by=100; x-by=-60; rotation=180; visible=false;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrPreBvr)
            }
            else
            {
                // title
                SC_INSERT_LABEL_BMFONT(NULL,0,0,"dock=top|mid-x; y-by=-50;","Test Stage","blue_font.fnt")
                SC_INSERT_LABEL(NULL, 0, 0, "dock=top|mid-x; y-by=-100; color-text=black;", _ptrWatchDescription, "", 18)
                
                // back button
                SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black; dock=left|top; x-by=3; y-by=-3;", "Back", "", 22, SCBehaviorSceneBack::create())
                
                SC_INSERT_BUTTON(&_pNextMenuItem, 0, 0, "dock=bottom|mid-x; y-by=50; x-by=60;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrNextBvr)
                
                SC_INSERT_BUTTON(&_pPreMenuItem, 0, 0, "dock=bottom|mid-x; y-by=50; x-by=-60; rotation=180; visible=false;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrPreBvr)
            }
    
            SC_INSERT_LAYER(&_pContainerLayer, 0.5, 0.5, NULL, SCWinSize)

        SC_END_CONTAINER
    SC_END_CONTAINER
}


