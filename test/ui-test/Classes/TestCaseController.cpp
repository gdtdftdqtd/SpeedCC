/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu) All rights reserved.
 
 Licensed under the MIT License (the "License"); you may not use this file except
 in compliance with the License. You may obtain a copy of the License at
 
 http://opensource.org/licenses/MIT
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NON INFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 
 ****************************************************************************/

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
                                                         _pNextMenuItem->setVisible(false);
                                                     }
                                                     
                                                     _pPreMenuItem->setVisible(true);
                                                     _ptrCaseBvr->execute();
                                                 });
    
    auto ptrPreBvr = SCBehaviorCallFunc::create([this]()
                                                 {
                                                     (*_ptrCaseBvr->getWatch())--;
                                                     if((*_ptrCaseBvr->getWatch())<=0)
                                                     {
                                                         _pPreMenuItem->setVisible(false);
                                                     }
                                                     _pNextMenuItem->setVisible(true);
                                                     _ptrCaseBvr->execute();
                                                 });
    
    bool bDock = false;
    if(parameters.hasKey("name"))
    {
        auto value = parameters.getValue("name");
        bDock = (value.getString()=="dock");
    }
    
    SCString strTitle;
    if(parameters.hasKey("title"))
    {
        auto value = parameters.getValue("title");
        strTitle = value.getString();
    }
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,nullptr,SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0.5,0.5,nullptr,SCWinSize,Color4B::WHITE)
    
            if(bDock)
            {
                // title
                SC_INSERT_LABEL_BMFONT(nullptr,0,0,"dock=top|mid-x; y-by=-100;",strTitle,"blue_font.fnt")
                SC_INSERT_LABEL(nullptr, 0, 0, "dock=top|mid-x; y-by=-150; color-text=black;", _ptrWatchDescription, "", 18)
                
                // back button
                SC_INSERT_BUTTON_LABEL(nullptr, 0, 0, "color-text=black; dock=left|top; x-by=3; y-by=-100;", "Back", "", 22, SCBehaviorSceneBack::create())
                
                SC_INSERT_BUTTON(&_pNextMenuItem, 0, 0, "dock=bottom|mid-x; y-by=100; x-by=60;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrNextBvr)
                
                SC_INSERT_BUTTON(&_pPreMenuItem, 0, 0, "dock=bottom|mid-x; y-by=100; x-by=-60; rotation=180; visible=false;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrPreBvr)
            }
            else
            {
                // title
                SC_INSERT_LABEL_BMFONT(nullptr,0,0,"dock=top|mid-x; y-by=-50;",strTitle,"blue_font.fnt")
                SC_INSERT_LABEL(nullptr, 0, 0, "dock=top|mid-x; y-by=-100; color-text=black;", _ptrWatchDescription, "", 18)
                
                // back button
                SC_INSERT_BUTTON_LABEL(nullptr, 0, 0, "color-text=black; dock=left|top; x-by=3; y-by=-3;", "Back", "", 22, SCBehaviorSceneBack::create())
                
                SC_INSERT_BUTTON(&_pNextMenuItem, 0, 0, "dock=bottom|mid-x; y-by=50; x-by=60;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrNextBvr)
                
                SC_INSERT_BUTTON(&_pPreMenuItem, 0, 0, "dock=bottom|mid-x; y-by=50; x-by=-60; rotation=180; visible=false;", "btn_arrow.png", "btn_arrow.png", "btn_arrow.png", ptrPreBvr)
            }
    
            SC_INSERT_LAYER(&_pContainerLayer, 0.5, 0.5, nullptr, SCWinSize)

        SC_END_CONTAINER
    SC_END_CONTAINER
}


