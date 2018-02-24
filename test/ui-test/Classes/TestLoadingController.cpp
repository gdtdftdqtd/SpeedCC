/****************************************************************************
 
 Copyright (c) 2017-2018 Kevin Wu (Feng Wu)
 
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
    
    SC_BEGIN_CONTAINER_ROOT("dock=center;",SCWinSize)
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,"dock=center;",SCWinSize,Color4B::WHITE)
            // title
            SC_INSERT_LABEL_BMFONT(nullptr,"dock=top|mid-x; y-by=-100;","Test Loading","blue_font.fnt")
    
            SC_INSERT_LABEL(nullptr, "dock=center; color-text=black;", _ptrWatchStr, "", 20)
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
        this->finish();
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
    SC_BEGIN_CONTAINER_ROOT_EX("dock=center;", SCWinSize, _pContainerLayer, this)
        SC_INSERT_BUTTON_LABEL(nullptr, "dock=center; color-text=black;", "Test Back", "", 20, SCBehaviorSceneGoto::create<TestLoadingTraget1Controller>())
    SC_END_CONTAINER
}

///--------------- TestLoadingTraget1Controller
void TestLoadingTraget1Controller::onCreate(SpeedCC::SCDictionary parameters)
{
    parameters.setValue("title", "Test Target1 Loading");
    TestCaseController::onCreate(parameters);
}






