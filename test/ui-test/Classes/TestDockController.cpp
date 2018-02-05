
#include "TestDockController.h"

USING_NS_CC;

void TestDockController::onCreate(SCDictionary parameters)
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
                                                     _ptrCaseBvr->execute(SCDictionary());
                                                 });
    
    auto ptrPreBvr = SCBehaviorCallFunc::create([this]()
                                                 {
                                                     (*_ptrCaseBvr->getWatch())--;
                                                     if((*_ptrCaseBvr->getWatch())<=0)
                                                     {
                                                         _pPreMenuItem->getParent()->setVisible(false);
                                                     }
                                                     _pNextMenuItem->getParent()->setVisible(true);
                                                     _ptrCaseBvr->execute(SCDictionary());
                                                 });
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,NULL,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0.5,0.5,NULL,SCWinSize,Color4B::WHITE)
    
            // title
            SC_INSERT_LABEL_BMFONT(NULL,0,0,"dock=top|mid-x; y-by=-100;","Test Dock","blue_font.fnt")
            SC_INSERT_LABEL(NULL, 0, 0, "dock=top|mid-x; y-by=-150; color-text=black;", _ptrWatchDescription, "", 18)
    
            // back button
            SC_INSERT_BUTTON_LABEL(NULL, 0, 0, "color-text=black; dock=left|top; x-by=3; y-by=-100;", "Back", "", 22, SCBehaviorSceneBack::create())
    
            SC_INSERT_BUTTON(&_pNextMenuItem, 0, 0, "dock=center; y-by=-120; x-by=60;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrNextBvr)
    
            SC_INSERT_BUTTON(&_pPreMenuItem, 0, 0, "dock=center; y-by=-120; x-by=-60; rotation=180; visible=false;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrPreBvr)
    
            SC_INSERT_LAYER(&_pContainerLayer, 0.5, 0.5, NULL, SCWinSize)

        SC_END_CONTAINER
    SC_END_CONTAINER
    
    _ptrCaseBvr->setCase(0, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseNoScale, this)));
    _ptrCaseBvr->setCase(1, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseWithScale, this)));
    _ptrCaseBvr->setCase(2, SCBehaviorCallFunc::create(SC_MAKE_FUNC(testCaseWithScaleAnchor, this)));
    
    _ptrCaseBvr->execute(SCDictionary());
}

void TestDockController::testCaseNoScale()
{
    (*_ptrWatchDescription) = "(No Scale, Middle Anchor)";
    _pContainerLayer->removeAllChildren();
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
    
        // center
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=center;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "center", "", 18)
        SC_END_CONTAINER
    
        // top-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|top;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n left", "", 18)
        SC_END_CONTAINER
    
        // top-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=top|mid-x;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n mid-x", "", 18)
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
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=bottom|mid-x;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // bottom-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|bottom;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n right", "", 18)
        SC_END_CONTAINER
    
        // left mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|mid-y;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "mid-y \n left", "", 18)
        SC_END_CONTAINER
    
        // right mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|mid-y;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "mid-y \n right", "", 18)
        SC_END_CONTAINER
    SC_END_CONTAINER
}



void TestDockController::testCaseWithScale()
{
    (*_ptrWatchDescription) = "(With Scale, Middle Anchor)";
    _pContainerLayer->removeAllChildren();
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
    
        // center
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=center; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "center", "", 18)
        SC_END_CONTAINER
    
        // top-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|top; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n left", "", 18)
        SC_END_CONTAINER
    
        // top-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=top|mid-x; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // top-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|top; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n right", "", 18)
        SC_END_CONTAINER
    
        // bottom-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|bottom; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n left", "", 18)
        SC_END_CONTAINER
    
        // bottom-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=bottom|mid-x; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // bottom-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|bottom; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n right", "", 18)
        SC_END_CONTAINER
    
        // left mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|mid-y; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "mid-y \n left", "", 18)
        SC_END_CONTAINER
    
        // right mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|mid-y; scale=0.5;",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "mid-y \n right", "", 18)
        SC_END_CONTAINER
    SC_END_CONTAINER
}

void TestDockController::testCaseWithScaleAnchor()
{
    (*_ptrWatchDescription) = "(With Scale, Different Anchor)";
    _pContainerLayer->removeAllChildren();
    
    SC_BEGIN_CONTAINER_ROOT_EX(0.5, 0.5, NULL, SCWinSize, _pContainerLayer, this)
    
        // center
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=center; scale=0.5; anchor=(0,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "center", "", 18)
        SC_END_CONTAINER
    
        // top-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|top; scale=0.5; anchor=(0.5,1);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n left", "", 18)
        SC_END_CONTAINER
    
        // top-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=top|mid-x; scale=0.5; anchor=(0,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // top-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|top; scale=0.5; anchor=(0,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "top \n right", "", 18)
        SC_END_CONTAINER
    
        // bottom-left
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|bottom; scale=0.5; anchor=(0.1,0.2);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n left", "", 18)
        SC_END_CONTAINER
    
        // bottom-middle
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=bottom|mid-x; scale=0.5; anchor=(0,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n mid-x", "", 18)
        SC_END_CONTAINER
    
        // bottom-right
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|bottom; scale=0.5; anchor=(0,1);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "bottom \n right", "", 18)
        SC_END_CONTAINER
    
        // left mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=left|mid-y; scale=0.5; anchor=(1,1);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "mid-y \n left", "", 18)
        SC_END_CONTAINER
    
        // right mid-y
        SC_BEGIN_CONTAINER_LAYER_COLOR(NULL,0,0,"dock=right|mid-y; scale=0.5; anchor=(1,0);",Size(80,80),Color4B::RED)
            SC_INSERT_LABEL(NULL, 0.5, 0.5, "color-text=blue;", "mid-y \n right", "", 18)
        SC_END_CONTAINER
    SC_END_CONTAINER
}

