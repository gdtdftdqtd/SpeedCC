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

#include "TestHomeController.h"
#include "TestLabelBindingController.h"
#include "TestStageController.h"
#include "TestDockController.h"
#include "TestProgressController.h"
#include "TestLoadingController.h"
#include "TestPageViewController.h"
#include "TestUIMiscController.h"
#include "TestAlertBoxController.h"

USING_NS_CC;

using namespace SpeedCC;

void TestHomeController::onCreate(SCDictionary parameters)
{
    SCSceneController::onCreate(parameters);

    auto viewSize = Size(SCWinSize.width*3/4,SCWinSize.height*2/3);
    auto containerSize = Size(viewSize.width,viewSize.height);
    
    auto ptrLoadingBvr = SCBehaviorSceneGoto::create<TestLoadingTraget0Controller,SCClassNull,TestLoadingController>();
    
    SC_BEGIN_CONTAINER_ROOT(0.5,0.5,nullptr,nullptr)
        SC_BEGIN_CONTAINER_LAYER_COLOR(nullptr,0.5,0.5,nullptr,SCWinSize,Color4B::WHITE)
            SC_INSERT_LABEL_BMFONT(nullptr,0.5,0.90,"","Home Scene","blue_font.fnt")
    
            SC_BEGIN_CONTAINER_SCROLLVIEW(nullptr,0.5,0.5,"",false,viewSize,containerSize,nullptr)
                SC_BEGIN_CONTAINER_ALIGNMENT(nullptr,0,0,"dock=top|mid-x;",false,20,SCNodeUtils::kDockCenter)
    
                    SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","Label Binding","",23,SCBehaviorSceneGoto::create<TestLabelBindingController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","Stage","",23,SCBehaviorSceneGoto::create<TestStageController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","Dock","",23,SCBehaviorSceneGoto::create<TestDockController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","Progress","",23,SCBehaviorSceneGoto::create<TestProgressController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","Loading","",23,ptrLoadingBvr)
    
                    SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","PageView","",23,SCBehaviorSceneGoto::create<TestPageViewController>())
    
//                    SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","PageView","",23,SCBehaviorSceneGoto::create<TestPageViewController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","UI Misc","",23,SCBehaviorSceneGoto::create<TestUIMiscController>())
    
                    SC_INSERT_BUTTON_LABEL(nullptr,0,0,"color-text=black;","AlertBox","",23,SCBehaviorSceneGoto::create<TestAlertBoxController>())
    
                SC_END_CONTAINER
            SC_END_CONTAINER
        SC_END_CONTAINER
    SC_END_CONTAINER
}


